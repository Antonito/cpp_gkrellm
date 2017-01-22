#include "ModuleManager.hpp"
#include "NcRAM.hpp"

namespace Graphic
{
  namespace Module
  {
    namespace Ncurses
    {
      NcRAM::NcRAM(Graphic::Ncurses::Frame *frame,
                           ModuleManager const &    m)
	: ANcModule(frame), m_data(m.getRAM()), m_text(0.1, 0.1)
      {
      }

      NcRAM::~NcRAM()
      {
      }

      NcRAM &NcRAM::operator=(NcRAM const &)
      {
	return (*this);
      }

      void NcRAM::update()
      {

	int ram = 0;
	if (m_data.rd.memTotal != 0)
	  ram = m_data.rd.memFree * 50 / m_data.rd.memTotal;

	int swap = 0;
	if (m_data.sd.swapTotal != 0)
	  swap = m_data.sd.swapFree * 50 / m_data.sd.swapTotal;

	m_text.clear();
	m_text << "Ram  : " << std::string(ram, '|') << std::string(50 - ram, '-')
	       << ram * 2 << "%%  " << (m_data.rd.memTotal / 100000) / 10.0 << "GB";
	m_text.split();
	m_text << "Swap : " << std::string(swap, '|') << std::string(50 - swap, '-')
	       << swap * 2 << "%%  " << (m_data.sd.swapTotal / 100000) / 10.0  << "GB";
	m_text.split();
      }

      void NcRAM::refresh()
      {
	m_text.display(*this);
      }
    }
  }
}
