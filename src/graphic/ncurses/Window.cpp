#include <ncurses.h>
#include <fcntl.h>
#include <termios.h>
#include <sys/select.h>
#include <cstring>
#include <stdexcept>
#include <string>
#include <unistd.h>
#include <iostream>
#include <sys/ioctl.h>
#include "Window.hpp"
#include "GraphicException.hpp"

namespace Graphic
{
  namespace Ncurses
  {
    Window::Window(std::string const &name) : AWindow(name)
    {
      struct termios new_term;

      ::initscr();
      ::raw();
      ::keypad(stdscr, TRUE);
      ::noecho();
      ::tcgetattr(0, &m_orig_termios);
      std::memcpy(&new_term, &m_orig_termios, sizeof(new_term));

      ::cfmakeraw(&new_term);
      ::tcsetattr(0, TCSANOW, &new_term);
      ::curs_set(0);
    }

    Window::~Window()
    {
      ::endwin();
    }

    bool Window::update()
    {
      while (keyboardHit())
	{
	  int key = getchar();
	  if (key == 'q')
	    return (false);
	}
      m_currentTab->second->update();
      return (true);
    }

    void Window::refresh() const
    {
      //::refresh();
      m_currentTab->second->refresh();
    }

    void Window::updateInfos()
    {
      getmaxyx(stdscr, m_height, m_width);
      m_headerSize = 1;
    }

    int Window::readKey()
    {
      return (0);
    }

    int Window::keyboardHit()
    {
      struct timeval tv = {0L, 0L};
      fd_set         fds;
      FD_ZERO(&fds);
      FD_SET(0, &fds);
      return select(1, &fds, NULL, NULL, &tv);
    }
  }
}
