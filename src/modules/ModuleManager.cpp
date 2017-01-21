
#include <unistd.h>
#include "ModuleManager.hpp"
#include "Logger.hpp"

static void *_loop(void *_data)
{
  ModuleManagerThreadData *data =
      static_cast<ModuleManagerThreadData *>(_data);

  while (1)
    {
      pthread_testcancel();
      for (std::vector<Module::IModuleMonitor *>::iterator it =
               data->modules.begin();
           it != data->modules.end(); ++it)
	{
	  (*it)->parse();
	}
      usleep(data->delay_useconds);
    }
  return (NULL);
}

std::vector<Module::IModuleMonitor *> ModuleManager::createCPUModule()
{
  std::vector<Module::IModuleMonitor *> _module;
  Module::Processor::CPU *              cpu = new Module::Processor::CPU();
  Module::System *                      sys = new Module::System();
  Module::Disk *                        disk = new Module::Disk();
  Module::RAM *                         memory = new Module::RAM();

  cpu->setData(const_cast<Module::Processor::CPU::CPUGlobal *>(&m_buffer.CPU));
  _module.push_back(cpu);
  sys->setData(const_cast<Module::System::SystemGlobal *>(&m_buffer.sys));
  _module.push_back(sys);
  disk->setData(const_cast<Module::Disk::DiskGlobal *>(&m_buffer.disk));
  _module.push_back(disk);
  memory->setData(const_cast<Module::RAM::RAMGlobal *>(&m_buffer.ram));
  _module.push_back(memory);
  return (_module);
}

std::vector<Module::IModuleMonitor *> ModuleManager::createNetworkModule()
{
  std::vector<Module::IModuleMonitor *> _module;
  Module::Network *                     net = new Module::Network();

  net->setData(
      const_cast<Module::Network::NetworkGlobal *>(&m_buffer.network));
  _module.push_back(net);
  return (_module);
}

ModuleManager::ModuleManager() : m_started(false)
{
  // Init modules
  ModuleManagerThreadData tmp;

  tmp.modules = createCPUModule();
  tmp.delay_useconds = 1 * 1000 * 1000;
  m_modules.push_back(tmp);
  tmp.modules = createNetworkModule();
  tmp.delay_useconds = 1 * 1000 * 1000;
  m_modules.push_back(tmp);
  for (std::vector<ModuleManagerThreadData>::iterator it = m_modules.begin();
       it != m_modules.end(); ++it)
    {
      // Add routes to server
      for (std::vector<Module::IModuleMonitor *>::iterator jt =
               it->modules.begin();
           jt != it->modules.end(); ++jt)
	{
	  (*jt)->setRoute();
	}
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
  for (std::vector<ModuleManagerThreadData>::iterator it = m_modules.begin();
       it != m_modules.end(); ++it)
    {
      for (std::vector<Module::IModuleMonitor *>::iterator jt =
               (*it).modules.begin();
           jt != (*it).modules.end(); ++jt)
	{
	  delete *jt;
	}
      (*it).modules.clear();
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
