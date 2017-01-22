#include <iterator>
#include <iomanip>
#include "ModuleManager.hpp"
#include "NcCpu.hpp"

namespace Graphic
{
  namespace Module
  {
    namespace Ncurses
    {
      NcCpu::NcCpu(Graphic::Ncurses::Frame *frame,
                           ModuleManager const &    m)
	: ANcModule(frame), m_data(m.getCPU()), m_text(0.1, 0.1)
      {
      }

      NcCpu::~NcCpu()
      {
      }

      NcCpu &NcCpu::operator=(NcCpu const &)
      {
	return (*this);
      }

      void NcCpu::update()
      {
	m_text.clear();

	// clang-format off
	std::vector< ::Module::Processor::CPU::CPUData>::const_iterator it;
	// clang-format on

	m_text << "Processor : " << m_data.name;
	m_text.split();

	size_t i = 0;
	for (it = m_data.coresData.begin(); it != m_data.coresData.end(); it++)
	  {
	    std::stringstream s;
	    m_text.split();
	    m_text.split();
	    s << std::fixed << std::setprecision(1) << it->curFreq / 1000;
	    m_text << "Core " << i << " : " << s.str() << " GHz";
	    i++;
	  }
      }

      void NcCpu::refresh()
      {
	m_text.display(*this);
      }
    }
  }
}
