#ifndef SFFRAME_HPP_
#define SFFRAME_HPP_

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics.hpp>
#include "SfWindow.hpp"
#include "AFrame.hpp"

namespace Graphic
{
  namespace SFML
  {
    class SfFrame : public Graphic::AFrame
    {
    public:
      SfFrame(SfWindow &win);
      ~SfFrame();

      virtual void enable(size_t x, size_t y, size_t offX, size_t offY,
                          size_t width, size_t height);
      virtual void      disable();
      virtual void      update();
      virtual void      refresh();
      sf::RenderWindow &getWin();

    private:
      SfFrame &operator=(SfFrame const &other);

      sf::RenderWindow & m_win;
      sf::RectangleShape m_rect;
    };
  }
}

#endif // !SFFRAME_HPP_
