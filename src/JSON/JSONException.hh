#ifndef JSONEXCEPTION_HH_
#define JSONEXCEPTION_HH_

#include <stdexcept>
#include <string>

class JSONException : public std::exception
{
public:
  JSONException(std::string const &message);
  virtual ~JSONException();

  virtual const char *what() throw();

private:
  std::string m_message;
};

#endif // !JSONEXCEPTION_HH_