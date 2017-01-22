#include <iostream>
#include "NcTextArea.hpp"

namespace Graphic
{
  namespace Ncurses
  {
    NcTextArea::NcTextArea() : m_x(0), m_y(0)
    {
    }

    NcTextArea::NcTextArea(double x, double y) : m_x(x), m_y(y)
    {
    }

    NcTextArea::NcTextArea(NcTextArea const &o) : m_x(o.m_x), m_y(o.m_y)
    {
      m_value << o.m_value.str();
    }

    NcTextArea::~NcTextArea()
    {
    }

    NcTextArea &NcTextArea::operator=(NcTextArea const &o)
    {
      if (this != &o)
	{
	  m_x = o.m_x;
	  m_y = o.m_y;
	  m_value << o.m_value.str();
	}
      return (*this);
    }

    NcTextArea &NcTextArea::operator<<(std::string const &s)
    {
      m_value << s;
      return (*this);
    }

    NcTextArea &NcTextArea::operator<<(int n)
    {
      m_value << n;
      return (*this);
    }

    void NcTextArea::clear()
    {
      m_value.str("");
    }

    void NcTextArea::display(Graphic::Module::ANcModule const &m) const
    {
      //       ::move(m.getX() + m_x * m.getWidth() + 0.5,
      //              m.getY() + m_y * m.getHeight() + 0.5);
      //::move(0, 0);
      ::mvwprintw(m.getWin(), m_y * m.getHeight() + 0.5,
                  m_x * m.getWidth() + 0.5, m_value.str().c_str());
      //::wrefresh(m.getWin());
    }

    void NcTextArea::setPosition(double x, double y)
    {
      m_x = x;
      m_y = y;
    }
  }
}
