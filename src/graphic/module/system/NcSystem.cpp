#include "ModuleManager.hpp"
#include "NcSystem.hpp"

namespace Graphic
{
  namespace Module
  {
    namespace Ncurses
    {
      NcSystem::NcSystem(Graphic::Ncurses::Frame *frame,
                           ModuleManager const &    m)
	: ANcModule(frame), m_data(m.getSystem()), m_text(0.1, 0.1)
      {
      }

      NcSystem::~NcSystem()
      {
      }

      NcSystem &NcSystem::operator=(NcSystem const &)
      {
	return (*this);
      }

      void NcSystem::update()
      {
	m_text.clear();
	m_text << "Host : " << m_data.hostname;
	m_text.split();
	m_text << "User : " << m_data.userName;
	m_text.split();
	m_text.split();
	m_text << "Kernel : " << m_data.kernel;
	m_text.split();
	m_text << "OS Name : " << m_data.osName;
	m_text.split();
	m_text.split();
	m_text << "Uptime : " << m_data.uptime;
	m_text.split();
	m_text << "Idletime : " << m_data.idletime;
	m_text.split();
	m_text.split();
	m_text << "Load average (1 min) : " << m_data.loadAverage1;
	m_text.split();
	m_text << "Load average (5 min) : " << m_data.loadAverage5;
	m_text.split();
	m_text << "Load average (15 min) : " << m_data.loadAverage15;
	m_text.split();
	m_text.split();
	m_text << "Datetime : " << m_data.datetime;
      }

      void NcSystem::refresh()
      {
	m_text.display(*this);
      }
    }
  }
}
