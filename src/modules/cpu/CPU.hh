#ifndef CPUMODULE_HH_
#define CPUMODULE_HH_

#include <string>
#include <vector>
#include <map>
#include "IModuleMonitor.hh"

namespace Module
{
  namespace Processor
  {
    class CPU : public IModuleMonitor
    {
    public:
      typedef struct CpuData
      {
	std::string coreName;
	size_t      user;
	size_t      nice;
	size_t      system;
	size_t      idle;
	size_t      iowait;
	size_t      irq;
	size_t      softirq;
      } CpuData;
      typedef struct CpuGlobal
      {
	std::string          name;
	std::vector<CpuData> coresData;
      } CpuGlobal;
      CPU();
      ~CPU();
      virtual void parse();
      virtual void setRoute();

    private:
      CpuGlobal m_data;
    };
  }
}
#endif
