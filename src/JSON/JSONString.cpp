#include "JSONString.hh"
#include "JSONException.hh"

JSONString::JSONString() : m_value("")
{
}

JSONString::JSONString(std::string const &str) : m_value(str)
{
}

JSONString::~JSONString()
{
}

std::string JSONString::str(std::string const &c) const
{
  return (c + m_value + c);
}

IJSONElement &JSONString::operator[](size_t)
{
  throw JSONException("Index accessing on JSONString");
}

IJSONElement &JSONString::operator[](std::string const &)
{
  throw JSONException("Property accessing on JSONString");
}

void JSONString::setValue(std::string const &value)
{
  m_value = value;
}