#include "Frame.hpp"

namespace Graphic
{
  namespace Ncurses
  {
    Frame::Frame() : AFrame(), m_win(NULL)
    {
    }

    Frame::Frame(Frame const &)
    {
    }

    Frame::~Frame()
    {
    }

    Frame &Frame::operator=(Frame const &)
    {
      return (*this);
    }

    void Frame::enable(size_t x, size_t y, size_t offX, size_t offY,
                       size_t width, size_t height)
    {
      if (this->m_isEnabled)
	this->disable();
      m_x = x;
      m_y = y;
      m_offX = offX;
      m_offY = offY;
      m_width = width;
      m_height = height;

      m_win = ::newwin(m_height, m_width, m_y + m_offY, m_x + m_offX);
      if (m_win == NULL)
	{
	  // THROW: Failed to create ncurses frame
	}
      ::box(m_win, '|', '-');
      ::wrefresh(m_win);
      // Enable child frame recursively
      if (m_splitMode == VERTICAL)
	{
	  if (m_split.size() >= 1)
	    m_split[0]->enable(m_x, m_y, m_offX, m_offY,
	                       m_width * m_ratio + 0.5, m_height);
	  if (m_split.size() >= 2)
	    m_split[1]->enable(m_x + (m_ratio * m_width) + 0.5, m_y, m_offX,
	                       m_offY, m_width * (1.0 - m_ratio) + 0.5,
	                       m_height);
	}
      else
	{
	  if (m_split.size() >= 1)
	    m_split[0]->enable(m_x, m_y, m_offX, m_offY, m_width,
	                       m_height * m_ratio + 0.5);
	  if (m_split.size() >= 2)
	    m_split[1]->enable(m_x, m_y + (m_ratio * m_height) + 0.5, m_offX,
	                       m_offY, m_width,
	                       m_height * (1.0 - m_ratio) + 0.5);
	}
    }

    void Frame::disable()
    {
      ::wborder(m_win, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
      ::wrefresh(m_win);
      ::delwin(m_win);
      if (m_split.size() >= 1)
	m_split[0]->disable();
      if (m_split.size() >= 2)
	m_split[1]->disable();
    }

    void Frame::update()
    {
      if (m_split.size() >= 1)
	m_split[0]->update();
      if (m_split.size() >= 2)
	m_split[1]->update();
      if (m_module)
	{
	  m_module->position(m_x + m_offX, m_y + m_offY, m_width, m_height);
	  m_module->update();
	}
    }

    void Frame::refresh()
    {
      //::wrefresh(m_win);
      ::wnoutrefresh(m_win);
      ::wclear(m_win);
      ::box(m_win, '|', '-');
      if (m_split.size() >= 1)
	m_split[0]->refresh();
      if (m_split.size() >= 2)
	m_split[1]->refresh();
      if (m_module)
	m_module->refresh();
    }

    WINDOW *Frame::getWin() const
    {
      return (m_win);
    }
  }
}
