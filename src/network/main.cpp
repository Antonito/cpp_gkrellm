#include <unistd.h>
#include "HTTPServer.hpp"

int main()
{
  HTTPServer srv(12345, 64);

  srv.start();
  //  for (size_t i = 0; i < (size_t)~0; ++i);
  sleep(20);
  return (0);
}