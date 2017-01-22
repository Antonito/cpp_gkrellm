#include <unistd.h>
#include "ModuleManager.hpp"
#include "Logger.hpp"

static void *_loop(void *_data)
{
  ModuleManagerThreadData *data =
      static_cast<ModuleManagerThreadData *>(_data);

  Logger::Instance().log(Logger::Info, "Started one data-miner thread.");
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
  Module::Process *                     proc = new Module::Process();
  Module::Power *                       power = new Module::Power();
  Module::Misc *                        misc = new Module::Misc();

  net->setData(
      const_cast<Module::Network::NetworkGlobal *>(&m_buffer.network));
  _module.push_back(net);
  proc->setData(const_cast<Module::Process::ProcessGlobal *>(&m_buffer.proc));
  _module.push_back(proc);
  power->setData(const_cast<Module::Power::PowerGlobal *>(&m_buffer.power));
  _module.push_back(power);
  misc->setData(const_cast<Module::Misc::MiscGlobal *>(&m_buffer.misc));
  _module.push_back(misc);
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
      stop();
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
  Logger::Instance().log(Logger::Info, "Module Manager started.");
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
  Logger::Instance().log(Logger::Info, "Module Manager stopped.");
  return (true);
}

Module::Processor::CPU::CPUGlobal const &ModuleManager::getCPU() const
{
  return (*const_cast<Module::Processor::CPU::CPUGlobal *>(&m_buffer.CPU));
}

Module::Network::NetworkGlobal const &ModuleManager::getNetwork() const
{
  return (*const_cast<Module::Network::NetworkGlobal *>(&m_buffer.network));
}

Module::System::SystemGlobal const &ModuleManager::getSystem() const
{
  return (*const_cast<Module::System::SystemGlobal *>(&m_buffer.sys));
}

Module::Disk::DiskGlobal const &ModuleManager::getDisk() const
{
  return (*const_cast<Module::Disk::DiskGlobal *>(&m_buffer.disk));
}

Module::RAM::RAMGlobal const &ModuleManager::getRAM() const
{
  return (*const_cast<Module::RAM::RAMGlobal *>(&m_buffer.ram));
}

Module::Process::ProcessGlobal const &ModuleManager::getProcess() const
{
  return (*const_cast<Module::Process::ProcessGlobal *>(&m_buffer.proc));
}

Module::Power::PowerGlobal const &ModuleManager::getPower() const
{
  return (*const_cast<Module::Power::PowerGlobal *>(&m_buffer.power));
}

Module::Misc::MiscGlobal const &ModuleManager::getMisc() const
{
  return (*const_cast<Module::Misc::MiscGlobal *>(&m_buffer.misc));
}
