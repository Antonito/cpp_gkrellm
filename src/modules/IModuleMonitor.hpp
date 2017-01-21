#ifndef IMODULEMONITOR_HPP_
#define IMODULEMONITOR_HPP_

namespace Module
{
  class IModuleMonitor
  {
  public:
    virtual void parse() = 0;
    virtual void setRoute() = 0;
  };
}

#endif // !IMODULEMONITOR_HPP_
