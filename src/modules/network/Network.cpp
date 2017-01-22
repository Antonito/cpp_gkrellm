#include <fstream>
#include <sstream>
#include <algorithm>
#include "Network.hpp"
#include "UtilsModule.hpp"
#include "Logger.hpp"
#include "HTTPServer.hpp"

namespace Module
{

  Network::NetworkGlobal *Network::m_data = NULL;

  Network::Network()
  {
  }

  Network::~Network()
  {
  }

  void Network::setData(NetworkGlobal *ng)
  {
    m_data = ng;
  }

  std::string Network::networkSerializer()
  {
    std::string json;

    json = "{ \"network\": [";
    for (std::vector<NetworkData>::iterator it = m_data->nd.begin();
         it != m_data->nd.end(); ++it)
      {
	std::stringstream nb;

	if (it != m_data->nd.begin())
	  {
	    json += ", ";
	  }
	json += "{\"name\": \"";
	json += (*it).interface;
	json += "\", \"bytes_rec\": ";
	nb.str("");
	nb << (*it).bytesRecv;
	json += nb.str();
	json += ", \"pkt_rec\": ";
	nb.str("");
	nb << (*it).packetRecv;
	json += nb.str();
	json += ", \"pkt_rec_errs\": ";
	nb.str("");
	nb << (*it).packetRecvErrs;
	json += nb.str();
	json += ", \"pkt_rec_drop\": ";
	nb.str("");
	nb << (*it).packetRecvDrop;
	json += nb.str();
	json += ", \"pkt_rec_fifo\": ";
	nb.str("");
	nb << (*it).packetRecvFifo;
	json += nb.str();
	json += ", \"pkt_rec_frame\": ";
	nb.str("");
	nb << (*it).packetRecvFrame;
	json += nb.str();
	json += ", \"pkt_rec_compressed\": ";
	nb.str("");
	nb << (*it).packetRecvCompressed;
	json += nb.str();
	json += ", \"pkt_rec_multicast\": ";
	nb.str("");
	nb << (*it).packetRecvMulticast;
	json += nb.str();
	json += ", \"bytes_sent\": ";
	nb.str("");
	nb << (*it).bytesSend;
	json += nb.str();
	json += ", \"pkt_sent\": ";
	nb.str("");
	nb << (*it).packetSend;
	json += nb.str();
	json += ", \"pkt_sent_errs\": ";
	nb.str("");
	nb << (*it).packetSendErrs;
	json += nb.str();
	json += ", \"pkt_sent_drop\": ";
	nb.str("");
	nb << (*it).packetSendDrop;
	json += nb.str();
	json += ", \"pkt_sent_fifo\": ";
	nb.str("");
	nb << (*it).packetSendFifo;
	json += nb.str();
	json += ", \"pkt_sent_colls\": ";
	nb.str("");
	nb << (*it).packetSendColls;
	json += nb.str();
	json += ", \"pkt_sent_carrier\": ";
	nb.str("");
	nb << (*it).packetSendCarrier;
	json += nb.str();
	json += ", \"pkt_sent_compressed\": ";
	nb.str("");
	nb << (*it).packetSendCompressed;
	json += nb.str();
	json += "}";
      }
    json += "]}";
    return (json);
  }

  void Network::setRoute()
  {
    Logger::Instance().log(Logger::Info, "Added routes for Network Module.");
    HTTPServer::addRoute("/network", static_cast<HTTPServer::serializerToJSON>(
                                         &Network::networkSerializer));
  }

  void Network::parse()
  {
    std::ifstream            ff;
    std::stringstream        mystream;
    std::vector<std::string> m_split;

    m_data->nd.clear();
    ff.open("/proc/net/dev", std::ios_base::in);
    if (!ff.good())
      {
	Logger::Instance().log(Logger::Error, "CANNOT READ NETWORK Info");
	return;
      }
    mystream << ff.rdbuf();
    ff.close();
    m_split = split(mystream.str(), '\n');

    NetworkData nd;
    for (std::vector<std::string>::iterator it = m_split.begin();
         it != m_split.end(); ++it)
      {
	if (it->find(":") != std::string::npos)
	  {
	    std::stringstream interfaceInfo;

	    interfaceInfo << it->substr(it->find(":") + 1);
	    nd.interface = it->substr(0, it->find(":"));
	    nd.interface.erase(std::remove_if(nd.interface.begin(),
	                                      nd.interface.end(), isspace),
	                       nd.interface.end());
	    interfaceInfo >> nd.bytesRecv;
	    interfaceInfo >> nd.packetRecv;
	    interfaceInfo >> nd.packetRecvErrs;
	    interfaceInfo >> nd.packetRecvDrop;
	    interfaceInfo >> nd.packetRecvFifo;
	    interfaceInfo >> nd.packetRecvFrame;
	    interfaceInfo >> nd.packetRecvCompressed;
	    interfaceInfo >> nd.packetRecvMulticast;
	    interfaceInfo >> nd.bytesSend;
	    interfaceInfo >> nd.packetSend;
	    interfaceInfo >> nd.packetSendErrs;
	    interfaceInfo >> nd.packetSendDrop;
	    interfaceInfo >> nd.packetSendFifo;
	    interfaceInfo >> nd.packetSendColls;
	    interfaceInfo >> nd.packetSendCarrier;
	    interfaceInfo >> nd.packetSendCompressed;
	    m_data->nd.push_back(nd);
	  }
      }
  }
}
