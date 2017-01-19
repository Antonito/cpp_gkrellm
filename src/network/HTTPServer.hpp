#ifndef HTTPSERVER_HPP_
#define HTTPSERVER_HPP_

#include <queue>
#include "TCPSocket.hpp"
#include "ThreadPool.hpp"
#include "Mutex.hpp"
#include "Semaphore.hpp"

struct HTTPClient
{
  HTTPClient(int fd = -1);
  int  clientFd;
  bool wrote;
};

struct HTTPQueueElem
{
  HTTPQueueElem(HTTPClient &info, char const *str);
  HTTPClient &client;
  char const *payload;
};

struct HTTPServerData
{
  HTTPServerData(bool const &_running, Mutex &_mut, Semaphore &_sem,
                 int const &fd, int const _maxClient);
  bool const &                running;
  Mutex &                     mut;
  Semaphore &                 sem;
  int const &                 srvFd;
  int const                   maxClient;
  std::queue<HTTPQueueElem *> queue;
};

class HTTPServer
{
public:
  HTTPServer(uint16_t port, int maxClient);
  ~HTTPServer();

  bool start();
  bool stop();

  bool isStarted() const;

private:
  bool           m_started;
  TCPSocket      m_sock;
  ThreadPool     m_threads;
  Mutex          m_mut;
  Semaphore      m_sem;
  HTTPServerData m_data;
  HTTPServer(HTTPServer const &);
  HTTPServer &operator=(HTTPServer const &);
  static int accept_client(int fd);
  static void *_serverLoopWrite(void *_data);
  static void *_serverLoopRead(void *_data);
};

#endif // !HTTPSERVER_HPP_
