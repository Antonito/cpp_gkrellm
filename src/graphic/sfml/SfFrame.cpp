#include <unistd.h>
#include "SfWindow.hpp"
#include "SfFrame.hpp"

namespace Graphic
{
  namespace SFML
  {
    SfFrame::SfFrame(SfWindow &win) : AFrame(), m_win(win.getWin())
    {
    }

    SfFrame::~SfFrame()
    {
    }

    SfFrame &SfFrame::operator=(SfFrame const &)
    {
      return (*this);
    }

    void SfFrame::enable(size_t x, size_t y, size_t offX, size_t offY,
                         size_t width, size_t height)
    {
      m_x = x;
      m_y = y;
      m_offX = offX;
      m_offY = offY;
      m_width = width;
      m_height = height;
      m_isEnabled = true;
      m_rect.setSize(sf::Vector2f(width, height));
      m_rect.setPosition(m_x + m_offX, m_y + m_offY);
      // m_rect.setFillColor(sf::Color::Red);
      m_rect.setOutlineThickness(10);
      m_rect.setOutlineColor(sf::Color::Red);
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

    void SfFrame::disable()
    {
      m_isEnabled = false;
    }

    void SfFrame::update()
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

    void SfFrame::refresh()
    {
      m_win.draw(m_rect);
      if (m_split.size() >= 1)
	m_split[0]->refresh();
      if (m_split.size() >= 2)
	m_split[1]->refresh();
      if (m_module)
	m_module->refresh();
      usleep(30000);
    }

    sf::RenderWindow &SfFrame::getWin()
    {
      return (m_win);
    }
  }
}
