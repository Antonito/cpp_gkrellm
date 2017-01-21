#include "MainManager.hpp"
#include "Logger.hpp"

MainManager::MainManager(uint16_t port, int nbClients)
  : m_modules(), m_http(port, nbClients)
{
  Logger &logger = Logger::Instance();
  #if 0

  logger.setLogLevel(Logger::Info);
  if (m_logfile.is_open())
    {
      logger.setStream(&m_logfile);
    }
  #endif
  logger.log(Logger::Info, "Starting MainManager.");
  m_modules.start();
  m_http.start();
  logger.log(Logger::Info, "MainManager started.");
}

MainManager::~MainManager()
{
  #if 0
  if (m_logfile.is_open())
    {
      m_logfile.close();
      logger.setStream(&std::clog);
    }
  #endif
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
