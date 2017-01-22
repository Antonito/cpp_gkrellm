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
#include <csignal>
#include "Window.hpp"
#include "GraphicException.hpp"

namespace Graphic
{
  namespace Ncurses
  {
    bool Window::m_resized = false;

    void Window::doResize(int s)
    {
      if (s == SIGWINCH)
	{
	  Window::m_resized = true;
	}
    }

    Window::Window(std::string const &name) : AWindow(name)
    {
      struct termios new_term;

      signal(SIGWINCH, Window::doResize);
      Window::m_resized = false;
      getmaxyx(stdscr, m_height, m_width);
      ::initscr();
      ::raw();
      ::keypad(stdscr, TRUE);
      ::noecho();
      ::tcgetattr(0, &m_orig_termios);
      std::memcpy(&new_term, &m_orig_termios, sizeof(new_term));

      ::cfmakeraw(&new_term);
      ::tcsetattr(0, TCSANOW, &new_term);
      ::curs_set(0);
      ::start_color();
      init_pair(1, COLOR_RED, COLOR_YELLOW);
    }

    Window::~Window()
    {
      ::endwin();
    }

    Graphic::Event Window::update()
    {
      if (m_resized)
	return (Graphic::RESIZE);

      while (keyboardHit())
	{
	  int key = getchar();
	  switch (key)
	    {
	    case 'q':
	      return (Graphic::EXIT);
	    case 'm':
	      return (Graphic::SWITCH_MODE);
	    case 'o':
	      this->prevTab();
	      break;
	    case 'p':
	      this->nextTab();
	      break;
	    }
	}
      m_currentTab->second->update();
      return (Graphic::CONTINUE);
    }

    void Window::refresh()
    {
      ::doupdate();
      ::clear();
      m_currentTab->second->refresh();
      usleep(60000);
    }

    void Window::updateInfos()
    {
       getmaxyx(stdscr, m_height, m_width);
      m_headerSize = 0;
    }

    void Window::resize()
    {
      ::wresize(stdscr, m_height, m_width);
      if (m_tab.size() > 0)
	{
	  if (m_currentTab->second->isEnabled())
	    m_currentTab->second->disable();
	  m_currentTab->second->enable(0, m_headerSize, 0, 0, m_width,
	                               m_height - m_headerSize);
	}
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
