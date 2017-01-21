#include <unistd.h>
#include "MainManager.hpp"

int main()
{
  MainManager manager;

  for (;;)
    usleep(500);
  return (0);
}
