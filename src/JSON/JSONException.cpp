#include "JSONException.hh"

namespace JSON
{
  JSONException::JSONException(std::string const &message) : m_message(message)
  {
  }

  JSONException::~JSONException() throw()
  {
  }

  const char *JSONException::what() const throw()
  {
    return (m_message.c_str());
  }
}