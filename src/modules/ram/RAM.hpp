#ifndef RAM_HPP_
#define RAM_HPP_

namespace Module
{
  class RAM
  {
  public:
    struct RAMData
    {
      size_t memTotal;
      size_t memFree;
      size_t memeAvailable;
    };
    struct SWAPData
    {
      size_t swapTotal;
      size_t swapFree
    };
    struct RAMGlobal
    {
      RAMData  rd;
      SWAPData sd;
    };
    static std::string ramSerializer();
    RAM();
    virtual ~RAM();
    void setData(RAMGlobal *rg);
    virtual void parse();
    virtual void setRoute();

  private:
    static RAMGlobal *m_data;
  };
}

#endif
