#ifndef SFCPU_HPP_
#define SFCPU_HPP_

#include <SFML/Graphics/Text.hpp>
#include <vector>
#include "AModule.hpp"
#include "SfFrame.hpp"
#include "Network.hpp"
#include "ModuleManager.hpp"

class SfCPU : public Graphic::AModule
{
public:
  SfCPU(Graphic::SFML::SfFrame *frame, ModuleManager const &m);
  ~SfCPU();

  void update();
  void refresh();

private:
  SfCPU &operator=(SfCPU const &other);

  Graphic::SFML::SfFrame *m_frame;

  ::Module::Network::NetworkGlobal const &m_data;

  sf::Text              m_modelName;
  sf::Text              m_temp;
  std::vector<sf::Text> m_curFreq;
};

#endif // !SFCPU_HPP_
