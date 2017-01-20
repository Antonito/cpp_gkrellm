#include <ncurses.h>
#include "Window.hh"

int main()
{
  Graphic::NCurses::Window *win = new Graphic::NCurses::Window();
  getch();
  delete win;
}