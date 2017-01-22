#include <iostream>
#include "NcTextArea.hpp"

namespace Graphic
{
  namespace Ncurses
  {
    NcTextArea::NcTextArea() : m_x(0), m_y(0)
    {
      m_value.push_back(new std::stringstream());
    }

    NcTextArea::NcTextArea(double x, double y) : m_x(x), m_y(y)
    {
      m_value.push_back(new std::stringstream());
    }

    NcTextArea::NcTextArea(NcTextArea const &o) : m_x(o.m_x), m_y(o.m_y)
    {
      for (size_t i = 0; i < o.m_value.size(); ++i)
	{
	  m_value.push_back(new std::stringstream());
	  *m_value[i] << o.m_value[i]->str();
	}
    }

    NcTextArea::~NcTextArea()
    {
      for (size_t i = 0; i < m_value.size(); ++i)
	delete m_value[i];
    }

    NcTextArea &NcTextArea::operator=(NcTextArea const &o)
    {
      if (this != &o)
	{
	  m_x = o.m_x;
	  m_y = o.m_y;
	  for (size_t i = 0; i < o.m_value.size(); ++i)
	    {
	      m_value.push_back(new std::stringstream());
	      *m_value[i] << o.m_value[i]->str();
	    }
	}
      return (*this);
    }

    NcTextArea &NcTextArea::operator<<(std::string const &s)
    {
      *m_value[m_value.size() - 1] << s;
      return (*this);
    }

    NcTextArea &NcTextArea::operator<<(int n)
    {
      *m_value[m_value.size() - 1] << n;
      return (*this);
    }

    NcTextArea &NcTextArea::operator<<(size_t n)
    {
      *m_value[m_value.size() - 1] << n;
      return (*this);
    }

    NcTextArea &NcTextArea::operator<<(double n)
    {
      *m_value[m_value.size() - 1] << n;
      return (*this);
    }

    void NcTextArea::clear()
    {
      for (size_t i = 0; i < m_value.size(); ++i)
	delete m_value[i];
      m_value.clear();
      m_value.push_back(new std::stringstream());
    }

    void NcTextArea::display(Graphic::Module::ANcModule const &m) const
    {
      //       ::move(m.getX() + m_x * m.getWidth() + 0.5,
      //              m.getY() + m_y * m.getHeight() + 0.5);
      //::move(0, 0);
      for (size_t i = 0; i < m_value.size(); ++i)
	::mvwprintw(m.getWin(), m_y * m.getHeight() + 0.5 + i,
		    m_x * m.getWidth() + 0.5, m_value[i]->str().c_str());
      //::wrefresh(m.getWin());
    }

    void NcTextArea::setPosition(double x, double y)
    {
      m_x = x;
      m_y = y;
    }

    void NcTextArea::split()
    {
      m_value.push_back(new std::stringstream());
    }
  }
}
