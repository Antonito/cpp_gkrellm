#ifndef WINDOW_HPP_
#define WINDOW_HPP_

#include <termios.h>
#include "Graphic/AWindow.hpp"

namespace Graphic
{
  namespace Ncurses
  {
    class Window : public Graphic::AWindow
    {
    public:
      Window(std::string const &name);
      virtual ~Window();
      virtual void updateInfos();
      virtual bool update();
      virtual void refresh() const;

    private:
      static int     readKey();
      static int     keyboardHit();
      struct termios m_orig_termios;
    };
  }
}

#endif // !WINDOW_HPP_