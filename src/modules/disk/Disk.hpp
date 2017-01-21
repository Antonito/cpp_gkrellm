#ifndef DISK_HPP_
#define DISK_HPP_

namespace Module
{
  class Disk
  {
  public:
    struct DiskParition
    {
      size_t      majorNumber;
      size_t      minorNumber;
      std::string deviceName;
      size_t      readsSuccess;
      size_t      readsMerged;
      size_t      sectorsRead;
      size_t      timeSpentReadingMS;
      size_t      writesSuccess;
      size_t      writesMerged;
      size_t      sectorsWritten;
      size_t      timeSpentWrittingMS;
      size_t      ioCur;
      size_t      timeSpentIOMS;
      size_t      wTimeSpentIOMS;
    };
    struct DiskData
    {
      std::string               diskName;
      std::vector<DiskParition> dp;
    };
    struct DiskGlobal
    {
      std::vector<DiskData> rd;
    };
    static std::string ramSerializer();
    Disk();
    virtual ~Disk();
    void setData(DiskGlobal *rg);
    virtual void parse();
    virtual void setRoute();

  private:
    static DiskGlobal *m_data;
  };
}

#endif
