#include <unistd.h>
#include "HTTPServer.hpp"
#include "ModuleManager.hpp"

int main()
{
  HTTPServer    http(12345, 64);
  ModuleManager manager;

  manager.start();
  http.start();
  //  for (size_t i = 0; i < (size_t)~0; ++i);
  for (;;)
    usleep(100);
  return (0);
}
