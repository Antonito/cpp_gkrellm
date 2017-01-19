#include <iterator>
#include "JSONException.hh"
#include "JSONArray.hh"

typedef std::vector<IJSONElement *>::const_iterator it_type;

JSONArray::JSONArray()
{
}

JSONArray::~JSONArray()
{
  for (it_type it = m_values.begin(); it != m_values.end(); it++)
    delete *it;
}

std::string JSONArray::str(std::string const &c) const
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

IJSONElement &JSONArray::operator[](size_t index)
{
  return (*m_values[index]);
}

IJSONElement &JSONArray::operator[](std::string const &)
{
  throw JSONException("Property accessing on JSONArray");
}

void JSONArray::push(IJSONElement *elem)
{
  m_values.push_back(elem);
}

void JSONArray::pop()
{
  return (m_values.pop_back());
}

void JSONArray::erase(size_t index)
{
  if (index < m_values.size())
    delete m_values[index];
  m_values.erase(m_values.begin() + index);
}