#include "AWindow.hpp"

namespace Graphic
{
  AWindow::AWindow(std::string const &name) : m_name(name)
  {
  }

  void AWindow::addTab(std::string const &name, AFrame &frame)
  {
    m_tab[name] = &frame;
    if (m_tab.size() == 1)
      m_currentTab = m_tab.begin();
  }

  void AWindow::nextTab()
  {
    this->updateInfos();
    if (m_tab.size() > 0)
      {
	if (m_currentTab->second->isEnabled())
	  m_currentTab->second->disable();
	m_currentTab++;
	if (m_currentTab == m_tab.end())
	  m_currentTab = m_tab.begin();
	m_currentTab->second->enable(0, m_headerSize, 0, 0, m_width,
	                             m_height - m_headerSize);
      }
  }

  void AWindow::prevTab()
  {
    this->updateInfos();
    if (m_tab.size() > 0)
      {
	if (m_currentTab->second->isEnabled())
	  m_currentTab->second->disable();
	if (m_currentTab == m_tab.begin())
	  m_currentTab = m_tab.end();
	m_currentTab--;
	m_currentTab->second->enable(0, m_headerSize, 0, 0, m_width,
	                             m_height - m_headerSize);
      }
  }

  void AWindow::enable()
  {
    this->updateInfos();
    if (m_tab.size() > 0 && m_currentTab->second->isEnabled() == false)
      {
	m_currentTab->second->enable(0, m_headerSize, 0, 0, m_width,
	                             m_height - m_headerSize);
      }
  }

  void AWindow::disable()
  {
    if (m_tab.size() > 0 && m_currentTab->second->isEnabled() == true)
      {
	m_currentTab->second->disable();
      }
  }
}