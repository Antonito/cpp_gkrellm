#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include "Disk.hpp"
#include "UtilsModule.hpp"
#include "Logger.hpp"

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
  std::string Disk::ramSerializer()
  {
  }

  void Disk::setRoute()
  {
    Loggger::Instance().log(Logger::LogLevel::INFO,
                            "Added routes for Disk module");
    HTTPServer::addRoute("/disk", static_cast<HTTPServer::SerializerToJSON>(
                                      &Disk::ramSerializer));
  }
  void Disk::parse()
  {
    std::ifstream            ff;
    std::stringstream        strbuf;
    std::vector<std::string> m_split;

    m_data->rd.clear();
    ff.open("/proc/diskstats", std::ios_base::in);
    if (!ff.good())
      {
	Loggger::Instance().log(Logger::LogLevel::ERROR,
	                        "Cannot read memory info");
	return;
      }
    strbuf << ff.rdbuf();
    m_split = split(strbuf.str(), '\n');

    DiskGlobal data;

    unsigned int nb_disk = 0;
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
	mystream >> dp.sectosRead;
	mystream >> dp.timeSpentReadingMS;
	mystream >> dp.writesSuccess;
	mystream >> dp.writeMerged;
	mystream >> dp.sectorsWritten;
	mystream >> dp.ioCur;
	mystream >> dp.timeSpentIOMS;
	mystream >> dp.wTimeSpentIOMS;
      }
  }
};
