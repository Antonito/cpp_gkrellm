#include <unistd.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstring>
#include "TCPSocket.hpp"

TCPSocket::TCPSocket(uint16_t port, int maxClient)
    : m_fd(-1), m_port(port), m_maxClient(maxClient)
{
  struct sockaddr_in sin;
  int                enable = 1;

  m_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (m_fd == -1)
    {
      // TODO: throw exception
    }
  if (setsockopt(m_fd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(enable)) < 0)
    {
      // TODO: Log
    }
  sin.sin_addr.s_addr = htonl(INADDR_ANY);
  sin.sin_port = htons(port);
  sin.sin_family = AF_INET;
  if (bind(m_fd, reinterpret_cast<struct sockaddr *>(&sin), sizeof(sin)) == -1)
    {
      // TODO: throw exception
    }
  if (listen(m_fd, maxClient) == -1)
    {
      // TODO: throw exception
    }
}

TCPSocket::TCPSocket(TCPSocket const &other)
{
  m_fd = other.m_fd;
  m_port = other.m_port;
}

TCPSocket &TCPSocket::operator=(TCPSocket const &other)
{
  if (this != &other)
    {
      m_fd = other.m_fd;
      m_port = other.m_port;
    }
  return (*this);
}

TCPSocket::~TCPSocket()
{
  if (m_fd != -1)
    {
      close(m_fd);
    }
}

bool TCPSocket::send(char const *str, size_t len)
{
  assert(m_fd != -1);
  if (write(m_fd, str, len) < 0)
    {
      return (false);
    }
  return (true);
}

char const *TCPSocket::receive()
{
  char *  buff = new char[TCP_BUFF_SIZE];
  ssize_t buffSize = 0;
  ssize_t prev = 0;
  size_t  loop = 0;

  // Security
  while (loop < 100)
    {
      char *tmp;
      buffSize += read(m_fd, buff + prev,
                       static_cast<unsigned>(buffSize) + TCP_BUFF_SIZE - 1);
      for (ssize_t i = prev; i < buffSize; ++i)
	{
	  if (buff[i] == '\r' && i + 1 < buffSize && buff[i + 1] == '\n' &&
	      i + 2 < buffSize && buff[i + 2] == '\r' && i + 3 < buffSize &&
	      buff[i + 3] == '\n')
	    {
	      buff[i] = '\0';
	      return (buff);
	    }
	}
      tmp = new char[buffSize + TCP_BUFF_SIZE];
      std::memcpy(tmp, buff, static_cast<unsigned>(buffSize));
      delete[] buff;
      buff = tmp;
      prev = buffSize;
      ++loop;
    }
  delete[] buff;
  return (NULL);
}

bool TCPSocket::isStarted() const
{
  return (m_fd != -1);
}
