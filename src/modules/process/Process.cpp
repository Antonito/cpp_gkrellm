#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <dirent.h>
#include "Process.hpp"
#include "UtilsModule.hpp"
#include "Logger.hpp"
#include "HTTPServer.hpp"

namespace Module
{
  Process::ProcessGlobal *Process::m_data = NULL;

  Process::Process()
  {
  }

  Process::~Process()
  {
  }

  void Process::setData(ProcessGlobal *rg)
  {
    m_data = rg;
  }

  std::string Process::processSerializer()
  {
    std::string json = "{ \"process\": [";
    for (std::vector<ProcessData>::iterator it = m_data->pd.begin();
         it != m_data->pd.end(); ++it)
      {
	std::stringstream nb;
	if (it != m_data->pd.begin())
	  {
	    json += ", ";
	  }
	json += "{ \"pid\": ";
	nb.str("");
	nb << it->pid;
	json += nb.str();
	json += ", \"user\": \"";
	json += it->user;
	json += "\", \"cmdline\": \"";
	json += it->cmdline;
	json += "\"}";
      }
    json += "]}";
    return (json);
  }

  void Process::setRoute()
  {
    Logger::Instance().log(Logger::Info, "Added routes for Process module");
    HTTPServer::addRoute("/process", static_cast<HTTPServer::serializerToJSON>(
                                         &Process::processSerializer));
  }
  void Process::parse()
  {
    m_data->pd.clear();

    std::string   root_path("/proc/");
    std::string   file_path;
    std::ifstream ff;
    pid_t         pid = 0;

    DIR *          dir;
    struct dirent *ent;
    if ((dir = opendir("/proc/")) != NULL)
      {
	int pointpoint = 0;
	while ((ent = readdir(dir)) != NULL)
	  {
	    pointpoint++;
	    if (pointpoint < 3)
	      continue;
	    if (ent->d_type == DT_DIR)
	      {
		pid = 0;
		ProcessData        pd = {};
		std::string        fileName(ent->d_name);
		std::istringstream ss(fileName);
		ss >> pid;
		ss >> pid;
		if (pid == 0) // check if it is a process directory
		  {
		    continue;
		  }
		pd.pid = pid;
		file_path = root_path + ent->d_name + "/cmdline";
		ff.open(file_path.c_str(), std::ios_base::in);
		if (!ff.good())
		  {
		    continue;
		  }
		std::stringstream mystream;
		getline(ff, pd.cmdline, '\0');
		ff.close();
		if (pd.cmdline == "")
		  {
		    continue;
		  }
		pd.user = "UserLogin";
		m_data->pd.push_back(pd);
	      }
	  }
	closedir(dir);
      }
    else
      {
	Logger::Instance().log(Logger::Error,
	                       "Cannot open /proc, WTF ? is this blinux ?");
      }
  }
}
