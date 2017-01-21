#ifndef NCNETWORK_HPP_
#define NCNETWORK_HPP_

#include "Network.hpp"
#include "ANcModule.hpp"
#include "NcTextArea.hpp"
#include "Frame.hpp"

namespace Graphic
{
  namespace Module
  {
    namespace Ncurses
    {
      class NcNetwork : public ANcModule
      {
      public:
	NcNetwork(Graphic::Ncurses::Frame *frame);
	virtual ~NcNetwork();

	virtual void update();
	virtual void refresh();

      private:
	NcNetwork &operator=(NcNetwork const &other);

	::Module::Network::NetworkGlobal m_data;
	Graphic::Ncurses::NcTextArea     m_rec;
	Graphic::Ncurses::NcTextArea     m_recDrop;
	Graphic::Ncurses::NcTextArea     m_send;
	Graphic::Ncurses::NcTextArea     m_sendDrop;
      };
    }
  }
}

#endif // !NCNETWORK_HPP_