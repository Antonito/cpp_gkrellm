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
      size_t buffers;
      size_t cached;
      size_t active;
      size_t inactive;
      size_t active_anon;
      size_t inactive_anon;
      size_t active_file;
      size_t inactive_file;
      size_t unevictable;
      size_t mlocked;
      size_t dirty;
      size_t writeback;
      size_t anon_pages;
      size_t mapped;
      size_t shmem;
      size_t slab;
      size_t sreclaimable;
      size_t sunreclaim;
      size_t kernelstack;
      size_t pagetable;
      size_t nfs_unstable;
      size_t bounce;
      size_t writebacktmp;
      size_t commitlimit;
      size_t committed_as;
      size_t vmallocTotal;
      size_t vmallocUsed;
      size_t vmallocChunk;
      size_t hardwareCorrupted;
      size_t anonHugePages;
      size_t shmemHugePages;
      size_t shmemPmdMapped;
      size_t hugePagesTotal;
      size_t hugePagesFree;
      size_t hugePagesRsvd;
      size_t hugePagesSurp;
      size_t hugepagesize;
      size_t directMap4k;
      size_t directMap2M;
      size_t directMap1G;
    };
    struct SWAPData
    {
      size_t swapTotal;
      size_t swapFree;
      size_t swapCached;
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
