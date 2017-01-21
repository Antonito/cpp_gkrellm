#ifndef HTTPSERVER_HPP_
#define HTTPSERVER_HPP_

#include <queue>
#include <map>
#include "IModuleMonitor.hpp"
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

struct HTTPHeader
{
  enum HTTP_CODE
  {
    HTTP_200 = 0,
    HTTP_404,
    HTTP_500,
    HTTP_501
  };
  static std::string generateHeader(HTTP_CODE          code,
                                    std::string const &payload = "");
  HTTPHeader(std::string const &payload);
  std::string verb;
  std::string route;
  std::string protocol;
};

// Singleton
class HTTPServer
{
public:
  typedef std::string http_route;

  // Returns a JSON string
  typedef std::string (*serializerToJSON)();
  HTTPServer(uint16_t port, int maxClient);
  ~HTTPServer();

  bool start();
  bool stop();
  bool isStarted() const;

  // Routes
  static void addRoute(http_route const &route, serializerToJSON serial);
  static bool             isRoute(http_route const &);
  static serializerToJSON getRoute(http_route const &route);

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
  static std::map<http_route, serializerToJSON> m_routes;
};

#endif // !HTTPSERVER_HPP_
