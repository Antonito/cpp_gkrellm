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
	std::stringstream stream;

	if (it != m_data->rd.begin())
	  {
	    json += ", ";
	  }
	json += "{\"name\": \"";
	json += it->diskName;
	json += "\", \"disk_size\": ";
	stream.str("");
	stream << it->diskSize;
	json += stream.str();
	json += ", \"partitions\": [";
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
	           << ", \"write_success\": " << itb->writesSuccess
	           << ", \"partition_size\": " << itb->partitionSize;
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
	std::ifstream     partition_file;
	std::stringstream partition_stream;
	std::string       partition_path;
	partition_path =
	    "/sys/block/" + disk.diskName + "/" + dp.deviceName + "/size";
	partition_file.open(partition_path.c_str(), std::ios_base::in);
	if (partition_file.good())
	  {
	    partition_stream << partition_file.rdbuf();
	    partition_file.close();
	    size_t partition_go;
	    partition_stream >> partition_go;
	    dp.partitionSize = partition_go;
	  }
	if (dp.deviceName.find(disk.diskName, 0) == 0)
	  {
	    disk.dp.push_back(dp);
	  }
	if (dp.deviceName.find(disk.diskName, 0) != 0 ||
	    it == m_split.end() - 1)
	  {
	    std::ifstream     size_file;
	    std::stringstream size_stream;
	    std::string       file_path;
	    file_path = "/sys/block/" + disk.diskName + "/size";
	    size_file.open(file_path.c_str(), std::ios_base::in);
	    if (size_file.good())
	      {
		size_stream << size_file.rdbuf();
		size_file.close();
		size_t size_go;
		size_stream >> size_go;
		disk.diskSize = size_go;
		disk.dp[0].partitionSize = size_go;
	      }
	    else
	      disk.diskSize = 0;
	    m_data->rd.push_back(disk);
	    disk.diskName = dp.deviceName;
	    disk.dp.clear();
	  }
      }
  }
}
