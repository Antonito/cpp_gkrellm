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
  m_rec.setFont(font);
  m_recDrop.setFont(font);
  m_send.setFont(font);
  m_sendDrop.setFont(font);
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
  std::stringstream ss;
  // clang-format off
  std::vector< ::Module::Processor::CPU::CPUData>::iterator it;
  // clang-format on

  it = m_data.coresData.begin();
  int i = 0;
  for (; it != m_data.coresData.end(); ++it)
    {
      if (i >= m_data->coresData.size())
	break;
      std::stringstream dtos;
      dtos << "core " << i << ": " << it->curFreq << "MHz";
      sf::Text text;
      text.setString(dtos.str());
      m_curFreq.push_back(text);
      i++;
    }

  // std::cout << it->packetRecv << std::endl;

  ss << m_data.name;
  m_modelName.setString(ss.str());
  m_modelName.setFillColor(sf::Color::Black);
  ss.str("");

  ss << m_data.temp;
  m_temp.setString(ss.str());
  m_temp.setFillColor(sf::Color::Black);
  ss.str("");
}

void SfCPU::refresh()
{
  m_modelName.setPosition(m_x + 0.1 * m_width, m_y + 0.1 * m_height);
  m_frame->getWin().draw(m_modelName);

  m_temp.setPosition(m_x + 0.8 * m_width, m_y + 0.5 * m_height);
  m_frame->getWin().draw(m_temp);

  double toto = 0.1;
  for (std::vector<sf::Text>::iterator it = m_curFreq.begin();
       it != m_curFreq.end(); ++it)
    {
      it->setPosition(m_x + 0.2 * m_width, m_y + 0.1 * m_height + toto);
      m_frame->getWin().draw(*it);
      toto += 0.1;
    }
}
