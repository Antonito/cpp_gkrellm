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
	int ram = m_data.rd.memFree * 100 / m_data.rd.memTotal;
	int swap = m_data.sd.swapFree * 100 / m_data.sd.swapTotal;

	m_text.clear();
	m_text << "Ram  : " << std::string('|', ram) << std::string('-', 100 - ram)
	       << ram << "%  " << m_data.rd.memTotal / 1000000000 << "GB";
	m_text.split();
	m_text << "Swap : " << std::string('|', swap) << std::string('-', 100 - swap)
	       << swap << "%  " << m_data.rd.swapTotal / 1000000000 << "GB";
	m_text.split();
	m_text.split();
      }

      void NcRAM::refresh()
      {
	m_text.display(*this);
      }
    }
  }
}
