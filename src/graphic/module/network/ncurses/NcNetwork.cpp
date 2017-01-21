#include "NcNetwork.hpp"

namespace Graphic
{
  namespace Module
  {
    namespace Ncurses
    {
      NcNetwork::NcNetwork(Graphic::Ncurses::Frame *frame)
          : ANcModule(frame), m_rec(0.1, 0.1), m_recDrop(0.6, 0.1),
            m_send(0.1, 0.7), m_sendDrop(0.6, 0.7)
      {
	m_data.nd.push_back(::Module::Network::NetworkData());
	m_data.nd[0].packetRecv += 100;
	m_data.nd[0].packetRecvDrop += 100;
	m_data.nd[0].packetSend += 100;
	m_data.nd[0].packetSendDrop += 100;
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
	m_data.nd[0].packetRecv += random() % 10 - 3;
	m_data.nd[0].packetRecvDrop += random() % 5 - 1;
	m_data.nd[0].packetSend += random() % 10 - 3;
	m_data.nd[0].packetSendDrop += random() % 5 - 1;
	m_rec.clear();
	m_recDrop.clear();
	m_send.clear();
	m_sendDrop.clear();
	m_rec << "Received : " << m_data.nd[0].packetRecv;
	m_recDrop << "Drop : " << m_data.nd[0].packetRecvDrop;
	m_send << "Send : " << m_data.nd[0].packetSend;
	m_sendDrop << "Drop : " << m_data.nd[0].packetSendDrop;
      }

      void NcNetwork::refresh()
      {

	m_rec.display(*this);
	m_recDrop.display(*this);
	m_send.display(*this);
	m_sendDrop.display(*this);
      }
    }
  }
}
