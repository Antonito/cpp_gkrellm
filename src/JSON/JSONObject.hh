#ifndef JSONOBJECT_HH_
#define JSONOBJECT_HH_

#include <map>
#include <string>
#include "JSONIElement.hh"

namespace JSON
{
  class Object : public IElement
  {
  public:
    Object();
    virtual ~Object();

    virtual std::string str(std::string const &c = "\"") const;
    virtual IElement &operator[](size_t index);
    virtual IElement &operator[](std::string const &prop);
    void addProperty(std::string const &prop, IElement *elem);
    void removeProperty(std::string const &prop);
    size_t size() const;

  private:
    std::map<std::string, IElement *> m_properties;
  };
}
#endif // !JSONOBJECT_HH_