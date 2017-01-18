#include <iostream>
#include <unistd.h>
#include <sys/select.h>
#include <netinet/in.h>
#include "HTTPServer.hpp"

HTTPQueueElem::HTTPQueueElem(int fd, char const *str)
    : clientFd(fd), payload(str)
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
  fd_set          readfds, exceptfds;
  int             maxFd;
  int *           clients = new int[data->maxClient];

  for (ssize_t i = 0; i < data->maxClient; ++i)
    {
      clients[i] = -1;
    }
  while (data->running)
    {
      int rc;
      // Prepare fd
      FD_ZERO(&readfds);
      FD_ZERO(&exceptfds);
      maxFd = data->srvFd;
      FD_SET(data->srvFd, &readfds);
      for (ssize_t i = 0; i < data->maxClient; ++i)
	{
	  if (clients[i] != -1)
	    {
	      FD_SET(clients[i], &readfds);
	      maxFd = (maxFd > clients[i]) ? maxFd : clients[i];
	    }
	}
      exceptfds = readfds;

      // Select
      rc = select(maxFd + 1, &readfds, NULL, &exceptfds, NULL);
      if (rc < 0)
	{
	  // We have an error
	  continue;
	}
      else if (FD_ISSET(data->srvFd, &readfds))
	{
	  int     sock = accept_client(data->srvFd);
	  ssize_t i;

	  for (i = 0; i < data->maxClient; ++i)
	    {
	      if (clients[i] == -1)
		{
		  clients[i] = sock;
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
	      if (clients[i] == -1)
		{
		  continue;
		}
	      else if (FD_ISSET(clients[i], &readfds))
		{
		  char const *payload = TCPSocket::receive(clients[i]);

		  if (payload)
		    {
		      data->mut.lock();
		      data->queue.push(new HTTPQueueElem(clients[i], payload));
		      data->mut.unlock();
		      data->sem.post();
		    }
		}
	      else if (FD_ISSET(clients[i], &exceptfds))
		{
		  close(clients[i]);
		  clients[i] = -1;
		}
	    }
	}
      std::cout << "THREAD READ" << std::endl;
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
      TCPSocket::send(
          elem->clientFd,
          "HTTP/1.0 404 Not found\r\nConnection: close\r\n\r\n",
          sizeof("HTTP/1.0 404 Not found\r\nConnection: close\r\n\r\n"));
      // Parse
      // Respond to Client
      // Disconnect client
      std::cout << "THREAD WRITE" << std::endl;
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