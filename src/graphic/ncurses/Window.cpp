#include <ncurses.h>
#include "Window.hh"

namespace Graphic
{
  namespace NCurses
  {
    Window::Window()
    {
      initscr();
      raw();
      keypad(stdscr, TRUE);
      noecho();
    }

    Window::~Window()
    {
      endwin();
    }

    void Window::refresh()
    {
      ::refresh();
    }

    // Private
    Window &Window::operator=(Window const &)
    {
      return *this;
    }
  }
}