#include <unistd.h>
#include "ModuleManager.hpp"
#include "Logger.hpp"

static void *_loop(void *_data)
{
  ModuleManagerThreadData *data =
      static_cast<ModuleManagerThreadData *>(_data);

  // Add routes to the server
  for (std::vector<IModuleMonitor *>::iterator it = data->modules.begin();
       it != data->modules.end(); ++it)
    {
      // (*it).setRoute();
    }
  while (1)
    {
      pthread_testcancel();
      for (std::vector<IModuleMonitor *>::iterator it = data->modules.begin();
           it != data->modules.end(); ++it)
	{
	  // TODO: Call module parser
	}
      usleep(data->delay_useconds);
    }
  return (NULL);
}

ModuleManager::ModuleManager() : m_started(false)
{
  // Init modules
  // m_modules.push_back();
  for (std::vector<ModuleManagerThreadData>::iterator it = m_modules.begin();
       it != m_modules.end(); ++it)
    {
      // Add threads
      // m_threads.addThread(&_loop, (*it));
    }
}

ModuleManager::~ModuleManager()
{
  if (m_started)
    {
      m_threads.stopAll();
    }
  m_modules.clear();
}

bool ModuleManager::start()
{
  if (m_started)
    {
      return (false);
    }
  m_started = true;
  m_threads.startAll();
  Logger::Instance().log(Logger::INFO, "Module Manager started.");
  return (true);
}

bool ModuleManager::stop()
{
  if (!m_started)
    {
      return (false);
    }
  m_started = false;
  m_threads.stopAll();
  Logger::Instance().log(Logger::INFO, "Module Manager stopped.");
  return (true);
}