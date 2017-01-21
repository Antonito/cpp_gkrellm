#ifndef IMONITORDISPLAY_HPP_
#define IMONITORDISPLAY_HPP_

#include "JSON.hh"

class IMonitorDisplay
{
public:
  virtual ~IMonitorDisplay(){};
  virtual void update() = 0;
  virtual void refresh() = 0;
  virtual void position(size_t x, size_t y, size_t offX, size_t offY,
                        size_t width, size_t height) = 0;
};

#endif // !IMONITORDISPLAY_HPP_