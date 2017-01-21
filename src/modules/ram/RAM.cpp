#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include "RAM.hpp"
#include "UtilsModule.hpp"
#include "Logger.hpp"
#include "HTTPServer.hpp"

namespace Module
{
  RAM::RAMGlobal *RAM::m_data = NULL;

  RAM::RAM()
  {
  }

  RAM::~RAM()
  {
  }

  void RAM::setData(RAMGlobal *rg)
  {
    m_data = rg;
  }

  std::string RAM::ramSerializer()
  {
    std::stringstream nb;
    std::string       json = "{ \"ram\" : { \"mem_total\": ";

    nb.str("");
    nb << m_data->rd.memTotal;
    json += nb.str();
    json += ", \"mem_free\": ";
    nb.str("");
    nb << m_data->rd.memFree;
    json += nb.str();
    json += ", \"mem_available\": ";
    nb.str("");
    nb << m_data->rd.memAvailable;
    json += nb.str();

    json += ", \"buffers\": ";
    nb.str("");
    nb << m_data->rd.buffers;
    json += nb.str();
    json += ", \"cached\": ";
    nb.str("");
    nb << m_data->rd.cached;
    json += nb.str();
    json += ", \"active\": ";
    nb.str("");
    nb << m_data->rd.active;
    json += nb.str();
    json += ", \"inactive\": ";
    nb.str("");
    nb << m_data->rd.inactive;
    json += nb.str();
    json += ", \"active_anon\": ";
    nb.str("");
    nb << m_data->rd.active_anon;
    json += nb.str();
    json += ", \"inactive_anon\": ";
    nb.str("");
    nb << m_data->rd.inactive_anon;
    json += nb.str();
    json += ", \"active_file\": ";
    nb.str("");
    nb << m_data->rd.active_file;
    json += nb.str();
    json += ", \"inactive_file\": ";
    nb.str("");
    nb << m_data->rd.inactive_file;
    json += nb.str();
    json += ", \"unevictable\": ";
    nb.str("");
    nb << m_data->rd.unevictable;
    json += nb.str();
    json += ", \"mlocked\": ";
    nb.str("");
    nb << m_data->rd.mlocked;
    json += nb.str();
    json += ", \"dirty\": ";
    nb.str("");
    nb << m_data->rd.dirty;
    json += nb.str();
    json += ", \"writeback\": ";
    nb.str("");
    nb << m_data->rd.writeback;
    json += nb.str();
    json += ", \"anon_pages\": ";
    nb.str("");
    nb << m_data->rd.anon_pages;
    json += nb.str();
    json += ", \"mapped\": ";
    nb.str("");
    nb << m_data->rd.mapped;
    json += nb.str();
    json += ", \"shmem\": ";
    nb.str("");
    nb << m_data->rd.shmem;
    json += nb.str();
    json += ", \"slab\": ";
    nb.str("");
    nb << m_data->rd.slab;
    json += nb.str();
    json += ", \"sreclaimable\": ";
    nb.str("");
    nb << m_data->rd.sreclaimable;
    json += nb.str();
    json += ", \"sunreclaim\": ";
    nb.str("");
    nb << m_data->rd.sunreclaim;
    json += nb.str();
    json += ", \"kernel_stack\": ";
    nb.str("");
    nb << m_data->rd.kernelstack;
    json += nb.str();
    json += ", \"nfs_unstable\": ";
    nb.str("");
    nb << m_data->rd.nfs_unstable;
    json += nb.str();
    json += ", \"pagetable\": ";
    nb.str("");
    nb << m_data->rd.pagetable;
    json += nb.str();
    json += ", \"bounce\": ";
    nb.str("");
    nb << m_data->rd.bounce;
    json += nb.str();
    json += ", \"writebacktmp\": ";
    nb.str("");
    nb << m_data->rd.writebacktmp;
    json += nb.str();
    json += ", \"commit_limit\": ";
    nb.str("");
    nb << m_data->rd.commitlimit;
    json += nb.str();
    json += ", \"committed_as\": ";
    nb.str("");
    nb << m_data->rd.committed_as;
    json += nb.str();
    json += ", \"vmalloc_total\": ";
    nb.str("");
    nb << m_data->rd.vmallocTotal;
    json += nb.str();
    json += ", \"vmalloc_used\": ";
    nb.str("");
    nb << m_data->rd.vmallocUsed;
    json += nb.str();
    json += ", \"vmalloc_chunk\": ";
    nb.str("");
    nb << m_data->rd.vmallocChunk;
    json += nb.str();
    json += ", \"hardware_corrupted\": ";
    nb.str("");
    nb << m_data->rd.hardwareCorrupted;
    json += nb.str();
    json += ", \"anon_huge_pages\": ";
    nb.str("");
    nb << m_data->rd.anonHugePages;
    json += nb.str();
    json += ", \"shmem_huge_pages\": ";
    nb.str("");
    nb << m_data->rd.shmemHugePages;
    json += nb.str();
    json += ", \"shmem_pmd_mapped\": ";
    nb.str("");
    nb << m_data->rd.shmemPmdMapped;
    json += nb.str();
    json += ", \"huge_pages_total\": ";
    nb.str("");
    nb << m_data->rd.hugePagesTotal;
    json += nb.str();
    json += ", \"huge_pages_free\": ";
    nb.str("");
    nb << m_data->rd.hugePagesFree;
    json += nb.str();
    json += ", \"huge_pages_rsvd\": ";
    nb.str("");
    nb << m_data->rd.hugePagesRsvd;
    json += nb.str();
    json += ", \"huge_pages_surp\": ";
    nb.str("");
    nb << m_data->rd.hugePagesSurp;
    json += nb.str();
    json += ", \"huge_page_size\": ";
    nb.str("");
    nb << m_data->rd.hugepagesize;
    json += nb.str();
    json += ", \"direct_map_4k\": ";
    nb.str("");
    nb << m_data->rd.directMap4k;
    json += nb.str();
    json += ", \"direct_map_2m\": ";
    nb.str("");
    nb << m_data->rd.directMap2M;
    json += nb.str();
    json += ", \"direct_map_1g\": ";
    nb.str("");
    nb << m_data->rd.directMap1G;
    json += nb.str();

    json += " }, \"swap\": { \"swap_total\": ";
    nb.str("");
    nb << m_data->sd.swapTotal;
    json += nb.str();
    json += ", \"swap_free\": ";
    nb.str("");
    nb << m_data->sd.swapFree;
    json += nb.str();
    json += ", \"swap_cached\": ";
    nb.str("");
    nb << m_data->sd.swapCached;
    json += nb.str();
    json += " } }";
    return (json);
  }

