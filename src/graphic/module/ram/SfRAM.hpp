#ifndef SFRAM_HPP_
#define SFRAM_HPP_

#include <SFML/Graphics/Text.hpp>
#include "AModule.hpp"
#include "SfFrame.hpp"
#include "Network.hpp"
#include "ModuleManager.hpp"

class SfRAM : public Graphic::AModule
{
public:
  SfRAM(Graphic::SFML::SfFrame *frame, ModuleManager const &m);
  ~SfRAM();

  void update();
  void refresh();

private:
  SfRAM &operator=(SfRAM const &other);

  Graphic::SFML::SfFrame *m_frame;

  ::Module::RAM::RAMGlobal const &m_data;

  sf::Text m_swap;
  sf::Text m_swapFree;
  sf::Text m_mem;
  sf::Text m_memFree;
};

#endif // !SFRAM_HPP_
