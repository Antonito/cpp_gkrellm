#ifndef JSONSTRING_HH_
#define JSONSTRING_HH_

#include <string>
#include "IJSONElement.hh"

class JSONString : public IJSONElement
{
public:
  JSONString();
  JSONString(std::string const &str);
  virtual ~JSONString();

  virtual std::string str(std::string const &c = "\"") const;
  virtual IJSONElement &operator[](size_t index);
  virtual IJSONElement &operator[](std::string const &prop);
  void setValue(std::string const &val);

private:
  std::string m_value;
};

#endif // !JSONSTRING_HH_