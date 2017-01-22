#include <iostream>
#include <sstream>
#include "SfRAM.hpp"

// clang-format off

SfRAM::SfRAM(Graphic::SFML::SfFrame *frame, ModuleManager const &m)
    : m_frame(frame),
      m_data(m.getRAM())
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

SfRAM::~SfRAM()
{
}

SfRAM &SfRAM::operator=(SfRAM const &)
{
  return (*this);
}

void SfRAM::update()
{
  std::stringstream ss;
  // clang-format off
  std::vector< ::Module::Network::NetworkData>::const_iterator it;
  // clang-format on

  it = m_data.nd.begin();
  while (it != m_data.nd.end() && it->interface != "wlo1")
    it++;

  // std::cout << it->packetRecv << std::endl;

  ss << it->packetRecv;
  m_rec.setString(ss.str());
  m_rec.setFillColor(sf::Color::Black);
  ss.str("");

  ss << it->packetRecvDrop;
  m_recDrop.setString(ss.str());
  m_recDrop.setFillColor(sf::Color::Black);
  ss.str("");

  ss << it->packetSend;
  m_send.setString(ss.str());
  m_send.setFillColor(sf::Color::Black);
  ss.str("");

  ss << it->packetSendDrop;
  m_sendDrop.setString(ss.str());
  m_sendDrop.setFillColor(sf::Color::Black);
}

void SfRAM::refresh()
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
