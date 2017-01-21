#include "MainManager.hpp"
#include "Logger.hpp"

MainManager::MainManager(uint16_t port, int nbClients)
    : m_modules(), m_http(port, nbClients)
{
  Logger::Instance().log(Logger::Info, "Starting MainManager.");
  m_modules.start();
  m_http.start();
  Logger::Instance().log(Logger::Info, "MainManager started.");
}

MainManager::~MainManager()
{
  Logger::Instance().log(Logger::Info, "Stopping MainManager...");
}

void MainManager::reloadModules()
{
  Logger::Instance().log(Logger::Info, "Restarting data miners modules.");
  m_modules.stop();
  m_modules.start();
}

void MainManager::reloadHTTP()
{
  Logger::Instance().log(Logger::Info, "Restarting HTTP server.");
  m_http.stop();
  m_http.start();
}

// Private
MainManager::MainManager(MainManager const &other)
    : m_modules(), m_http(other.m_http.getPort(), other.m_http.getMaxClients())
{
}

MainManager &MainManager::operator=(MainManager const &)
{
  return (*this);
}
