#ifndef JSONSTRING_HH_
#define JSONSTRING_HH_

#include <string>
#include "JSONIElement.hh"

namespace JSON
{
  class String : public IElement
  {
  public:
    String();
    String(std::string const &str);
    virtual ~String();

    virtual std::string str(std::string const &c = "\"") const;
    virtual IElement &operator[](size_t index);
    virtual IElement &operator[](std::string const &prop);
    void setValue(std::string const &val);

  private:
    std::string m_value;
  };
}
#endif // !JSONSTRING_HH_