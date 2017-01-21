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
	size_t      user;    // normal processes executing in user mode
	size_t      nice;    // niced processes executing in user mode
	size_t      system;  // processes executing in kernel mode
	size_t      idle;    // twiddling thumbs
	size_t      iowait;  // waiting for I/O to complete
	size_t      irq;     // ervicing interrupts
	size_t      softirq; // servicing softirqs
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
