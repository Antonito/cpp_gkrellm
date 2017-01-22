#include <iterator>
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
	: ANcModule(frame), m_data(m.getCPU())
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
	m_name.clear();
	m_curFreq.clear();
	// clang-format off
	std::vector< ::Module::Processor::CPU::CPUData>::const_iterator it;
	// clang-format on

	    m_name << "Processor : " << m_data.name;

	    size_t i = 0;
	for (it = m_data.coresData.begin(); it != m_data.coresData.end(); it++)
	  {
	    Graphic::Ncurses::NcTextArea freq;

	    freq << "Core " << i << " : " << it->curFreq << " MHz";

	    m_curFreq.push_back(freq);
	    i++;
	  }
      }

      void NcCpu::refresh()
      {
	m_name.setPosition(0.1, 0.1);
	m_name.display(*this);
	for (size_t i = 0; i < m_curFreq.size(); ++i)
	  {
	    m_curFreq[i].setPosition(0.1, 0.2 + i * 0.5 / m_curFreq.size() + 0.1);
	    m_curFreq[i].display(*this);
	  }
      }
    }
  }
}
