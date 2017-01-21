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
    Logger::Instance().log(Logger::INFO, "Added routes for Memory module");
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
	Logger::Instance().log(Logger::ERROR, "Cannot read memory info");
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
      }
  }
};
