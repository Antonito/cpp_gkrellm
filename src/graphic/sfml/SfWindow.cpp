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
