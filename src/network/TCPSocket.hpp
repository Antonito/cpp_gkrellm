#ifndef TCPSOCKET_HPP_
#define TCPSOCKET_HPP_

#include <stdint.h>
#include <string>

#define TCP_BUFF_SIZE (4096)

class TCPSocket
{
public:
  TCPSocket(uint16_t port, int maxClient);
  TCPSocket(TCPSocket const &);
  TCPSocket &operator=(TCPSocket const &);
  ~TCPSocket();

  bool send(char const *str, size_t len);
  char const *receive();

  bool isStarted() const;

private:
  int      m_fd;
  uint16_t m_port;
  int      m_maxClient;
};

#endif // !TCPSOCKET_HPP_
