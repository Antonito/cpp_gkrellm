#include "MainManager.hpp"
#include "Logger.hpp"

MainManager::MainManager(uint16_t port, int nbClients)
    : m_modules(), m_http(port, nbClients)
{
  Logger &logger = Logger::Instance();

  logger.setLogLevel(Logger::Info);
  logger.log(Logger::Info, "Logging to ./gkrellm.log");
  logger.setFile("./gkrellm.log");
  logger.log(Logger::Info, "Starting MainManager.");
  m_modules.start();
  m_http.start();
  logger.log(Logger::Info, "MainManager started.");
}

MainManager::~MainManager()
{
  Logger &logger = Logger::Instance();

  logger.log(Logger::Info, "Stopping MainManager...");
  logger.closeFile();
  logger.log(Logger::Info, "Closed ./gkrellm.log");
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

ModuleManager const &MainManager::getModuleManager() const
{
  return (m_modules);
}
