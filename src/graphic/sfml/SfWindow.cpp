#include <iostream>
#include <SFML/Graphics.hpp>
#include "SfWindow.hpp"

namespace Graphic
{
  namespace SFML
  {
    SfWindow::SfWindow(std::string const &name, size_t width, size_t height)
        : AWindow(name), m_window(sf::VideoMode(width, height), name)
    {
      m_width = width;
      m_height = height;
      m_headerSize = 30;
    }

    SfWindow::~SfWindow()
    {
    }

    SfWindow &SfWindow::operator=(SfWindow const &)
    {
      return (*this);
    }

    bool SfWindow::isOpen() const
    {
      return (m_window.isOpen());
    }

    Graphic::Event SfWindow::update()
    {
      sf::Event event;

      while (m_window.pollEvent(event))
	{
	  switch (event.type)
	    {
	    case sf::Event::Closed:
	      return (Graphic::EXIT);
	      break;
	    case sf::Event::Resized:
	      m_width = event.size.width;
	      m_height = event.size.height;
	      break;
	    case sf::Event::KeyPressed:
	      if (event.key.code == sf::Keyboard::M)
		{
		  return (Graphic::SWITCH_MODE);
		}
	      else if (event.key.code == sf::Keyboard::Escape)
		{
		  return (Graphic::EXIT);
		}
	      else if (event.key.code == sf::Keyboard::P)
		{
		  this->nextTab();
		}
	      else if (event.key.code == sf::Keyboard::O)
		{
		  this->prevTab();
		}
	      break;
	    default:
	      break;
	    }
	}
      if (m_tab.size() > 0)
	{
	  m_currentTab->second->update();
	}
      return (Graphic::CONTINUE);
    }

    void SfWindow::refresh()
    {
      m_window.clear();
      if (m_tab.size() > 0)
	{
	  m_currentTab->second->refresh();
	}
      m_window.display();
    }

    void SfWindow::updateInfos()
    {
    }

    sf::RenderWindow &SfWindow::getWin()
    {
      return (m_window);
    }
  }
}
