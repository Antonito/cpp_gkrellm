#include <iostream>
#include "NcTextArea.hpp"

namespace Graphic
{
  namespace Ncurses
  {
    NcTextArea::NcTextArea(double x, double y) : m_x(x), m_y(y)
    {
    }

    NcTextArea::NcTextArea(NcTextArea const &)
    {
    }

    NcTextArea::~NcTextArea()
    {
    }

    NcTextArea &NcTextArea::operator=(NcTextArea const &)
    {
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
  }
}
