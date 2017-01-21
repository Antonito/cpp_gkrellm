#ifndef RAM_HPP_
#define RAM_HPP_

#include <vector>
#include <string>
#include "IModuleMonitor.hpp"

namespace Module
{
class RAM : public IModuleMonitor
{
public:
struct RAMData
    {
      size_t memTotal;
      size_t memFree;
      size_t memAvailable;
    };
    struct SWAPData
    {
      size_t swapTotal;
      size_t swapFree;
    };
    struct RAMGlobal
    {
      RAMData  rd;
      SWAPData sd;
    };
    static std::string ramSerializer();
    RAM();
    virtual ~RAM();
    void setData(RAMGlobal *rg);
    virtual void parse();
    virtual void setRoute();

  private:
    static RAMGlobal *m_data;
  };
}

#endif
