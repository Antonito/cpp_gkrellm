#include <iterator>
#include "JSONObject.hh"
#include "JSONException.hh"

namespace JSON
{
  typedef std::map<std::string, IElement *>::const_iterator it_type;

  Object::Object()
  {
  }

  Object::~Object()
  {
    for (it_type it = m_properties.begin(); it != m_properties.end(); it++)
      {
	delete it->second;
      }
  }

  std::string Object::str(std::string const &c) const
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

  IElement &Object::operator[](size_t)
  {
    throw JSONException("Index accessing on JSON::Object");
  }

  IElement &Object::operator[](std::string const &prop)
  {
    if (m_properties.find(prop) == m_properties.end())
      throw JSONException("No such property");
    return (*m_properties[prop]);
  }

  void Object::addProperty(std::string const &prop, IElement *elem)
  {
    if (m_properties.find(prop) != m_properties.end())
      delete m_properties[prop];
    m_properties[prop] = elem;
  }

  void Object::removeProperty(std::string const &prop)
  {
    if (m_properties.find(prop) != m_properties.end())
      {
	IElement *tmp = m_properties[prop];

	m_properties.erase(prop);
	delete tmp;
      }
  }

  size_t Object::size() const
  {
	  return (m_properties.size());
  }
}