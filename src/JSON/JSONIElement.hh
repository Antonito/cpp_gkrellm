#ifndef JSONIELEMENT_HH_
#define JSONIELEMENT_HH_

namespace JSON
{
  class IElement
  {
  public:
    virtual ~IElement(){};

    virtual std::string str(std::string const &c = "\"") const = 0;
    virtual IElement &operator[](size_t index) = 0;
    virtual IElement &operator[](std::string const &name) = 0;
  };
}
#endif // !JSONIELEMENT_HH_