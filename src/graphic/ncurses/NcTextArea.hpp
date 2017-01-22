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
      NcTextArea();
      NcTextArea(double x, double y);
      ~NcTextArea();
      NcTextArea(NcTextArea const &other);
      NcTextArea &operator=(NcTextArea const &other);

      NcTextArea &operator<<(std::string const &s);
      NcTextArea &operator<<(int n);
      NcTextArea &operator<<(size_t n);
      NcTextArea &operator<<(double n);

      void clear();

      void display(Graphic::Module::ANcModule const &module) const;
      void setPosition(double x, double y);
      void split();

    private:

      std::vector<std::stringstream *> m_value;
      double            m_x;
      double            m_y;
    };
  }
}

#endif // !NCTEXTAREA_HPP_
