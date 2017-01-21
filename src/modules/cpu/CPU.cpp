#include <fstream>
#include <sstream>
#include <string>
#include <sstream>
#include <vector>
#include <iostream>
#include <cassert>
#include "CPU.hpp"
#include "Logger.hpp"
#include "UtilsModule.hpp"
#include "HTTPServer.hpp"

namespace Module
{
  namespace Processor
  {
    CPU::CPUGlobal *CPU::m_data = NULL;

    CPU::CPU()
    {
    }

    CPU::~CPU()
    {
    }

    void CPU::setData(CPUGlobal *cpu)
    {
      m_data = cpu;
    }

    std::string CPU::cpuSerializer()
    {
      std::string       json;
      std::stringstream nb;
      size_t            nbCore = m_data->coresData.size();

      json = "{ \"name\": \"" + m_data->name + "\", \"nb_core\": ";
      nb << nbCore;
      json += nb.str();
      json += ", \"core\": [";
      for (size_t i = 0; i < nbCore; ++i)
	{
	  if (i)
	    {
	      json += ", ";
	    }
	  json += "{";
	  json += "\"name\": \"";
	  json += m_data->coresData[i].coreName;
	  json += "\", \"user\": ";
	  nb.str("");
	  nb << m_data->coresData[i].user;
	  json += nb.str();
	  json += ", \"nice\": ";
	  nb.str("");
	  nb << m_data->coresData[i].nice;
	  json += nb.str();
	  json += ", \"system\": ";
	  nb.str("");
	  nb << m_data->coresData[i].system;
	  json += nb.str();
	  json += ", \"idle\": ";
	  nb.str("");
	  nb << m_data->coresData[i].idle;
	  json += nb.str();
	  json += ", \"iowait\": ";
	  nb.str("");
	  nb << m_data->coresData[i].iowait;
	  json += nb.str();
	  json += ", \"irq\": ";
	  nb.str("");
	  nb << m_data->coresData[i].irq;
	  json += nb.str();
	  json += ", \"softirq\": ";
	  nb.str("");
	  nb << m_data->coresData[i].softirq;
	  json += nb.str();
	  json += ", \"freq_mhz\": ";
	  nb.str("");
	  nb << m_data->coresData[i].curFreq;
	  json += nb.str();
	  json += "}";
	}
      json += "]}";
      return (json);
    }

    void CPU::setRoute()
    {
      Logger::Instance().log(Logger::INFO, "Added routes for CPU Module.");
      HTTPServer::addRoute("/cpu", static_cast<HTTPServer::serializerToJSON>(
                                       &CPU::cpuSerializer));
    }

    void CPU::parse()
    {
      std::ifstream            ff;
      std::stringstream        strbuf;
      std::string              strData;
      std::vector<std::string> m_split;

      assert(m_data != NULL);
      m_data->coresData.clear();
      ff.open("/proc/stat", std::ios_base::in);
      if (!ff.good())
	{
	  // Logger::Instance().log(Logger::ERROR, "cannot read cores info");
	  return;
	}
      strbuf << ff.rdbuf();
      strData = strbuf.str();

      m_split = split(strData, '\n');

      CPUData info_proc;
      for (std::vector<std::string>::iterator it = m_split.begin();
           it != m_split.end(); ++it)
	{
	  if (it->find("cpu", 0) == 0)
	    {
	      std::stringstream core_info;
	      core_info << *it;
	      std::string tmp;
	      core_info >> info_proc.coreName;
	      core_info >> info_proc.user;
	      core_info >> info_proc.nice;
	      core_info >> info_proc.system;
	      core_info >> info_proc.idle;
	      core_info >> info_proc.iowait;
	      core_info >> info_proc.irq;
	      core_info >> info_proc.softirq;
	      m_data->coresData.push_back(info_proc);
	    }
	}
      ff.close();
      ff.open("/proc/cpuinfo", std::ios_base::in);
      if (!ff.good())
	{
	  // Logger::Instance().log(Logger::ERROR, "cannot read cpu info :(");
	  return;
	}
      strbuf.str("");
      strbuf << ff.rdbuf();
      strData = strbuf.str();

      m_split = split(strData, '\n');
      // /proc/cpuinfo
      unsigned int nb_cores = 0;
      for (std::vector<std::string>::iterator it = m_split.begin();
           it != m_split.end(); ++it)
	{
	  if (it->find("model name", 0) == 0)
	    {
	      size_t pos = it->find(":", 0);
	      m_data->name = it->substr(pos + 2);
	    }
	  if (it->find("cpu MHz", 0) == 0)
	    {
	      std::stringstream streamFreq;
	      size_t            pos = it->find(":", 0);
	      streamFreq << it->substr(pos + 2);
	      streamFreq >> m_data->coresData[nb_cores].curFreq;
	      nb_cores++;
	    }
	  /*if (it->find("cache size", 0) == 0)
	    {
	      tmp_proco << *it << "\n";
	      std::cout << "get actual core frequency" << std::endl;
	    }
	  if (it->find("bogomips", 0) == 0)
	    {
	      tmp_proco << *it << "\n";
	      std::cout << "get max speed of the core" << std::endl;
	    }
	  if (*it == "")
	    {
	      std::stringstream core_info;
	      core_info << "Core: " << nb_cores << "\n";
	      // core_info << tmp_proco.str();
	      std::cout << "get a processor" << std::endl;
	      m_data.push_back(core_info.str());
	      tmp_proco.str("");
	      nb_cores += 1;
	    }*/
	}
      ff.close();
    }
  }
}
