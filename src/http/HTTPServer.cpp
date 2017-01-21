#include <iostream>
#include <sstream>
#include <unistd.h>
#include <sys/select.h>
#include <netinet/in.h>
#include <ctime>
#include <cstdlib>
#include "Logger.hpp"
#include "HTTPServer.hpp"

std::map<HTTPServer::http_route, HTTPServer::serializerToJSON>
    HTTPServer::m_routes =
        std::map<HTTPServer::http_route, HTTPServer::serializerToJSON>();

std::string HTTPHeader::generateHeader(HTTP_CODE          code,
                                       std::string const &payload)
{
  char               buf[100];
  time_t             now = time(0);
  struct tm          tm = *gmtime(&now);
  static std::string _msg[] = {"200 OK", "404 Not Found",
                               "500 Internal Server Error",
                               "501 Not Implemented"};

  strftime(buf, sizeof buf, "%a, %d %b %Y %H:%M:%S %Z", &tm);
  std::string header = "HTTP/1.1 ";
  header += _msg[code];
  header += "\r\nConnection: close\r\n";
  header += "Date: ";
  header += buf;
  header += "\r\n";
  if (code == HTTP_200)
    {
      header += "Content-Type: application/json\r\n";
    }
  if (payload != "")
    {
      std::stringstream nb;

      nb << payload.length();
      header += "Content-length: ";
      header += nb.str();
      header += "\r\n\r\n";
      header += payload;
    }
  else
    {
      header += "\r\n";
    }
  return (header);
}

HTTPHeader::HTTPHeader(std::string const &payload)
{
  // Parses a HTTP Header
  std::istringstream parse(payload);

  parse >> verb;
  parse >> route;
  parse >> protocol;
}

HTTPClient::HTTPClient(int fd) : clientFd(fd), wrote(false)
{
}

HTTPQueueElem::HTTPQueueElem(HTTPClient &info, char const *str)
    : client(info), payload(str)
{
}

HTTPServerData::HTTPServerData(bool const &_running, Mutex &_mut,
                               Semaphore &_sem, int const &fd,
                               int const _maxClient)
    : running(_running), mut(_mut), sem(_sem), srvFd(fd),
      maxClient(_maxClient), clients(NULL)
{
}

HTTPServer::HTTPServer(uint16_t port, int _maxClient)
    : m_started(false), m_sock(port, _maxClient), m_mut(), m_sem(0),
      m_data(m_started, m_mut, m_sem, m_sock.getFd(), _maxClient)
{
}

HTTPServer::~HTTPServer()
{
  if (isStarted())
    {
      stop();
    }
}

int HTTPServer::accept_client(int fd)
{
  struct sockaddr_in sin = {0, 0, 0, 0};
  socklen_t          sinsize = sizeof(sin);
  int                sock;

  sock = accept(fd, reinterpret_cast<struct sockaddr *>(&sin), &sinsize);
  return (sock);
}

void *HTTPServer::_serverLoopRead(void *_data)
{
  HTTPServerData *data = static_cast<HTTPServerData *>(_data);
  fd_set          readfds, writefds, exceptfds;
  int             maxFd;
  HTTPClient *    clients = data->clients;

  for (ssize_t i = 0; i < data->maxClient; ++i)
    {
      clients[i].clientFd = -1;
      clients[i].wrote = false;
    }
  while (data->running)
    {
      int            rc;
      struct timeval timeout;

      // Prepare fd
      FD_ZERO(&readfds);
      FD_ZERO(&exceptfds);
      maxFd = data->srvFd;
      FD_SET(data->srvFd, &readfds);
      for (ssize_t i = 0; i < data->maxClient; ++i)
	{
	  if (clients[i].clientFd != -1)
	    {
	      FD_SET(clients[i].clientFd, &readfds);
	      maxFd =
	          (maxFd > clients[i].clientFd) ? maxFd : clients[i].clientFd;
	    }
	}
      exceptfds = readfds;
      writefds = readfds;

      // Reset timeout, 60 seconds
      timeout.tv_sec = 60;
      timeout.tv_usec = 0;

      // Select
      rc = select(maxFd + 1, &readfds, &writefds, &exceptfds, &timeout);
      if (rc < 0)
	{
	  // We have an error
	  Logger::Instance().log(Logger::ERROR, "select failed");
	  continue;
	}
      else if (FD_ISSET(data->srvFd, &readfds))
	{
	  int     sock = accept_client(data->srvFd);
	  ssize_t i;

	  for (i = 0; i < data->maxClient; ++i)
	    {
	      if (clients[i].clientFd == -1)
		{
		  clients[i].clientFd = sock;
		  clients[i].wrote = false;
		  break;
		}
	    }
	  if (i == data->maxClient)
	    {
	      // We don't have any slots free
	      Logger::Instance().log(Logger::WARNING,
	                             "No more space on HTTP Server");
	      close(sock);
	    }
	}
      else
	{
	  for (ssize_t i = 0; i < data->maxClient; ++i)
	    {
	      if (clients[i].clientFd == -1)
		{
		  continue;
		}
	      else if (FD_ISSET(clients[i].clientFd, &readfds))
		{
		  char const *payload =
		      TCPSocket::receive(clients[i].clientFd);

		  if (payload)
		    {
		      data->mut.lock();
		      data->queue.push(new HTTPQueueElem(clients[i], payload));
		      data->mut.unlock();
		      data->sem.post();
		    }
		  else
		    {
		      if (clients[i].clientFd > 0)
			{
			  close(clients[i].clientFd);
			}
		      clients[i].clientFd = -1;
		      clients[i].wrote = false;
		    }
		}
	      else if (FD_ISSET(clients[i].clientFd, &writefds))
		{
		  if (clients[i].wrote == true)
		    {
		      close(clients[i].clientFd);
		      clients[i].clientFd = -1;
		      clients[i].wrote = false;
		    }
		}
	      else if (FD_ISSET(clients[i].clientFd, &exceptfds))
		{
		  close(clients[i].clientFd);
		  clients[i].clientFd = -1;
		  clients[i].wrote = false;
		}
	    }
	}
    }
  return (NULL);
}

