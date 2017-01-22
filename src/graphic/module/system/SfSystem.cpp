#include <iostream>
#include <sstream>
#include "SfSystem.hpp"

// clang-format off

SfSystem::SfSystem(Graphic::SFML::SfFrame *frame, ModuleManager const &m)
    : m_frame(frame),
      m_data(m.getSystem())
{
  static sf::Font font;
  if (!font.loadFromFile("./fonts/arial.ttf"))
    {
      //throw
    }
  m_osName.setFont(font);
  m_userName.setFont(font);
  m_hostName.setFont(font);
  m_kernel.setFont(font);
  m_datetime.setFont(font);
}

SfSystem::~SfSystem()
{
}

SfSystem &SfSystem::operator=(SfSystem const &)
{
  return (*this);
}

void SfSystem::update()
{
  std::stringstream ss;

  // std::cout << it->packetRecv << std::endl;

  ss << "OS Name: " << m_data.osName;
  m_osName.setString(ss.str());
  m_osName.setFillColor(sf::Color::Black);
  ss.str("");

  ss << "User Name: " << m_data.userName;
  m_userName.setString(ss.str());
  m_userName.setFillColor(sf::Color::Black);
  ss.str("");

  ss << "Hostname: " << m_data.hostname;
  m_hostName.setString(ss.str());
  m_hostName.setFillColor(sf::Color::Black);
  ss.str("");

  ss << "Kernel: " << m_data.kernel;
  m_kernel.setString(ss.str());
  m_kernel.setFillColor(sf::Color::Black);
  ss.str("");

  ss << "Date & Time: " << m_data.datetime;
  m_datetime.setString(ss.str());
  m_datetime.setFillColor(sf::Color::Black);
  ss.str("");
}

void SfSystem::refresh()
{
  m_osName.setPosition(m_x + 0.0 * m_width, m_y + 0.1 * m_height);
  m_frame->getWin().draw(m_osName);

  m_userName.setPosition(m_x + 0.0 * m_width, (m_y + 10) + 0.2 * m_height);
  m_frame->getWin().draw(m_userName);

  m_hostName.setPosition(m_x + 0.0 * m_width, (m_y + 10) + 0.3 * m_height);
  m_frame->getWin().draw(m_hostName);

  m_kernel.setPosition(m_x + 0.0 * m_width, (m_y + 10) + 0.4 * m_height);
  m_frame->getWin().draw(m_kernel);

  m_datetime.setPosition(m_x + 0.0 * m_width, (m_y + 10) + 0.5 * m_height);
  m_frame->getWin().draw(m_datetime);
}
