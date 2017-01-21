#include <fstream>
#include <sstream>
#include <algorithm>
#include <unistd.h>
#include <ctime>
#include "System.hpp"
#include "UtilsModule.hpp"
#include "Logger.hpp"
#include "HTTPServer.hpp"

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

  std::string System::systemSerializer()
  {
    std::stringstream nb;
    std::string       json;

    json = "{ \"hostname\": \"";
    json += m_data->hostname;
    json += "\", \"username\": \"";
    json += m_data->userName;
    json += "\", \"os\": \"";
    json += m_data->osName;
    json += "\", \"kernel\": \"";
    json += m_data->kernel;
    json += "\", \"date\": \"";
    json += m_data->datetime;
    json += "\", \"uptime\": ";
    nb.str("");
    nb << m_data->uptime;
    json += nb.str();
    json += ", \"idletime\": ";
    nb.str("");
    nb << m_data->idletime;
    json += nb.str();
    json += ", \"loadaverage1\": ";
    nb.str("");
    nb << m_data->loadAverage1;
    json += nb.str();
    json += ", \"loadaverage5\": ";
    nb.str("");
    nb << m_data->loadAverage5;
    json += nb.str();
    json += ", \"loadaverage15\": ";
    nb.str("");
    nb << m_data->loadAverage15;
    json += nb.str();
    json += " }";
    return (json);
  }

  void System::setRoute()
  {
    Logger::Instance().log(Logger::Info, "Added routes for System Module.");
    HTTPServer::addRoute("/system", static_cast<HTTPServer::serializerToJSON>(
                                        &System::systemSerializer));
  }

  void System::parse()
  {
    std::ifstream     ff;
    std::stringstream mystream;

    // getting hostname
    ff.open("/proc/sys/kernel/hostname", std::ios_base::in);
    if (!ff.good())
      {
	Logger::Instance().log(Logger::Error,
	                       "cannot read system module info");
	return;
      }

    mystream << ff.rdbuf();
    m_data->hostname = mystream.str();
    m_data->hostname.erase(std::remove_if(m_data->hostname.begin(),
                                          m_data->hostname.end(), isspace),
                           m_data->hostname.end());
    mystream.str("");
    ff.close();

    // getting kernel
    ff.open("/proc/sys/kernel/osrelease", std::ios_base::in);
    if (!ff.good())
      {
	Logger::Instance().log(Logger::Error,
	                       "cannot read system module info");
	return;
      }
    mystream << ff.rdbuf();
    m_data->kernel = mystream.str();
    m_data->kernel.erase(
        std::remove_if(m_data->kernel.begin(), m_data->kernel.end(), isspace),
        m_data->kernel.end());
    mystream.str("");
    ff.close();

    // getting osName
    ff.open("/proc/version", std::ios_base::in);
    if (!ff.good())
      {
	Logger::Instance().log(Logger::Error,
	                       "cannot read system module info");
	return;
      }
    mystream << ff.rdbuf();
    mystream >> m_data->osName;
    mystream.str("");
    ff.close();

    // getting username
    char *login_check = getlogin();
    if (login_check != NULL)
      {
	std::string userName(getlogin());
	m_data->userName = userName;
      }
    else
      m_data->userName = "";

    // getting date and time
    char      buf[100];
    time_t    now = time(0);
    struct tm tm = *gmtime(&now);

    strftime(buf, sizeof buf, "%a, %d %b %Y %H:%M:%S %Z", &tm);
    std::string datetime(buf);
    m_data->datetime = datetime;

    // getting uptime
    ff.open("/proc/uptime", std::ios_base::in);
    if (!ff.good())
      {
	Logger::Instance().log(Logger::Error,
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
	Logger::Instance().log(Logger::Error,
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
