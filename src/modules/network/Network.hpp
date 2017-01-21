#ifndef NETWORK_HPP_
#define NETWORK_HPP_

#include <vector>
#include "IMonitorModule.hpp"

namespace Module
{
  class Network : public IMonitorModule
  {
  public:
    struct NetworkData
    {
      std::string interface;
      size_t      packetRecv;
      size_t      packetRecvDrop;
      size_t      packetSend;
      size_t      packetSendDrop;
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
  };
}

#endif
