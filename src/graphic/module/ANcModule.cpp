#include "ANcModule.hpp"

namespace Graphic
{
  namespace Module
  {
    ANcModule::ANcModule(Graphic::Ncurses::Frame *f) : m_frame(f)
    {
    }

    ANcModule::ANcModule(ANcModule const &o) : AModule(), m_frame(o.m_frame)
    {
    }

    ANcModule::~ANcModule()
    {
    }

    ANcModule &ANcModule::operator=(ANcModule const &)
    {
      return (*this);
    }

    WINDOW *ANcModule::getWin() const
    {
      return (m_frame->getWin());
    }
  }
}
