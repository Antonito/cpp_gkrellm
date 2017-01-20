#include "AGraphicFrame.hh"

namespace Graphic
{
  AGraphicFrame::AGraphicFrame(size_t posX, size_t posY, size_t width,
                               size_t height)
      : m_x(posX), m_y(posY), m_width(width), m_height(height)
  {
  }

  AGraphicFrame::AGraphicFrame(AGraphicFrame const &o)
      : m_x(o.m_x), m_y(o.m_y), m_width(o.m_width), m_height(o.m_height)
  {
  }

  AGraphicFrame::~AGraphicFrame()
  {
  }

  AGraphicFrame &AGraphicFrame::operator=(AGraphicFrame const &o)
  {
    if (this != &o)
      {
	m_x = o.m_x;
	m_y = o.m_y;
	m_width = o.m_width;
	m_height = o.m_height;
      }
    return (*this);
  }
}