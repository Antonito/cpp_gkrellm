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
    Logger::Instance().log(Logger::Info, "Added routes for Process module");
    HTTPServer::addRoute("/process", static_cast<HTTPServer::serializerToJSON>(
                                         &Process::processSerializer));
  }
  void Process::parse()
  {
    m_data->pd.clear();

    std::string       root_path("/proc/");
    std::string       file_path;
    std::ifstream     ff;
    std::stringstream mystream;
    pid_t             pid = 0;

    DIR *          dir;
    struct dirent *ent;
    if ((dir = opendir("/proc/")) != NULL)
      {
	while ((ent = readdir(dir)) != NULL)
	  {
	    if (ent->d_type == DT_DIR)
	      {
		__asm__("int $3");
		pid = 0;
		mystream.str("");
		ProcessData pd = {};
		std::string fileName(ent->d_name);
		mystream << fileName;
		std::cout << "REPERTORY: " << mystream.str() << std::endl;
		mystream >> pid;
		if (pid == 0) // check if it is a process directory
		  {
		    std::cout << "PIDPDIPDIDPIDPIDDPIDPID" << std::endl;
		    continue;
		  }
		pd.pid = pid;
		file_path = root_path + ent->d_name + "/cmdline";
		ff.open(file_path.c_str(), std::ios_base::in);
		if (!ff.good())
		  continue;
		mystream.str("");
		mystream << ff.rdbuf();
		ff.close();
		if (mystream.str() == "")
		  continue;
		mystream >> pd.cmdline;
		pd.user = "";
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
    for (std::vector<ProcessData>::iterator it = m_data->pd.begin();
         it != m_data->pd.end(); ++it)
      {

	std::cout << "PID: " << it->pid << "CMDLINE: " << it->cmdline
	          << std::endl;
      }
  }
}
