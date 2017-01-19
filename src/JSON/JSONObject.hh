#ifndef JSONOBJECT_HH_
#define JSONOBJECT_HH_

#include <map>
#include <string>
#include "IJSONElement.hh"

class JSONObject : public IJSONElement
{
public:
  JSONObject();
  virtual ~JSONObject();

  virtual std::string str(std::string const &c = "\"") const;
  virtual IJSONElement &operator[](size_t index);
  virtual IJSONElement &operator[](std::string const &prop);
  void addProperty(std::string const &prop, IJSONElement *elem);
  void removeProperty(std::string const &prop);

private:
  std::map<std::string, IJSONElement *> m_properties;
};

#endif // !JSONOBJECT_HH_