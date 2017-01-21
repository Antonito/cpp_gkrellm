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
    size_t Window::m_termWidth = 0;
    size_t Window::m_termHeight = 0;

    void do_resize(int s)
    {
      if (s == SIGWINCH)
	{
	  struct winsize w;
	  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

	  Window::setTermSize(w.ws_col, w.ws_row);
	}
    }

    void Window::setTermSize(size_t width, size_t height)
    {
      m_termWidth = width;
      m_termHeight = height;
    }

    Window::Window(std::string const &name) : AWindow(name)
    {
      struct termios new_term;

      signal(SIGWINCH, do_resize);
      do_resize(SIGWINCH);
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
      ::doupdate();
      ::clear();
      m_currentTab->second->refresh();
      usleep(60000);
    }

    void Window::updateInfos()
    {
      // getmaxyx(stdscr, m_height, m_width);
      if (m_width != m_termWidth || m_height != m_termHeight)
	{
	  m_width = m_termWidth;
	  m_height = m_termHeight;
	  this->resize();
	}
      m_headerSize = 1;
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
