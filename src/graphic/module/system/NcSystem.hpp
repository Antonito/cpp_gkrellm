#ifndef NCSYSTEM_HPP_
#define NCSYSTEM_HPP_

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
      class NcSystem : public ANcModule
      {
      public:
	NcSystem(Graphic::Ncurses::Frame *frame, ModuleManager const &m);
	virtual ~NcSystem();

	virtual void update();
	virtual void refresh();

      private:
	NcSystem &operator=(NcSystem const &other);

	::Module::System::SystemGlobal const &m_data;
	Graphic::Ncurses::NcTextArea            m_text;
      };
    }
  }
}

#endif // !NCSYSTEM_HPP_
