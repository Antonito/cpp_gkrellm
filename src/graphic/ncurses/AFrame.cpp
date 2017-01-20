#include "AFrame.hh"


namespace Graphic
{
  namespace NCurses
  {
AFrame::AFrame(size_t posX, size_t posY, size_t width, size_t height) :
AGraphicFrame(posX, posY, width, height)
{
}

AFrame::AFrame(AFrame const &o) : AGraphicFrame(o.m_x, o.m_y, o.m_width, o.m_height)
{
}

AFrame::~AFrame()
{
}

AFrame &AFrame::operator=(AFrame const &other)
{
  if (this != &other)
  {
	  AGraphicFrame::operator=(other);
  }
  return (*this);
}
}}