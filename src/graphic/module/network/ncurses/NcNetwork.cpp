#include "ModuleManager.hpp"
#include "NcNetwork.hpp"

namespace Graphic
{
  namespace Module
  {
    namespace Ncurses
    {
      NcNetwork::NcNetwork(Graphic::Ncurses::Frame *frame,
                           ModuleManager const &    m)
	: ANcModule(frame), m_data(m.getNetwork()), m_text(0.1, 0.05)
      {
      }

      NcNetwork::~NcNetwork()
      {
      }

      NcNetwork &NcNetwork::operator=(NcNetwork const &)
      {
	return (*this);
      }

      void NcNetwork::update()
      {
	m_text.clear();
	// clang-format off
	std::vector< ::Module::Network::NetworkData>::const_iterator it;
	// clang-format on

	for (it = m_data.nd.begin(); it != m_data.nd.end(); it++)
	  {
	    m_text.split();
	    m_text << "Interface : " << it->interface;
	    m_text.split();
	    m_text << "  Packet received : " << it->packetRecv;
	    m_text.split();
	    m_text << "  Byte received : " << it->bytesRecv;
	    m_text.split();
	    m_text << "  Packet send : " << it->packetSend;
	    m_text.split();
	    m_text << "  Byte send : " << it->bytesSend;
	    m_text.split();
	  }
      }

      void NcNetwork::refresh()
      {
	m_text.display(*this);
      }
    }
  }
}
