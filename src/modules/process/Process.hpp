#ifndef PROCESS_HPP_
#define PROCESS_HPP_

#include <vector>
#include <string>
#include <unistd.h>
#include "IModuleMonitor.hpp"

namespace Module
{
  class Process : public IModuleMonitor
  {
  public:
    struct ProcessData
    {
      pid_t       pid;
      std::string user;
      std::string cmdline;
    };
    struct ProcessGlobal
    {
      std::vector<ProcessData> pd;
    };
    static std::string processSerializer();
    Process();
    virtual ~Process();
    void setData(ProcessGlobal *rg);
    virtual void parse();
    virtual void setRoute();

  private:
    static ProcessGlobal *m_data;
  };
}

#endif
