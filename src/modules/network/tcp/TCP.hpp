#ifndef TCP_HPP_
#define TCP_HPP_

#include <vector>
#include "IMonitorModule.hpp"

namespace Module
{
  class TCP : public IMonitorModule
  {
  public:
    struct TCPData
    {
      std::string interface;
      size_t      packetRecv;
      size_t      packetRecvDrop;
      size_t      packetSend;
      size_t      packetSendDrop;
    };
    struct TCPGlobal
    {
      std::vector<TCPData> nd;
    };
    TCP();
    virtual ~TCP();

    void setData(TCPGlobal *net);
    virtual void parse();
    virtual void setRoute();

  private:
    static TCPGlobal *m_data;
  };
}

#endif
