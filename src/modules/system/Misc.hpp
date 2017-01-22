#ifndef MISC_HPP_
#define MISC_HPP_

#include <cstdlib>
#include <vector>
#include "IModuleMonitor.hpp"

namespace Module
{
  class Misc : public IModuleMonitor
  {
  public:
    struct MiscGlobal
    {
      size_t      brightness;
      size_t      brightnessMax;
      size_t      capslock;
      size_t      numlock;
      std::string macaddr;
    };
    Misc();
    virtual ~Misc();

    void setData(MiscGlobal *net);
    virtual void parse();
    virtual void setRoute();

  private:
    static MiscGlobal *m_data;
    static std::string miscSerializer();
  };
}

#endif // !MISC_HPP_
