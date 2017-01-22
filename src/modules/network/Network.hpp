#ifndef NETWORK_HPP_
#define NETWORK_HPP_

#include <vector>
#include <string>
#include "IModuleMonitor.hpp"

namespace Module
{
  class Network : public IModuleMonitor
  {
  public:
    struct NetworkData
    {
      std::string interface;
      size_t      bytesRecv;
      size_t      packetRecv;
      size_t      packetRecvErrs;
      size_t      packetRecvDrop;
      size_t      packetRecvFifo;
      size_t      packetRecvFrame;
      size_t      packetRecvCompressed;
      size_t      packetRecvMulticast;
      size_t      bytesSend;
      size_t      packetSend;
      size_t      packetSendErrs;
      size_t      packetSendDrop;
      size_t      packetSendFifo;
      size_t      packetSendColls;
      size_t      packetSendCarrier;
      size_t      packetSendCompressed;
    };
    struct NetworkGlobal
    {
      std::vector<NetworkData> nd;
    };
    Network();
    virtual ~Network();

    void setData(NetworkGlobal *net);
    virtual void parse();
    virtual void setRoute();

  private:
    static NetworkGlobal *m_data;
    static std::string    networkSerializer();
  };
}

#endif
