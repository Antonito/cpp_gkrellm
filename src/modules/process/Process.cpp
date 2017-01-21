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
    return ("");
  }

  void Process::setRoute()
  {
    Logger::Instance().log(Logger::INFO, "Added routes for Process module");
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
	while ((ent = readdir(dir)) != NULL)
	  {
	    if (ent->d_type == DT_DIR)
	      {
		ProcessData pd;
		ff << ent->d_name;
		ff >> pid;
		if (pid == 0) // check if it is a process directory
		  continue;
		pd.pid = pid;
		file_path = root_path + ent->d_name + "/cmdline";
		ff.open(file_path.c_str(), std::ios_base::in);
		if (!ff.good())
		  continue;
		ff.str("");
		ff << file_path.rdbuf();
		if (ff.str() == "")
		  continue;
		ff >> pd.cmdline;
		m_data->pd.push_back(pd);
	      }
	  }
	closedir(dir);
      }
    else
      {
	Logger::Instance().log(Logger::ERROR,
	                       "Cannot open /proc, WTF ? is this blinux ?");
      }
  }
}
