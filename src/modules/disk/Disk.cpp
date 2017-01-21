#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include "Disk.hpp"
#include "UtilsModule.hpp"
#include "Logger.hpp"
#include "HTTPServer.hpp"

namespace Module
{
  Disk::DiskGlobal *Disk::m_data = NULL;

  Disk::Disk()
  {
  }

  Disk::~Disk()
  {
  }

  void Disk::setData(DiskGlobal *rg)
  {
    m_data = rg;
  }
  std::string Disk::diskSerializer()
  {
    return ("");
  }

  void Disk::setRoute()
  {
    Logger::Instance().log(Logger::INFO, "Added routes for Disk module");
    HTTPServer::addRoute("/disk", static_cast<HTTPServer::serializerToJSON>(
                                      &Disk::diskSerializer));
  }

  void Disk::parse()
  {
    std::ifstream            ff;
    std::stringstream        strbuf;
    std::vector<std::string> m_split;
    DiskGlobal               data;

    m_data->rd.clear();
    ff.open("/proc/diskstats", std::ios_base::in);
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
	DiskPartition dp;

	std::stringstream mystream;
	std::string       trash;
	mystream << *it;

	mystream >> dp.majorNumber;
	mystream >> dp.minorNumber;
	mystream >> dp.deviceName;
	mystream >> dp.readsSuccess;
	mystream >> dp.readsMerged;
	mystream >> dp.sectorsRead;
	mystream >> dp.timeSpentReadingMS;
	mystream >> dp.writesSuccess;
	mystream >> dp.writesMerged;
	mystream >> dp.sectorsWritten;
	mystream >> dp.ioCur;
	mystream >> dp.timeSpentIOMS;
	mystream >> dp.wTimeSpentIOMS;
      }
  }
};
