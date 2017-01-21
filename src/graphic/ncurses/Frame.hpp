#ifndef FRAME_HPP_
#define FRAME_HPP_

#include <ncurses.h>
#include "AFrame.hpp"

namespace Graphic
{
  namespace Ncurses
  {
    class Frame : public Graphic::AFrame
    {
    public:
      Frame();
      virtual ~Frame();

      virtual void enable(size_t x, size_t y, size_t offX, size_t offY,
                          size_t width, size_t height);
      virtual void disable();
      virtual void update();
      virtual void refresh();

    private:
      Frame(Frame const &other);
      Frame &operator=(Frame const &other);

      WINDOW *m_win;
    };
  }
}

#endif // !FRAME_HPP_