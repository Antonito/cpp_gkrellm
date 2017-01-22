#ifndef MODULEMANAGER_HPP_
#define MODULEMANAGER_HPP_

#include <vector>
#include "IModuleMonitor.hpp"
#include "ThreadPool.hpp"
#include "ModuleDataBuffer.hpp"

struct ModuleManagerThreadData
{
  std::vector<Module::IModuleMonitor *> modules;
  unsigned int                          delay_useconds;
};

class ModuleManager
{
public:
  ModuleManager();
  ~ModuleManager();

  bool start();
  bool stop();

  // Getters
  Module::Processor::CPU::CPUGlobal const &getCPU() const;
  Module::Network::NetworkGlobal const &   getNetwork() const;
  Module::System::SystemGlobal const &     getSystem() const;
  Module::Disk::DiskGlobal const &         getDisk() const;
  Module::RAM::RAMGlobal const &           getRAM() const;
  Module::Process::ProcessGlobal const &   getProcess() const;
  Module::Power::PowerGlobal const &       getPower() const;
  Module::Misc::MiscGlobal const &         getMisc() const;

private:
  ThreadPool                           m_threads;
  bool                                 m_started;
  std::vector<ModuleManagerThreadData> m_modules;
  ModuleManager(ModuleManager const &);
  ModuleManager &operator=(ModuleManager const &);

  volatile ModuleDataBuffer m_buffer;

  std::vector<Module::IModuleMonitor *> createCPUModule();
  std::vector<Module::IModuleMonitor *> createNetworkModule();
};

#endif // !MODULEMANAGER_HPP_
