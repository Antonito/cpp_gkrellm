#ifndef NCRAM_HPP_
#define NCRAM_HPP_

#include "System.hpp"
#include "ANcModule.hpp"
#include "NcTextArea.hpp"
#include "Frame.hpp"

namespace Graphic
{
  namespace Module
  {
    namespace Ncurses
    {
      class NcRAM : public ANcModule
      {
      public:
	NcRAM(Graphic::Ncurses::Frame *frame, ModuleManager const &m);
	virtual ~NcRAM();

	virtual void update();
	virtual void refresh();

      private:
	NcRAM &operator=(NcRAM const &other);

	::Module::System::SystemGlobal const &m_data;
	Graphic::Ncurses::NcTextArea            m_text;
      };
    }
  }
}

#endif // !NCRAM_HPP_
