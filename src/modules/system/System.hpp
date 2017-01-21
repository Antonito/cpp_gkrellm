#ifndef SYSTEM_HPP_
#define SYSTEM_HPP_

#include <vector>
#include "IModuleMonitor.hpp"

namespace Module
{
  class System : public IMonitorModule
  {
  public:
    struct SystemGlobal
    {
      std::string userName;
      std::string localHost;
      std::string kernel; // kernel version + OS name
      double      uptime; // time since boot in sec
      double idletime; // time the computer has been idle, it is the sum of the
                       // idle time accumulated by each CPU (on some linux)
      double loadAverage1; // during the last minute, the system was overloaded
                           // by X% on average
      double loadAverage5; // during the last 5 minutes, the CPU was idling X%
                           // of the time on average.
      double loadAverage15; // uring the last 15 minutes, the system was
                            // overloaded X% on average
    };
    System();
    virtual ~System();

    void setData(SystemGlobal *net);
    virtual void parse();
    virtual void setRoute();

  private:
    static SystemGlobal *m_data;
  };
}

#endif
