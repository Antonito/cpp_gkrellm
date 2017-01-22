#ifndef ANCMODULE_HPP_
#define ANCMODULE_HPP_

#include <ncurses.h>
#include "AModule.hpp"
#include "Frame.hpp"

namespace Graphic
{
  namespace Module
  {
    class ANcModule : public Graphic::AModule
    {
    public:
      ANcModule(Graphic::Ncurses::Frame *f);
      virtual ~ANcModule() = 0;
      virtual void update() = 0;
      virtual void refresh() = 0;

      WINDOW *getWin() const;

    protected:
      ANcModule(ANcModule const &other);
      ANcModule &operator=(ANcModule const &other);

      Graphic::Ncurses::Frame *m_frame;
    };
  }
}

#endif // !ANCMODULE_HPP_