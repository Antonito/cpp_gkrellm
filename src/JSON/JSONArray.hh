#ifndef JSONARRAY_HH_
#define JSONARRAY_HH_

#include <string>
#include <vector>
#include "JSONIElement.hh"

namespace JSON
{
  class Array : public IElement
  {
  public:
    Array();
    virtual ~Array();

    virtual std::string str(std::string const &c = "\"") const;
    virtual IElement &operator[](size_t index);
    virtual IElement &operator[](std::string const &name);
    void push(IElement *elem);
    void pop();
    void erase(size_t index);
    size_t size() const;

  private:
    std::vector<IElement *> m_values;
  };
}

#endif // !JSONARRAY_HH_