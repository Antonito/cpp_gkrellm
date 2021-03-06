#ifndef WINDOW_HPP_
#define WINDOW_HPP_

#include <termios.h>
#include "AWindow.hpp"

namespace Graphic
{
  namespace Ncurses
  {
    class Window : public Graphic::AWindow
    {
    public:
      Window(std::string const &name);
      virtual ~Window();
      virtual void           updateInfos();
      virtual Graphic::Event update();
      virtual void           refresh();
      void                   resize();
      static void doResize(int s);

    private:
      static bool m_resized;
      static int     readKey();
      static int     keyboardHit();
      struct termios m_orig_termios;
    };
  }
}

#endif // !WINDOW_HPP_
