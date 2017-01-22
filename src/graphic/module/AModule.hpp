#ifndef AMODULE_HPP_
#define AMODULE_HPP_

#include "IMonitorDisplay.hpp"

namespace Graphic
{
  class AModule : public IMonitorDisplay
  {
  public:
    AModule();
    virtual ~AModule() = 0;
    virtual void update() = 0;
    virtual void refresh() = 0;
    virtual void position(size_t x, size_t y, size_t width, size_t height);
    size_t getX() const;
    size_t getY() const;
    size_t getWidth() const;
    size_t getHeight() const;

  protected:
    size_t m_x;
    size_t m_y;
    size_t m_width;
    size_t m_height;

  private:
    AModule(AModule const &other);
    AModule &operator=(AModule const &other);
  };
}

#endif // !AMODULE_HPP_