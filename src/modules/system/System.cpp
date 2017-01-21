#include <fstream>
#include <sstream>
#include <unistd.h>
#include "System.hpp"
#include "UtilsModule.hpp"
#include "Logger.hpp"

namespace Module
{

  System::SystemGlobal *System::m_data = NULL;

  System::System()
  {
  }
  System::~System()
  {
  }

  void System::setData(SystemGlobal *ng)
  {
    m_data = ng;
  }

  std::string System::networkSerializer()
  {
  }

  void System::setRoute()
  {
    Logger::Instance().log(Logger::LogLevel::INFO,
                           "Added routes for System Module.");
    HTTPServer::addRoute("/system", static_cast<HTTPServer::serializerToJSON>(
                                        &System::networkSerializer));
  }

  void System::parse()
  {
    std::ifstream     ff;
    std::stringstream mystream;

    // getting hostname
    ff.open("/proc/sys/kernel/hostname", std::ios_base::in);
    if (!ff.good())
      {
	Logger::Instance().log(Logger::LogLevel::ERROR,
	                       "cannot read system module info");
	return;
      }
    mystream << ff.rdbuf();
    m_data->hostname = mystream.str();
    mystream.str("");
    ff.close();

    // getting kernel and OS
    ff.open("/proc/sys/kernel/osrelease", std::ios_base::in);
    if (!ff.good())
      {
	Logger::Instance().log(Logger::LogLevel::ERROR,
	                       "cannot read system module info");
	return;
      }
    mystream << ff.rdbuf();
    m_data->kernel = mystream.str();
    mystream.str("");
    ff.close();

    // getting username
    std::string userName(getlogin());
    m_data->userName = userName;

    // getting uptime
    ff.open("/proc/uptime", std::ios_base::in);
    if (!ff.good())
      {
	Logger::Instance().log(Logger::LogLevel::ERROR,
	                       "cannot read system module info");
	return;
      }
    mystream << ff.rdbuf();
    mystream >> m_data->uptime;
    mystream >> m_data->idletime;
    mystream.str("");
    ff.close();

    // getting load average
    ff.open("/proc/loadavg", std::ios_base::in);
    if (!ff.good())
      {
	Logger::Instance().log(Logger::LogLevel::ERROR,
	                       "cannot read system module info");
	return;
      }
    mystream << ff.rdbuf();
    mystream >> m_data->loadAverage1;
    mystream >> m_data->loadAverage5;
    mystream >> m_data->loadAverage15;
    mystream.str("");
    ff.close();
  }
}
