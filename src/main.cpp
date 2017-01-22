#include <unistd.h>
#include "MainManager.hpp"
#include "AModule.hpp"
#include "ncurses/NcNetwork.hpp"
#include "Frame.hpp"

int ncurseMode(MainManager const &)
{
  Graphic::Ncurses::Window win("gkrellm");

  // Network

  //

  win.enable();
  while (win.update())
    win.refresh();
  return (0);
}

int sfmlMode(MainManager const &)
{
  return (0);
}

int main()
{
  MainManager manager;
  for (;;)
    usleep(10000);
  ncurseMode(manager);
  return (0);
}
