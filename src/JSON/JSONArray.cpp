#include <iterator>
#include "JSONException.hh"
#include "JSONArray.hh"

namespace JSON
{
  typedef std::vector<IElement *>::const_iterator it_type;

  Array::Array()
  {
  }

  Array::~Array()
  {
    for (it_type it = m_values.begin(); it != m_values.end(); it++)
      delete *it;
  }

  std::string Array::str(std::string const &c) const
  {
    std::string s("[");

    for (it_type it = m_values.begin(); it != m_values.end(); it++)
      {
	if (it != m_values.begin())
	  s += ",";
	s += (*it)->str(c);
      }
    s += "]";
    return (s);
  }

  IElement &Array::operator[](size_t index)
  {
    return (*m_values[index]);
  }

  IElement &Array::operator[](std::string const &)
  {
    throw JSONException("Property accessing on JSON::Array");
  }

  void Array::push(IElement *elem)
  {
    m_values.push_back(elem);
  }

  void Array::pop()
  {
    return (m_values.pop_back());
  }

  void Array::erase(size_t index)
  {
    if (index < m_values.size())
      delete m_values[index];
    m_values.erase(m_values.begin() + index);
  }

 size_t Array::size() const
{

	  return (m_values.size());
 }
}