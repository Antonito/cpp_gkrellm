#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include "RAM.hpp"
#include "UtilsModule.hpp"
#include "Logger.hpp"

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
  }

  void RAM::setRoute()
  {
    Loggger::Instance().log(Logger::LogLevel::INFO,
                            "Added routes for Memory module");
    HTTPServer::addRoute("/mem", static_cast<HTTPServer::SerializerToJSON>(
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
	Loggger::Instance().log(Logger::LogLevel::ERROR,
	                        "Cannot read memory info");
	return;
      }
    strbuf << ff.rdbuf();
    m_split = split(strbuf.str(), '\n');

    RAMGlobal data;

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
