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
          : ANcModule(frame), m_data(m.getNetwork()), m_rec(0.1, 0.1),
            m_byteRec(0.1, 0.3),m_send(0.1, 0.5), m_byteSend(0.1, 0.7)
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
	// m_data.nd[0].packetRecv += random() % 10 - 3;
	// m_data.nd[0].packetRecvDrop += random() % 5 - 1;
	// m_data.nd[0].packetSend += random() % 10 - 3;
	// m_data.nd[0].packetSendDrop += random() % 5 - 1;
	m_rec.clear();
	m_byteRec.clear();
	m_send.clear();
	m_byteSend.clear();
	// clang-format off
	std::vector< ::Module::Network::NetworkData>::const_iterator it;
	// clang-format on

	it = m_data.nd.begin();
	while (it != m_data.nd.end() && it->interface != "wlo1")
	  it++;

	m_rec << "Packet received : " << it->packetRecv;
	m_byteRec << "Byte received : " << it->bytesRecv;
	m_send << "Packet send : " << it->packetSend;
	m_byteSend << "Byte send : " << it->bytesSend;
      }

      void NcNetwork::refresh()
      {

	m_rec.display(*this);
	m_byteRec.display(*this);
	m_send.display(*this);
	m_byteSend.display(*this);
      }
    }
  }
}
