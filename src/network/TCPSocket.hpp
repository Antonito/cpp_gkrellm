#ifndef TCPSOCKET_HPP_
#define TCPSOCKET_HPP_

#include <stdint.h>
#include <string>

class TCPSocket
{
public:
  TCPSocket(std::string const &ip, uint16_t port);
  TCPSocket(TCPSocket const &);
  TCPSocket &operator=(TCPSocket const &);
  ~TCPSocket();

  bool send(char const *str);
  char const *receive();

  bool isStarted() const;

private:
  int         m_fd;
  uint16_t    m_port;
  std::string m_ip;
};

#endif // !TCPSOCKET_HPP_
