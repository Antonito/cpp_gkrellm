#include <iostream>
#include <sstream>
#include "SfNetwork.hpp"

// clang-format off

SfNetwork::SfNetwork(Graphic::SFML::SfFrame *frame, ModuleManager const &m)
    : m_frame(frame),
      m_data(m.getNetwork())
{
  static sf::Font font;
  if (!font.loadFromFile("./fonts/arial.ttf"))
    {
      //throw
    }
  m_rec.setFont(font);
  m_recDrop.setFont(font);
  m_send.setFont(font);
  m_sendDrop.setFont(font);
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

  // std::cout << it->packetRecv << std::endl;

  ss << "Packet received: " << it->packetRecv;
  m_rec.setString(ss.str());
  m_rec.setFillColor(sf::Color::Black);
  ss.str("");

  ss << "Packet received drop: " << it->packetRecvDrop;
  m_recDrop.setString(ss.str());
  m_recDrop.setFillColor(sf::Color::Black);
  ss.str("");

  ss << "Packet sent: " << it->packetSend;
  m_send.setString(ss.str());
  m_send.setFillColor(sf::Color::Black);
  ss.str("");

  ss << "Packet sent drop: " << it->packetSendDrop;
  m_sendDrop.setString(ss.str());
  m_sendDrop.setFillColor(sf::Color::Black);
}

void SfNetwork::refresh()
{
  m_rec.setPosition(m_x + 0.1 * m_width, m_y + 0.1 * m_height);
  m_frame->getWin().draw(m_rec);

  m_recDrop.setPosition(m_x + 0.1 * m_width, (m_y + 20) + 0.2 * m_height);
  m_frame->getWin().draw(m_recDrop);

  m_send.setPosition(m_x + 0.1 * m_width, (m_y + 20) + 0.4 * m_height);
  m_frame->getWin().draw(m_send);

  m_sendDrop.setPosition(m_x + 0.1 * m_width, (m_y + 20) + 0.6 * m_height);
  m_frame->getWin().draw(m_sendDrop);
}