  void RAM::setRoute()
  {
    Logger::Instance().log(Logger::Info, "Added routes for Memory module");
    HTTPServer::addRoute("/memory", static_cast<HTTPServer::serializerToJSON>(
                                        &RAM::ramSerializer));
  }
  void RAM::parse()
  {
    std::ifstream            ff;
    std::stringstream        strbuf;
    std::vector<std::string> m_split;

    ff.open("/proc/meminfo", std::ios_base::in);
    if (!ff.good())
      {
	Logger::Instance().log(Logger::Error, "Cannot read memory info");
	return;
      }
    strbuf << ff.rdbuf();
    m_split = split(strbuf.str(), '\n');

    for (std::vector<std::string>::iterator it = m_split.begin();
         it != m_split.end(); ++it)
      {
	if (it->find("MemTotal:", 0) == 0)
	  {
	    std::stringstream mystream;
	    std::string       trash;
	    mystream << *it;
	    mystream >> trash;
	    mystream >> m_data->rd.memTotal;
	  }
	else if (it->find("MemFree:", 0) == 0)
	  {
	    std::stringstream mystream;
	    std::string       trash;
	    mystream << *it;
	    mystream >> trash;
	    mystream >> m_data->rd.memFree;
	  }
	else if (it->find("MemAvailable:", 0) == 0)
	  {
	    std::stringstream mystream;
	    std::string       trash;
	    mystream << *it;
	    mystream >> trash;
	    mystream >> m_data->rd.memAvailable;
	  }
	else if (it->find("SwapTotal:", 0) == 0)
	  {
	    std::stringstream mystream;
	    std::string       trash;
	    mystream << *it;
	    mystream >> trash;
	    mystream >> m_data->sd.swapTotal;
	  }
	else if (it->find("SwapFree:", 0) == 0)
	  {
	    std::stringstream mystream;
	    std::string       trash;
	    mystream << *it;
	    mystream >> trash;
	    mystream >> m_data->sd.swapFree;
	  }
	else if (it->find("SwapCached:", 0) == 0)
	  {
	    std::stringstream mystream;
	    std::string       trash;
	    mystream << *it;
	    mystream >> trash;
	    mystream >> m_data->sd.swapCached;
	  }
	else if (it->find("Buffers:", 0) == 0)
	  {
	    std::stringstream mystream;
	    std::string       trash;
	    mystream << *it;
	    mystream >> trash;
	    mystream >> m_data->rd.buffers;
	  }
	else if (it->find("Cached:", 0) == 0)
	  {
	    std::stringstream mystream;
	    std::string       trash;
	    mystream << *it;
	    mystream >> trash;
	    mystream >> m_data->rd.cached;
	  }
	else if (it->find("Active:", 0) == 0)
	  {
	    std::stringstream mystream;
	    std::string       trash;
	    mystream << *it;
	    mystream >> trash;
	    mystream >> m_data->rd.active;
	  }
	else if (it->find("Inactive:", 0) == 0)
	  {
	    std::stringstream mystream;
	    std::string       trash;
	    mystream << *it;
	    mystream >> trash;
	    mystream >> m_data->rd.inactive;
	  }
	else if (it->find("Active(anon):", 0) == 0)
	  {
	    std::stringstream mystream;
	    std::string       trash;
	    mystream << *it;
	    mystream >> trash;
	    mystream >> m_data->rd.active_anon;
	  }
	else if (it->find("Inactive(anon):", 0) == 0)
	  {
	    std::stringstream mystream;
	    std::string       trash;
	    mystream << *it;
	    mystream >> trash;
	    mystream >> m_data->rd.inactive_anon;
	  }
	else if (it->find("Active(file):", 0) == 0)
	  {
	    std::stringstream mystream;
	    std::string       trash;
	    mystream << *it;
	    mystream >> trash;
	    mystream >> m_data->rd.active_file;
	  }
	else if (it->find("Inactive(anon):", 0) == 0)
	  {
	    std::stringstream mystream;
	    std::string       trash;
	    mystream << *it;
	    mystream >> trash;
	    mystream >> m_data->rd.inactive_file;
	  }
	else if (it->find("Unevictable:", 0) == 0)
	  {
	    std::stringstream mystream;
	    std::string       trash;
	    mystream << *it;
	    mystream >> trash;
	    mystream >> m_data->rd.unevictable;
	  }
	else if (it->find("Mlocked:", 0) == 0)
	  {
	    std::stringstream mystream;
	    std::string       trash;
	    mystream << *it;
	    mystream >> trash;
	    mystream >> m_data->rd.mlocked;
	  }
	else if (it->find("Dirty:", 0) == 0)
	  {
	    std::stringstream mystream;
	    std::string       trash;
	    mystream << *it;
	    mystream >> trash;
	    mystream >> m_data->rd.dirty;
	  }
	else if (it->find("Writeback:", 0) == 0)
	  {
	    std::stringstream mystream;
	    std::string       trash;
	    mystream << *it;
	    mystream >> trash;
	    mystream >> m_data->rd.writeback;
	  }
	else if (it->find("AnonPages:", 0) == 0)
	  {
	    std::stringstream mystream;
	    std::string       trash;
	    mystream << *it;
	    mystream >> trash;
	    mystream >> m_data->rd.anon_pages;
	  }
	else if (it->find("Mapped:", 0) == 0)
	  {
	    std::stringstream mystream;
	    std::string       trash;
	    mystream << *it;
	    mystream >> trash;
	    mystream >> m_data->rd.mapped;
	  }
	else if (it->find("Shmem:", 0) == 0)
	  {
	    std::stringstream mystream;
	    std::string       trash;
	    mystream << *it;
	    mystream >> trash;
	    mystream >> m_data->rd.shmem;
	  }
	else if (it->find("Slab:", 0) == 0)
	  {
	    std::stringstream mystream;
	    std::string       trash;
	    mystream << *it;
	    mystream >> trash;
	    mystream >> m_data->rd.slab;
	  }
	else if (it->find("SReclaimable:", 0) == 0)
	  {
	    std::stringstream mystream;
	    std::string       trash;
	    mystream << *it;
	    mystream >> trash;
	    mystream >> m_data->rd.sreclaimable;
	  }
	else if (it->find("KernelStack:", 0) == 0)
	  {
	    std::stringstream mystream;
	    std::string       trash;
	    mystream << *it;
	    mystream >> trash;
	    mystream >> m_data->rd.kernelstack;
	  }
	else if (it->find("PageTables:", 0) == 0)
	  {
	    std::stringstream mystream;
	    std::string       trash;
	    mystream << *it;
	    mystream >> trash;
	    mystream >> m_data->rd.pagetable;
	  }
	else if (it->find("NFS_Unstable:", 0) == 0)
	  {
	    std::stringstream mystream;
	    std::string       trash;
	    mystream << *it;
	    mystream >> trash;
	    mystream >> m_data->rd.nfs_unstable;
	  }
	else if (it->find("Bounce:", 0) == 0)
	  {
	    std::stringstream mystream;
	    std::string       trash;
	    mystream << *it;
	    mystream >> trash;
	    mystream >> m_data->rd.bounce;
	  }
	else if (it->find("WritebackTmp:", 0) == 0)
	  {
	    std::stringstream mystream;
	    std::string       trash;
	    mystream << *it;
	    mystream >> trash;
	    mystream >> m_data->rd.writebacktmp;
	  }
	else if (it->find("CommitLimit:", 0) == 0)
	  {
	    std::stringstream mystream;
	    std::string       trash;
	    mystream << *it;
	    mystream >> trash;
	    mystream >> m_data->rd.commitlimit;
	  }
	else if (it->find("Committed_AS:", 0) == 0)
	  {
	    std::stringstream mystream;
	    std::string       trash;
	    mystream << *it;
	    mystream >> trash;
	    mystream >> m_data->rd.committed_as;
	  }
	else if (it->find("VmallocTotal:", 0) == 0)
	  {
	    std::stringstream mystream;
	    std::string       trash;
	    mystream << *it;
	    mystream >> trash;
	    mystream >> m_data->rd.vmallocTotal;
	  }
	else if (it->find("VmallocUsed:", 0) == 0)
	  {
	    std::stringstream mystream;
	    std::string       trash;
	    mystream << *it;
	    mystream >> trash;
	    mystream >> m_data->rd.vmallocUsed;
	  }
	else if (it->find("VmallocChunk:", 0) == 0)
	  {
	    std::stringstream mystream;
	    std::string       trash;
	    mystream << *it;
	    mystream >> trash;
	    mystream >> m_data->rd.vmallocChunk;
	  }
	else if (it->find("HardwareCorrupted:", 0) == 0)
	  {
	    std::stringstream mystream;
	    std::string       trash;
	    mystream << *it;
	    mystream >> trash;
	    mystream >> m_data->rd.hardwareCorrupted;
	  }
	else if (it->find("AnonHugePages:", 0) == 0)
	  {
	    std::stringstream mystream;
	    std::string       trash;
	    mystream << *it;
	    mystream >> trash;
	    mystream >> m_data->rd.anonHugePages;
	  }
	else if (it->find("ShmemHugePages:", 0) == 0)
	  {
	    std::stringstream mystream;
	    std::string       trash;
	    mystream << *it;
	    mystream >> trash;
	    mystream >> m_data->rd.shmemHugePages;
	  }
	else if (it->find("ShmemPmdMapped:", 0) == 0)
	  {
	    std::stringstream mystream;
	    std::string       trash;
	    mystream << *it;
	    mystream >> trash;
	    mystream >> m_data->rd.shmemPmdMapped;
	  }
	else if (it->find("HugePages_Total:", 0) == 0)
	  {
	    std::stringstream mystream;
	    std::string       trash;
	    mystream << *it;
	    mystream >> trash;
	    mystream >> m_data->rd.hugePagesTotal;
	  }
	else if (it->find("HugePages_Free:", 0) == 0)
	  {
	    std::stringstream mystream;
	    std::string       trash;
	    mystream << *it;
	    mystream >> trash;
	    mystream >> m_data->rd.hugePagesFree;
	  }
	else if (it->find("HugePages_Rsvd:", 0) == 0)
	  {
	    std::stringstream mystream;
	    std::string       trash;
	    mystream << *it;
	    mystream >> trash;
	    mystream >> m_data->rd.hugePagesRsvd;
	  }
	else if (it->find("HugePages_Surp:", 0) == 0)
	  {
	    std::stringstream mystream;
	    std::string       trash;
	    mystream << *it;
	    mystream >> trash;
	    mystream >> m_data->rd.hugePagesSurp;
	  }
	else if (it->find("Hugepagesize:", 0) == 0)
	  {
	    std::stringstream mystream;
	    std::string       trash;
	    mystream << *it;
	    mystream >> trash;
	    mystream >> m_data->rd.hugepagesize;
	  }
	else if (it->find("DirectMap4k:", 0) == 0)
	  {
	    std::stringstream mystream;
	    std::string       trash;
	    mystream << *it;
	    mystream >> trash;
	    mystream >> m_data->rd.directMap4k;
	  }
	else if (it->find("DirectMap2M:", 0) == 0)
	  {
	    std::stringstream mystream;
	    std::string       trash;
	    mystream << *it;
	    mystream >> trash;
	    mystream >> m_data->rd.directMap2M;
	  }
	else if (it->find("DirectMap1G:", 0) == 0)
	  {
	    std::stringstream mystream;
	    std::string       trash;
	    mystream << *it;
	    mystream >> trash;
	    mystream >> m_data->rd.directMap1G;
	  }
      }
  }
}
