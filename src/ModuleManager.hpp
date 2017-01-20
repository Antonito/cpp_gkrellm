#ifndef MODULEMANAGER_HPP_
#define MODULEMANAGER_HPP_

#include <vector>
#include "ThreadPool.hpp"

struct ModuleManagerThreadData
{
  std::vector<IModule *> modules;
  unsigned int           delay_useconds;
};

class ModuleManager
{
public:
  ModuleManager();
  ~ModuleManager();

  bool start();
  bool stop();

private:
  ThreadPool                           m_threads;
  bool                                 m_started;
  std::vector<ModuleManagerThreadData> m_modules;
  ModuleManager(ModuleManager const &);
  ModuleManager &operator=(ModuleManager const &);

  // std::vector<IModule *>createModule1() const;
};

#endif // !MODULEMANAGER_HPP_
