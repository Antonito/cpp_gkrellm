#ifndef SFWINDOW_HPP_
#define SFWINDOW_HPP_

#include <SFML/Graphics.hpp>
#include <string>
#include "AWindow.hpp"

namespace Graphic
{
  namespace SFML
  {
    class SfWindow : public Graphic::AWindow
    {
    public:
      SfWindow(std::string const &name, size_t w, size_t h);
      ~SfWindow();

      bool                   isOpen() const;
      virtual void           updateInfos();
      virtual Graphic::Event update();
      virtual void           refresh();
      sf::RenderWindow &     getWin();

    private:
      SfWindow &operator=(SfWindow const &other);

      sf::RenderWindow m_window;
    };
  }
}

#endif // !SFWINDOW_HPP_