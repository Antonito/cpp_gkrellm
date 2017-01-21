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
    for (std::vector<DiskData>::iterator it = m_data->rd.begin();
         it != m_data->rd.end(); ++it)
      {

	std::cout << "Disk: " << it->diskName << " " << it->diskSize << "Bytes"
	          << std::endl;
	for (std::vector<DiskPartition>::iterator itb = it->dp.begin();
	     itb != it->dp.end(); ++itb)
	  {
	    // TO REMOVE
	    std::cout << itb->majorNumber << " " << itb->minorNumber << " "
	              << itb->deviceName << " " << itb->readsSuccess << " "
	              << itb->readsMerged << " " << itb->sectorsRead << " "
	              << itb->timeSpentReadingMS << " " << itb->writesSuccess
	              << " " << itb->writesMerged << " " << itb->sectorsWritten
	              << " " << itb->ioCur << " " << itb->timeSpentIOMS << " "
	              << itb->writesSuccess << " " << itb->partitionSize
	              << "Bytes" << std::endl;
	  }
	std::cout << std::endl;
      }
  }
}
