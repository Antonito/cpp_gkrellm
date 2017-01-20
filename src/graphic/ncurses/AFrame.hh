#ifndef AFRAME_HH_
#define AFRAME_HH_

#include <ncurses.h>
#include "graphic/AGraphicFrame.hh"

namespace Graphic
{
  namespace NCurses
  {
    class AFrame : public Graphic::AGraphicFrame
    {
    public:
      AFrame(size_t posX, size_t posY, size_t width, size_t height);
      AFrame(AFrame const &other);
      virtual ~AFrame() = 0;

      AFrame &operator=(AFrame const &other);

    private:
    };
  }
}

#endif // !AFRAME_HH_