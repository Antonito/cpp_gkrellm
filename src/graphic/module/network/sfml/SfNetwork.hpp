#ifndef SFNETWORK_HPP_
#define SFNETWORK_HPP_

#include <SFML/Graphics/Text.hpp>
#include "AModule.hpp"
#include "SfFrame.hpp"
#include "Network.hpp"
#include "ModuleManager.hpp"

class SfNetwork : public Graphic::AModule
{
public:
  SfNetwork(Graphic::SFML::SfFrame *frame, ModuleManager const &m);
  ~SfNetwork();

  void update();
  void refresh();

private:
  SfNetwork &operator=(SfNetwork const &other);

  Graphic::SFML::SfFrame *m_frame;

  ::Module::Network::NetworkGlobal const &m_data;

  sf::Text m_rec;
  sf::Text m_recDrop;
  sf::Text m_send;
  sf::Text m_sendDrop;
};

#endif // !SFNETWORK_HPP_