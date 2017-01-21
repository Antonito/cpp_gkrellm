#ifndef NCTEXTAREA_HPP_
#define NCTEXTAREA_HPP_

#include <string>
#include <sstream>

#include "ANcModule.hpp"

namespace Graphic
{
  namespace Ncurses
  {
    class NcTextArea
    {
    public:
      NcTextArea(double x, double y);
      ~NcTextArea();

      NcTextArea &operator<<(std::string const &s);
      NcTextArea &operator<<(int n);

      void clear();

      void display(Graphic::Module::ANcModule const &module) const;

    private:
      NcTextArea(NcTextArea const &other);
      NcTextArea &operator=(NcTextArea const &other);

      std::stringstream m_value;
      double            m_x;
      double            m_y;
    };
  }
}

#endif // !NCTEXTAREA_HPP_