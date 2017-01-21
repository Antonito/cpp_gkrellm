#ifndef CPUMODULE_HPP_
#define CPUMODULE_HPP_

#include <string>
#include <vector>
#include <map>
#include "IModuleMonitor.hpp"

namespace Module
{
  namespace Processor
  {
    class CPU : public IModuleMonitor
    {
    public:
      // TODO: Add freq, and comment
      typedef struct CPUData
      {
	std::string coreName;
	size_t      user;
	size_t      nice;
	size_t      system;
	size_t      idle;
	size_t      iowait;
	size_t      irq;
	size_t      softirq;
	double      curFreq; // TODO: add this to JSON
      } CPUData;
      typedef struct CPUGlobal
      {
	std::string          name;
	std::vector<CPUData> coresData;
      } CPUGlobal;
      static std::string cpuSerializer();
      CPU();
      virtual ~CPU();
      void setData(CPUGlobal *cpu);
      virtual void parse();
      virtual void setRoute();

    private:
      static CPUGlobal *m_data;
    };
  }
}
#endif // !CPUMODULE_HPP_
