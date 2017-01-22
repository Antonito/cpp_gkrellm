#ifndef POWER_HPP_
#define POWER_HPP_

#include <cstdlib>
#include <vector>
#include "IModuleMonitor.hpp"

namespace Module
{
  class Power : public IModuleMonitor
  {
  public:
    struct PowerGlobal
    {
      size_t      batAlarm;
      size_t      batCapacity;
      size_t      batChargeFull;
      size_t      batChargeNow;
      size_t      batCurrentNow;
      size_t      batVoltageNow;
      std::string batManufacturer;
      std::string batTechnology;
      std::string batStatus;
      std::string batModelName;
      size_t      ACOnline;
      std::string ACType;
    };
    Power();
    virtual ~Power();

    void setData(PowerGlobal *net);
    virtual void parse();
    virtual void setRoute();

  private:
    static PowerGlobal *m_data;
    static std::string  powerSerializer();
  };
}

#endif // !POWER_HPP_