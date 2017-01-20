#include <fstream>
#include <sstream>
#include <string>
#include <sstream>
#include <vector>
#include <iostream>
#include "CPU.hh"

namespace Module
{
  namespace Processor
  {
    void split(const std::string &s, char delim,
               std::vector<std::string> &elems)
    {
      std::stringstream ss;
      ss.str(s);
      std::string item;
      while (std::getline(ss, item, delim))
	{
	  elems.push_back(item);
	}
    }

    std::vector<std::string> split(const std::string &s, char delim)
    {
      std::vector<std::string> elems;
      split(s, delim, elems);
      return elems;
    }
    // CLASS HERE
    CPU::CPU()
    {
    }

    CPU::~CPU()
    {
    }

    void CPU::setRoute()
    {
    }

    void CPU::parse()
    {
      std::ifstream            ff;
      std::stringstream        strbuf;
      std::string              strData;
      std::vector<std::string> m_split;

      ff.open("/proc/stat", std::ios_base::in);
      if (!ff.good())
	{
	  // Logger::Instance().log(Logger::ERROR, "cannot read cores info");
	  return;
	}
      strbuf << ff.rdbuf();
      strData = strbuf.str();

      m_split = split(strData, '\n');

      CpuData info_proc;
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
	      m_data.coresData.push_back(info_proc);
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
      // unsigned int nb_cores = 0;
      for (std::vector<std::string>::iterator it = m_split.begin();
           it != m_split.end(); ++it)
	{
	  if (it->find("model name", 0) == 0)
	    {
	      size_t pos = it->find(":", 0);
	      m_data.name = it->substr(pos + 2);
	    }
	  /*if (it->find("cpu MHz", 0) == 0)
	    {
	      tmp_proco << *it << "\n";
	      std::cout << "get actual core frequency" << std::endl;
	    }
	  if (it->find("cache size", 0) == 0)
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

      return;
      std::cout << m_data.name << std::endl;
      for (std::vector<CpuData>::iterator it = m_data.coresData.begin();
           it != m_data.coresData.end(); ++it)
	{
	  std::cout << it->coreName << std::endl;
	  std::cout << "User: " << it->user << std::endl;
	  std::cout << "Nice: " << it->nice << std::endl;
	  std::cout << "System: " << it->system << std::endl;
	  std::cout << "Idle: " << it->idle << std::endl;
	  std::cout << "iowait: " << it->iowait << std::endl;
	  std::cout << "Irq: " << it->irq << std::endl;
	  std::cout << "SoftIrq: " << it->softirq << std::endl;
	  std::cout << std::endl;
	}
    }
  }
}
