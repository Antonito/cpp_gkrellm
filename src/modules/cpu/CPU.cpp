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

    CPU::CPUData::CPUData()
        : coreName(""), user(0), nice(0), system(0), idle(0), iowait(0),
          irq(0), softirq(0), curFreq(0), cachesize(""), cacheAlign(0),
          apicid(0), initialApicid(0), cpuFamily(0), cpuModel(0)
    {
    }

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
      json += ", \"temp\": ";
      nb.str("");
      nb << m_data->temp;
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
	  json += ", \"apicid\": ";
	  nb.str("");
	  nb << m_data->coresData[i].apicid;
	  json += nb.str();
	  json += ", \"initial_apicid\": ";
	  nb.str("");
	  nb << m_data->coresData[i].initialApicid;
	  json += nb.str();
	  json += ", \"cpu_family\": ";
	  nb.str("");
	  nb << m_data->coresData[i].cpuFamily;
	  json += nb.str();
	  json += ", \"cpu_model\": ";
	  nb.str("");
	  nb << m_data->coresData[i].cpuModel;
	  json += nb.str();
	  json += ", \"cache_size\": \"";
	  json += m_data->coresData[i].cachesize;
	  json += "\", \"cache_align\": ";
	  nb.str("");
	  nb << m_data->coresData[i].cacheAlign;
	  json += nb.str();
	  json += "}";
	}
      json += "]}";
      return (json);
    }

    void CPU::setRoute()
    {
      Logger::Instance().log(Logger::Info, "Added routes for CPU Module.");
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
	  // Logger::Instance().log(Logger::Error, "cannot read cores info");
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
      ff.open("/sys/class/thermal/thermal_zone0/temp", std::ios_base::in);
      if (!ff.good())
	{
	  Logger::Instance().log(Logger::Error, "cannot read cpu module info");
	  return;
	}
      strbuf.str("");
      strbuf << ff.rdbuf();
      strbuf >> m_data->temp;
      ff.close();
      ff.open("/proc/cpuinfo", std::ios_base::in);
      if (!ff.good())
	{
	  // Logger::Instance().log(Logger::Error, "cannot read cpu info :(");
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
	  else if (it->find("cpu MHz", 0) == 0)
	    {
	      std::stringstream streamFreq;
	      size_t            pos = it->find(":", 0);
	      streamFreq << it->substr(pos + 2);
	      streamFreq >> m_data->coresData[nb_cores].curFreq;
	      nb_cores++;
	    }
	  else if (it->find("cache size", 0) == 0)
	    {
	      size_t pos = it->find(":", 0);
	      m_data->coresData[nb_cores].cachesize = it->substr(pos + 2);
	    }
	  else if (it->find("cache_alignment", 0) == 0)
	    {
	      std::stringstream streamFreq;
	      size_t            pos = it->find(":", 0);
	      streamFreq << it->substr(pos + 2);
	      streamFreq >> m_data->coresData[nb_cores].cacheAlign;
	    }
	  else if (it->find("apicid", 0) == 0)
	    {
	      std::stringstream streamFreq;
	      size_t            pos = it->find(":", 0);
	      streamFreq << it->substr(pos + 2);
	      streamFreq >> m_data->coresData[nb_cores].apicid;
	    }
	  else if (it->find("initial apicid", 0) == 0)
	    {
	      std::stringstream streamFreq;
	      size_t            pos = it->find(":", 0);
	      streamFreq << it->substr(pos + 2);
	      streamFreq >> m_data->coresData[nb_cores].initialApicid;
	    }
	  else if (it->find("cpu family", 0) == 0)
	    {
	      std::stringstream streamFreq;
	      size_t            pos = it->find(":", 0);
	      streamFreq << it->substr(pos + 2);
	      streamFreq >> m_data->coresData[nb_cores].cpuFamily;
	    }
	  else if (it->find("model", 0) == 0)
	    {
	      std::stringstream streamFreq;
	      size_t            pos = it->find(":", 0);
	      streamFreq << it->substr(pos + 2);
	      streamFreq >> m_data->coresData[nb_cores].cpuModel;
	    }
	}
      ff.close();
    }
  }
}
