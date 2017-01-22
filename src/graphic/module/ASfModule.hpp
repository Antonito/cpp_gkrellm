#ifndef ASFMODULE_HPP_
#define ASFMODULE_HPP_

#include <SFML/Graphics.hpp>
#include "AModule.hpp"

class ASfModule : public Graphic::AModule
{
public:
  ASfModule();
  virtual ~ASfModule() = 0;

  ASfModule &operator=(ASfModule const &other);
  sf::RenderWindow *getWin();

protected:
  sf::RenderWindow *m_win;
};

#endif // !ASFMODULE_HPP_