#ifndef JSONARRAY_HH_
#define JSONARRAY_HH_

#include <string>
#include <vector>
#include "IJSONElement.hh"

class JSONArray : public IJSONElement
{
public:
  JSONArray();
  virtual ~JSONArray();

  virtual std::string str(std::string const &c = "\"") const;
  virtual IJSONElement &operator[](size_t index);
  virtual IJSONElement &operator[](std::string const &name);
  void push(IJSONElement *elem);
  void pop();
  void erase(size_t index);

private:
  std::vector<IJSONElement *> m_values;
};

#endif // !JSONARRAY_HH_