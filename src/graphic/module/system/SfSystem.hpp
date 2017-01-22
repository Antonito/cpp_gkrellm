#ifndef SFSYSTEM_HPP_
#define SFSYSTEM_HPP_

#include <SFML/Graphics/Text.hpp>
#include "AModule.hpp"
#include "SfFrame.hpp"
#include "System.hpp"
#include "ModuleManager.hpp"

class SfSystem : public Graphic::AModule
{
public:
  SfSystem(Graphic::SFML::SfFrame *frame, ModuleManager const &m);
  ~SfSystem();

  void update();
  void refresh();

private:
  SfSystem &operator=(SfSystem const &other);

  Graphic::SFML::SfFrame *m_frame;

  ::Module::System::SystemGlobal const &m_data;

  sf::Text m_osName;
  sf::Text m_userName;
  sf::Text m_hostName;
  sf::Text m_kernel;
  sf::Text m_datetime;
};

#endif // !SFSYSTEM_HPP_
