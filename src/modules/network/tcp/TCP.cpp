#include <fstream>
#include <sstream>
#include "TCP.hpp"
#include "Logger.hpp"

namespace Module
{

  TCP::TCPGlobal *TCP::m_data = NULL;

  void split(const std::string &s, char delim, std::vector<std::string> &elems)
  {
    std::stringstream ss;
    ss.str(s);
    std::string item;
    while (std::getline(ss, item, delim))
      {
	elems.push_back(item);
      }
  }

  std::vector<std::string> split(const std::string &s, char delim)
  {
    std::vector<std::string> elems;
    split(s, delim, elems);
    return elems;
  }
  TCP::TCP()
  {
  }
  TCP::~TCP()
  {
  }

  void TCP::setData(TCPGlobal *ng)
  {
    m_data = ng;
  }

  std::string TCP::networkSerializer()
  {
  }

  void TCP::setRoute()
  {
    Logger::Instance().log(Logger::LogLevel::INFO,
                           "Added routes for TCP Module.");
    HTTPServer::addRoute("/network", static_cast<HTTPServer::serializerToJSON>(
                                         &TCP::networkSerializer));
  }

  void TCP::parse()
  {
    std::ifstream            ff;
    std::stringstream        mystream;
    std::vector<std::string> m_split;

    m_data->nd.clear();
    ff.open("/proc/net/dev", std::ios_base::in);
    if (!ff.good())
      {
	Logger::Instance().log(Logger::LogLevel::ERROR,
	                       "Added routes for CPU Module.");
	return;
      }
    mystream << ff.rdbuf();
    ff.close();
    m_split = split(mystream.str(), '\n');

    TCPData nd;
    for (std::vector<std::string>::iterator it = m_split.begin();
         it != m_split.end(); ++it)
      {
	if (it->find(":") != std::string::npos)
	  {
	    std::stringstream interfaceInfo;
	    size_t            trash;
	    interfaceInfo << it->substr(it->find(":") + 1);
	    nb.interface = it->substr(0, it->find(":"));
	    interfaceInfo >> trash;
	    interfaceInfo >> nd.packetRecv;
	    interfaceInfo >> trash;
	    interfaceInfo >> nd.packetRecvDrop;
	    interfaceInfo >> trash;
	    interfaceInfo >> trash;
	    interfaceInfo >> trash;
	    interfaceInfo >> trash;
	    interfaceInfo >> trash;
	    interfaceInfo >> nd.packetSend;
	    interfaceInfo >> trash;
	    interfaceInfo >> nd.packetSendDrop;
	    m_data->nd.push_back(nd);
	  }
      }
    for (std::vector<TCPData>::iterator it = m_data->nd.begin();
         it != m_data->nd.end(); ++it)
      {
	std::cout << "Interface : " << it->interface << std::endl;
	std::cout << "PacketRecv : " << it->packetRecv << std::endl;
	std::cout << "PacketRecvDrop : " << it->packetRecvDrop << std::endl;
	std::cout << "PacketSend : " << it->packetSend << std::endl;
	std::cout << "PacketSendDrop : " << it->packetSendDrop << std::endl;
      }
  }
}