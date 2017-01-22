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
  m_swap.setFont(font);
  m_swapFree.setFont(font);
  m_mem.setFont(font);
  m_memFree.setFont(font);
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

  ss << "Total swap: " << m_data.sd.swapTotal / 1024 / 1024 << "Go";
  m_swap.setString(ss.str());
  m_swap.setFillColor(sf::Color::Black);
  ss.str("");

  ss << "Free swap: " << m_data.sd.swapFree / 1024 / 1024 << "Go";
  m_swapFree.setString(ss.str());
  m_swapFree.setFillColor(sf::Color::Black);
  ss.str("");

  ss << "Total ram: " << m_data.rd.memTotal / 1024 / 1024 << "Go";
  m_mem.setString(ss.str());
  m_mem.setFillColor(sf::Color::Black);
  ss.str("");

  ss << "used ram: " << m_data.rd.memFree / 1024 / 1024 << "Go";
  m_memFree.setString(ss.str());
  m_memFree.setFillColor(sf::Color::Black);
}

void SfRAM::refresh()
{
  m_swap.setPosition(m_x + 0.1 * m_width, m_y + 0.1 * m_height);
  m_frame->getWin().draw(m_swap);

  m_swapFree.setPosition(m_x + 0.1 * m_width, (m_y + 10) + 0.2 * m_height);
  m_frame->getWin().draw(m_swapFree);

  m_mem.setPosition(m_x + 0.1 * m_width, m_y + 0.4 * m_height);
  m_frame->getWin().draw(m_mem);

  m_memFree.setPosition(m_x + 0.1 * m_width, m_y + 0.5 * m_height);
  m_frame->getWin().draw(m_memFree);
}
