#include "MainManager.hpp"

MainManager::MainManager(uint16_t port, int nbClients)
    : m_modules(), m_http(port, nbClients)
{
  m_modules.start();
  m_http.start();
}

MainManager::~MainManager()
{
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