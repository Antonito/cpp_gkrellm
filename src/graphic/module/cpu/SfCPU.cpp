#include <iostream>
#include <sstream>
#include "SfCPU.hpp"

// clang-format off

SfCPU::SfCPU(Graphic::SFML::SfFrame *frame, ModuleManager const &m)
    : m_frame(frame),
      m_data(m.getCPU())
{
  static sf::Font font;
  if (!font.loadFromFile("./fonts/arial.ttf"))
    {
      //throw
    }
  m_modelName.setFont(font);
  m_temp.setFont(font);
}

SfCPU::~SfCPU()
{
}

SfCPU &SfCPU::operator=(SfCPU const &)
{
  return (*this);
}

void SfCPU::update()
{
	m_curFreq.clear();
  static sf::Font font;
  if (!font.loadFromFile("./fonts/arial.ttf"))
    {
      //throw
    }
  std::stringstream ss;
  // clang-format off
  std::vector< ::Module::Processor::CPU::CPUData>::const_iterator it;
  // clang-format on

  it = m_data.coresData.begin();
  unsigned int i = 0;
  for (; it != m_data.coresData.end(); ++it)
    {
      if (i >= m_data.coresData.size() - 1)
	break;
      std::stringstream dtos;
      dtos << "core " << i << ": " << it->curFreq << "MHz";
      sf::Text text;
      text.setFont(font);
      text.setString(dtos.str());
      text.setFillColor(sf::Color::Black);
      m_curFreq.push_back(text);
      i++;
    }

  // std::cout << it->packetRecv << std::endl;

  ss << m_data.name;
  m_modelName.setString(ss.str());
  m_modelName.setFillColor(sf::Color::Black);
  ss.str("");

  ss << "Temp. " << m_data.temp / 1000 << "C";
  m_temp.setString(ss.str());
  m_temp.setFillColor(sf::Color::Black);
  ss.str("");
}

void SfCPU::refresh()
{
  m_modelName.setPosition(m_x + 0.1 * m_width, m_y + 0.1 * m_height);
  m_frame->getWin().draw(m_modelName);

  m_temp.setPosition(m_x + 0.1 * m_width, m_y + 0.2 * m_height);
  m_frame->getWin().draw(m_temp);

  int    toto = 0;
  double tata = 0.0;
  for (std::vector<sf::Text>::iterator it = m_curFreq.begin();
       it != m_curFreq.end(); ++it)
    {
      it->setPosition(m_x + 0.2 * m_width,
                      (m_y + toto) + (0.3 + tata) * m_height);
      m_frame->getWin().draw(*it);
      toto += 10;
      tata += 0.1;
    }
}
