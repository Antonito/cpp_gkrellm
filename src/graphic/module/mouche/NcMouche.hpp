#ifndef NCMOUCHE_HPP_
#define NCMOUCHE_HPP_

#include "System.hpp"
#include "ANcModule.hpp"
#include "NcTextArea.hpp"
#include "Frame.hpp"

namespace Graphic
{
  namespace Module
  {
    namespace Ncurses
    {
      class NcMouche : public ANcModule
      {
      public:
	NcMouche(Graphic::Ncurses::Frame *frame, ModuleManager const &m);
	virtual ~NcMouche();

	virtual void update();
	virtual void refresh();

      private:
	NcMouche &operator=(NcMouche const &other);

	::Module::System::SystemGlobal const &m_data;
	Graphic::Ncurses::NcTextArea            m_text[2];
	int m_img;
      };
    }
  }
}

#endif // !NCMOUCHE_HPP_
