#include "JSONException.hh"

JSONException::JSONException(std::string const &message) : m_message(message)
{
}

JSONException::~JSONException()
{
}

const char *JSONException::what() throw()
{
  return (m_message.c_str());
}