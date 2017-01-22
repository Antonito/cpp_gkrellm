#include "AModule.hpp"

namespace Graphic
{
  AModule::AModule() : m_x(0), m_y(0), m_width(0), m_height(0)
  {
  }

  AModule::AModule(AModule const &o)
      : m_x(o.m_x), m_y(o.m_y), m_width(o.m_width), m_height(o.m_height)
  {
  }

  AModule::~AModule()
  {
  }

  AModule &AModule::operator=(AModule const &o)
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

  void AModule::position(size_t x, size_t y, size_t width, size_t height)
  {
    m_x = x;
    m_y = y;
    m_width = width;
    m_height = height;
  }

  size_t AModule::getX() const
  {
    return (m_x);
  }

  size_t AModule::getY() const
  {
    return (m_y);
  }

  size_t AModule::getWidth() const
  {
    return (m_width);
  }

  size_t AModule::getHeight() const
  {
    return (m_height);
  }
}