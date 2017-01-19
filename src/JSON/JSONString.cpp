#include "JSONString.hh"
#include "JSONException.hh"

namespace JSON
{
  String::String() : m_value("")
  {
  }

  String::String(std::string const &str) : m_value(str)
  {
  }

  String::~String()
  {
  }

  std::string String::str(std::string const &c) const
  {
    return (c + m_value + c);
  }

  IElement &String::operator[](size_t)
  {
    throw JSONException("Index accessing on JSON::String");
  }

  IElement &String::operator[](std::string const &)
  {
    throw JSONException("Property accessing on JSON::String");
  }

  void String::setValue(std::string const &value)
  {
    m_value = value;
  }
}