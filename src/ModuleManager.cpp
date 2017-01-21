#include <unistd.h>
#include "ModuleManager.hpp"
#include "Logger.hpp"

static void *_loop(void *_data)
{
  ModuleManagerThreadData *data =
      static_cast<ModuleManagerThreadData *>(_data);

  // Add routes to the server
  for (std::vector<Module::IModuleMonitor *>::iterator it = data->modules.begin();
       it != data->modules.end(); ++it)
    {
      (*it)->setRoute();
    }
  while (1)
    {
      pthread_testcancel();
      for (std::vector<Module::IModuleMonitor *>::iterator it = data->modules.begin();
           it != data->modules.end(); ++it)
	{
	  (*it)->parse();
	  // TODO: Call module parser
	}
      usleep(data->delay_useconds);
    }
  return (NULL);
}

std::vector<Module::IModuleMonitor *> ModuleManager::createCPUModule()
{
  std::vector<Module::IModuleMonitor *> _module;

  Module::Processor::CPU *cpu = new Module::Processor::CPU();
  cpu->setData(const_cast<Module::Processor::CPU::CPUGlobal *>(&m_buffer.CPU));
  _module.push_back(cpu);
  return (_module);
}

ModuleManager::ModuleManager() : m_started(false)
{
  // Init modules
  ModuleManagerThreadData tmp;

  tmp.modules = createCPUModule();
  tmp.delay_useconds = 1 * 1000 * 1000;
  m_modules.push_back(tmp);
  for (std::vector<ModuleManagerThreadData>::iterator it = m_modules.begin();
       it != m_modules.end(); ++it)
    {
      // Add threads
      m_threads.addThread(&_loop, &(*it));
    }
}

ModuleManager::~ModuleManager()
{
  if (m_started)
    {
      m_threads.stopAll();
    }
  // Free
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