void *HTTPServer::_serverLoopWrite(void *_data)
{
  HTTPServerData *data = static_cast<HTTPServerData *>(_data);

  while (data->running)
    {
      HTTPQueueElem *elem;

      data->sem.wait();
      data->mut.lock();
      // Get data from queue
      elem = data->queue.front();
      data->queue.pop();
      data->mut.unlock();

      // Parse
      HTTPHeader  header(elem->payload);
      std::string repHeader;
      if (header.verb != "GET")
	{
	  Logger::Instance().log(Logger::DEBUG, "HTTP server: 501.");
	  repHeader = HTTPHeader::generateHeader(HTTPHeader::HTTP_501);
	}
      else
	{
	  if (isRoute(header.route))
	    {
	      HTTPServer::serializerToJSON serializer = getRoute(header.route);
	      std::string                  msg;

	      Logger::Instance().log(Logger::DEBUG,
	                             "HTTP server: " + header.route);
	      msg = (serializer)();
	      repHeader =
	          HTTPHeader::generateHeader(HTTPHeader::HTTP_200, msg);
	    }
	  else
	    {
	      Logger::Instance().log(Logger::DEBUG, "HTTP server: 404.");
	      repHeader = HTTPHeader::generateHeader(HTTPHeader::HTTP_404);
	    }
	}

      // Respond to Client
      TCPSocket::send(elem->client.clientFd, repHeader.c_str(),
                      repHeader.length());
      elem->client.wrote = true;
      delete[] elem->payload;
      delete elem;
    }
  return (NULL);
}

bool HTTPServer::start()
{
  if (isStarted())
    {
      return (false);
    }
  m_started = true;
  m_data.clients = new HTTPClient[m_data.maxClient]();
  m_threads.addThread(&_serverLoopRead, &m_data);
  m_threads.addThread(&HTTPServer::_serverLoopWrite, &m_data);
  m_threads.startAll();
  Logger::Instance().log(Logger::INFO, "HTTP server started");
  return (true);
}

bool HTTPServer::stop()
{
  if (!isStarted())
    {
      return (false);
    }
  m_threads.stopAll();
  m_started = false;
  delete[] m_data.clients;
  m_data.clients = NULL;
  Logger::Instance().log(Logger::INFO, "HTTP server stopped.");
  return (true);
}

bool HTTPServer::isStarted() const
{
  return (m_started);
}

void HTTPServer::addRoute(HTTPServer::http_route const &route,
                          HTTPServer::serializerToJSON  serial)
{
  m_routes.insert(
      std::pair<HTTPServer::http_route, HTTPServer::serializerToJSON>(route,
                                                                      serial));
}

bool HTTPServer::isRoute(http_route const &route)
{
  return (m_routes.find(route) != m_routes.end());
}

HTTPServer::serializerToJSON HTTPServer::getRoute(http_route const &route)
{
  return ((m_routes.find(route))->second);
}

uint16_t HTTPServer::getPort() const
{
  return (m_sock.getPort());
}

int HTTPServer::getMaxClients() const
{
  return (m_sock.getMaxClients());
}