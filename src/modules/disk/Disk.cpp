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
    std::string json = "{ \"disks\": [";
    for (std::vector<DiskData>::iterator it = m_data->rd.begin();
         it != m_data->rd.end(); ++it)
      {
	if (it != m_data->rd.begin())
	  {
	    json += ", ";
	  }
	json += "{\"name\": \"";
	json += it->diskName;
	json += "\", \"partitons\": [";
	for (std::vector<DiskPartition>::iterator itb = it->dp.begin();
	     itb != it->dp.end(); ++itb)
	  {
	    std::stringstream stream;

	    if (itb != it->dp.begin())
	      {
		json += ", ";
	      }
	    stream << "{\"major\": " << itb->majorNumber
	           << ", \"minor\": " << itb->minorNumber
	           << ", \"device_name\": \"" << itb->deviceName
	           << "\", \"read_success\": " << itb->readsSuccess
	           << ", \"read_merged\": " << itb->readsMerged
	           << ", \"sectors_read\": " << itb->sectorsRead
	           << ", \"time_spent_reading\": " << itb->timeSpentReadingMS
	           << ", \"write_success\": " << itb->writesSuccess
	           << ", \"write_merged\": " << itb->writesMerged
	           << ", \"sectors_written\": " << itb->sectorsWritten
	           << ", \"io_cur\": " << itb->ioCur
	           << ", \"time_spent_ioms\": " << itb->timeSpentIOMS
	           << ", \"write_success\": " << itb->writesSuccess;
	    json += stream.str();
	    json += "}";
	  }
	json += "]}";
      }
    json += "]}";
    return (json);
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

    DiskData disk;
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
	if (it == m_split.begin())
	  {
	    disk.diskName = dp.deviceName;
	  }
	if (dp.deviceName.find(disk.diskName, 0) == 0)
	  {
	    disk.dp.push_back(dp);
	  }
	else
	  {
	    m_data->rd.push_back(disk);
	    disk.diskName = dp.deviceName;
	    disk.dp.clear();
	  }
	if (it == m_split.end() - 1)
	  {
	    m_data->rd.push_back(disk);
	    disk.diskName = dp.deviceName;
	    disk.dp.clear();
	  }
      }
  }
}
