#include "TCPSocket.hpp"
#include <unistd.h>

TCPSocket::TCPSocket(std::string const &ip, uint16_t port)
{
}
TCPSocket::TCPSocket(TCPSocket const &)
{
}
TCPSocket &TCPSocket::operator=(TCPSocket const &)
{
}

TCPSocket::~TCPSocket()
{
  if (m_fd != -1)
    {
      close(m_fd);
    }
}

bool TCPSocket::send(char const *str)
{
}

char const *TCPSocket::receive()
{
}

bool TCPSocket::isStarted() const
{
  return (m_fd != -1);
}
