namespace Module
{
  class IModuleMonitor
  {
  public:
    virtual void parse() = 0;
    virtual void setRoute() = 0;
  };
}
