#ifndef SYSTEM_HPP_
#define SYSTEM_HPP_

#include <vector>
#include "IModuleMonitor.hpp"

namespace Module
{
  class System : public IModuleMonitor
  {
  public:
    struct SystemGlobal
    {
      std::string hostname;
      std::string userName;
      std::string kernel; // kernel version
      std::string osName; // os name, should be set to 'linux'
      double      uptime; // time since boot in sec
      double idletime; // time the computer has been idle, it is the sum of the
                       // idle time accumulated by each CPU (on some linux)
      double loadAverage1; // during the last minute, the system was overloaded
                           // by X% on average
      double loadAverage5; // during the last 5 minutes, the CPU was idling X%
                           // of the time on average.
      double loadAverage15; // uring the last 15 minutes, the system was
                            // overloaded X% on average
      std::string datetime; // current time and date;
    };
    System();
    virtual ~System();

    void setData(SystemGlobal *net);
    virtual void parse();
    virtual void setRoute();

  private:
    static SystemGlobal *m_data;
    static std::string   systemSerializer();
  };
}

#endif
