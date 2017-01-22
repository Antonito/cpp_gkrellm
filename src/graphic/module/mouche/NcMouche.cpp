#include "ModuleManager.hpp"
#include "NcMouche.hpp"

namespace Graphic
{
  namespace Module
  {
    namespace Ncurses
    {
      NcMouche::NcMouche(Graphic::Ncurses::Frame *frame,
			 ModuleManager const &    m)
	: ANcModule(frame), m_data(m.getSystem()), m_img(10)
      {
	m_text[0] << " ,,                          ,,";
	m_text[0].split();
	m_text[0] << " (((((                    )))))";
	m_text[0].split();
	m_text[0] << " ((((((                  ))))))";
	m_text[0].split();
	m_text[0] << "  ((((((                ))))))";
	m_text[0].split();
	m_text[0] << "    (((((,r@@@@@@@@@@e,)))))";
	m_text[0].split();
	m_text[0] << "     (((@@@@@@@@@@@@@@@@)))";
	m_text[0].split();
	m_text[0] << "      \\@@/,:::,\\/,:::,\\@@";
	m_text[0].split();
	m_text[0] << "     /@@@|:::::||:::::|@@@\\";
	m_text[0].split();
	m_text[0] << "    / @@@\\':::'/\\':::'/@@@ \\";
	m_text[0].split();
	m_text[0] << "   /  /@@@@@@@//\\\\@@@@@@@\\  \\";
	m_text[0].split();
	m_text[0] << "  /  /  '@@@@@====@@@@@'  \\  \\";
	m_text[0].split();
	m_text[0] << " /  /     /          \\     \\  \\";
	m_text[0].split();
	m_text[0] << "   /     (            )     \\";
	m_text[0].split();
	m_text[0] << "          \\          /";
	m_text[0].split();
	m_text[0] << "";
	m_text[0].split();

	m_text[1] << "      ,,                ,,";
	m_text[1].split();
	m_text[1] << "    (((((              )))))";
	m_text[1].split();
	m_text[1] << "   ((((((              ))))))";
	m_text[1].split();
	m_text[1] << "   ((((((              ))))))";
	m_text[1].split();
	m_text[1] << "    (((((,r@@@@@@@@@@e,)))))";
	m_text[1].split();
	m_text[1] << "     (((@@@@@@@@@@@@@@@@)))";
	m_text[1].split();
	m_text[1] << "      \\@@/,:::,\\/,:::,\\@@";
	m_text[1].split();
	m_text[1] << "     /@@@|:::::||:::::|@@@\\";
	m_text[1].split();
	m_text[1] << "    / @@@\\':::'/\\':::'/@@@ \\";
	m_text[1].split();
	m_text[1] << "   /  /@@@@@@@//\\\\@@@@@@@\\  \\";
	m_text[1].split();
	m_text[1] << "  (  /  '@@@@@====@@@@@'  \\  )";
	m_text[1].split();
	m_text[1] << "   \\(     /          \\     )/";
	m_text[1].split();
	m_text[1] << "     \\   (            )   /";
	m_text[1].split();
	m_text[1] << "          \\          /";
	m_text[1].split();
	m_text[1] << "";
	m_text[1].split();
	m_text[0].setPosition(0.1, 0.1);
	m_text[1].setPosition(0.1, 0.1);
      }

      NcMouche::~NcMouche()
      {
      }

      NcMouche &NcMouche::operator=(NcMouche const &)
      {
	m_img = 10;
	return (*this);
      }

      void NcMouche::update()
      {

      }

      void NcMouche::refresh()
      {
	if (m_img % 2)
	  m_text[0].display(*this);
	else
	  m_text[1].display(*this);
	if (m_img == 0)
	  m_img = 11;
	m_img--;
      }
    }
  }
}
