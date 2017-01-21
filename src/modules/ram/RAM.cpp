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
    json += " }, \"swap\": { \"swap_total\": ";
    nb.str("");
    nb << m_data->sd.swapTotal;
    json += nb.str();
    json += ", \"swap_free\": ";
    nb.str("");
    nb << m_data->sd.swapFree;
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
      }
  }
}
