#include <iterator>
#include "JSONObject.hh"

typedef std::map<std::string, AJSONElement>::iterator it_type;

JSONObject::JSONObject()
{
}

JSONObject::~JSONObject()
{
}

std::string JSONObject::str() const
{
  std::string s("{");

  for (it_type it = m_properties.begin(); it != m_properties.end(); it++)
    {
      s += "\"" + it->first + "\""; // Key
      s += ":";
      s += it->second.str(); // Value
    }
  s += "}";
  return (s);
}

AJSONElement &operator[](size_t const &index) const
{
  throw JSONException("Index accessing on JSONObject");
}

AJSONElement &operator[](std::string const &prop) const
{
  if (m_properties.find(prop) == m_properties.end())
    throw JSONException("No such property");
  return (m_properties[prop]);
}

void addProperty(std::string const &prop, IJSONElement &elem)
{
  m_properties[prop] = elem;
}

void removeProperty(std::string const &prop)
{
  if (m_properties.find(prop) != m_properties.end())
    m_properties.erase(prop);
}