#ifndef MAINMANAGER_HPP_
#define MAINMANAGER_HPP_

#include "HTTPServer.hpp"
#include "ModuleManager.hpp"
#include "AFrame.hpp"
#include "Window.hpp"

class MainManager
{
public:
  MainManager(uint16_t port = 12345, int nbClients = 64);
  ~MainManager();

  void reloadModules();
  void reloadHTTP();

private:
  ModuleManager m_modules;
  HTTPServer    m_http;

  MainManager(MainManager const &);
  MainManager &operator=(MainManager const &);
};

#endif // !MAINMANAGER_HPP_
