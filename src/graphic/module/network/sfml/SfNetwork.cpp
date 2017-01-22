#include <iostream>
#include <sstream>
#include "SfNetwork.hpp"

// clang-format off

SfNetwork::SfNetwork(Graphic::SFML::SfFrame *frame, ModuleManager const &m)
    : m_frame(frame),
    m_data(m.getNetwork())
{
}

SfNetwork::~SfNetwork()
{
}

SfNetwork &SfNetwork::operator=(SfNetwork const &)
{
  return (*this);
}

void SfNetwork::update()
{
  std::stringstream ss;
  // clang-format off
  std::vector< ::Module::Network::NetworkData>::const_iterator it;
  // clang-format on

  it = m_data.nd.begin();
  while (it != m_data.nd.end() && it->interface != "wlo1")
    it++;

  std::cout << it->packetRecv << std::endl;

  ss << it->packetRecv;
  m_rec.setString(ss.str());
  m_rec.setColor(sf::Color::Black);
  ss.str("");

  ss << it->packetRecvDrop;
  m_recDrop.setString(ss.str());
  m_recDrop.setColor(sf::Color::Black);
  ss.str("");

  ss << it->packetSend;
  m_send.setString(ss.str());
  m_send.setColor(sf::Color::Black);
  ss.str("");

  ss << it->packetSendDrop;
  m_sendDrop.setString(ss.str());
  m_sendDrop.setColor(sf::Color::Black);
}

void SfNetwork::refresh()
{
  m_rec.setPosition(m_x + 0.1 * m_width, m_y + 0.1 * m_height);
  m_frame->getWin().draw(m_rec);

  m_recDrop.setPosition(m_x + 0.8 * m_width, m_y + 0.5 * m_height);
  m_frame->getWin().draw(m_recDrop);

  m_send.setPosition(m_x + 0.1 * m_width, m_y + 0.1 * m_height);
  m_frame->getWin().draw(m_send);

  m_sendDrop.setPosition(m_x + 0.8 * m_width, m_y + 0.5 * m_height);
  m_frame->getWin().draw(m_sendDrop);
}