#include <iterator>
#include "JSONObject.hh"
#include "JSONException.hh"

typedef std::map<std::string, IJSONElement *>::const_iterator it_type;

JSONObject::JSONObject()
{
}

JSONObject::~JSONObject()
{
  for (it_type it = m_properties.begin(); it != m_properties.end(); it++)
    {
      delete it->second;
    }
}

std::string JSONObject::str(std::string const &c) const
{
  std::string s("{");

  for (it_type it = m_properties.begin(); it != m_properties.end(); it++)
    {
      if (it != m_properties.begin())
	s += ",";
      s += c + it->first + c; // Key
      s += ":";
      s += it->second->str(c); // Value
    }
  s += "}";
  return (s);
}

IJSONElement &JSONObject::operator[](size_t)
{
  throw JSONException("Index accessing on JSONObject");
}

IJSONElement &JSONObject::operator[](std::string const &prop)
{
  if (m_properties.find(prop) == m_properties.end())
    throw JSONException("No such property");
  return (*m_properties[prop]);
}

void JSONObject::addProperty(std::string const &prop, IJSONElement *elem)
{
  if (m_properties.find(prop) != m_properties.end())
    delete m_properties[prop];
  m_properties[prop] = elem;
}

void JSONObject::removeProperty(std::string const &prop)
{
  if (m_properties.find(prop) != m_properties.end())
    {
      IJSONElement *tmp = m_properties[prop];

      m_properties.erase(prop);
      delete tmp;
    }
}