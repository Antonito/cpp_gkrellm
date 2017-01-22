#include "AWindow.hpp"
#include "Logger.hpp"

namespace Graphic
{
  AWindow::AWindow(std::string const &name) : m_name(name)
  {
  }

  AWindow::~AWindow()
  {
    for (std::map<std::string, AFrame *>::iterator it = m_tab.begin();
         it != m_tab.end(); ++it)
      delete it->second;
  }

  void AWindow::addTab(std::string const &name, AFrame &frame)
  {
    Logger &logger = Logger::Instance();

    logger.log(Logger::Info, "Adding tab " + name);
    m_tab[name] = &frame;
    if (m_tab.size() == 1)
      m_currentTab = m_tab.begin();
  }

  void AWindow::nextTab()
  {
    Logger &logger = Logger::Instance();

    logger.log(Logger::Info, "Switching to next tab");
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
    Logger &logger = Logger::Instance();

    logger.log(Logger::Info, "Switching to prev tab");
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
    Logger &logger = Logger::Instance();

    logger.log(Logger::Info, "Enabled window");
    this->updateInfos();
    if (m_tab.size() > 0 && m_currentTab->second->isEnabled() == false)
      {
	m_currentTab->second->enable(0, m_headerSize, 0, 0, m_width,
	                             m_height - m_headerSize);
      }
  }

  void AWindow::disable()
  {
    Logger &logger = Logger::Instance();

    logger.log(Logger::Info, "Disabled window");
    if (m_tab.size() > 0 && m_currentTab->second->isEnabled() == true)
      {
	m_currentTab->second->disable();
      }
  }
}
