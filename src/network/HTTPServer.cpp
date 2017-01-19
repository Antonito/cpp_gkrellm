#include <iostream>
#include <unistd.h>
#include <sys/select.h>
#include <netinet/in.h>
#include "HTTPServer.hpp"

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
    : running(_running), mut(_mut), sem(_sem), srvFd(fd), maxClient(_maxClient)
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
  HTTPClient *    clients = new HTTPClient[data->maxClient]();

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
	  std::cout << "Select error" << std::endl;
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
	      std::cout << "No more space" << std::endl;
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
      std::cout << elem->payload << std::endl;
      // Parse
      // Respond to Client
      TCPSocket::send(
          elem->client.clientFd,
          "HTTP/1.0 404 Not found\r\nConnection: close\r\n\r\n",
          sizeof("HTTP/1.0 404 Not found\r\nConnection: close\r\n\r\n"));
      elem->client.wrote = true;
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
  m_threads.addThread(&_serverLoopRead, &m_data);
  m_threads.addThread(&HTTPServer::_serverLoopWrite, &m_data);
  m_threads.startAll();
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
  return (true);
}

bool HTTPServer::isStarted() const
{
  return (m_started);
}