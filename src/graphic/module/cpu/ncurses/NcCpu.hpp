#ifndef NCCPU_HPP_
#define NCCPU_HPP_

#include "CPU.hpp"
#include "ANcModule.hpp"
#include "NcTextArea.hpp"
#include "Frame.hpp"

namespace Graphic
{
  namespace Module
  {
    namespace Ncurses
    {
      class NcCpu : public ANcModule
      {
      public:
	NcCpu(Graphic::Ncurses::Frame *frame, ModuleManager const &m);
	virtual ~NcCpu();

	virtual void update();
	virtual void refresh();

      private:
	NcCpu &operator=(NcCpu const &other);

	::Module::Processor::CPU::CPUGlobal const &m_data;
	Graphic::Ncurses::NcTextArea            m_name;
	std::vector<Graphic::Ncurses::NcTextArea>            m_curFreq;
      };
    }
  }
}

#endif // !NCCPU_HPP_
