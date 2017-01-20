#include <unistd.h>
#include "HTTPServer.hpp"

int main()
{
  HTTPServer http(12345, 64);

  http.start();
  //  for (size_t i = 0; i < (size_t)~0; ++i);
  for (;;)
    usleep(100);
  return (0);
}
