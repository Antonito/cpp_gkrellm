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

  static bool send(int fd, char const *str, size_t len);
  static char const *receive(int &fd);

  bool       isStarted() const;
  int const &getFd() const;

  uint16_t getPort() const;
  int      getMaxClients() const;

private:
  int      m_fd;
  uint16_t m_port;
  int      m_maxClient;
};

#endif // !TCPSOCKET_HPP_
