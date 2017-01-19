#ifndef JSONEXCEPTION_HH_
#define JSONEXCEPTION_HH_

#include <stdexcept>
#include <string>

namespace JSON
{
  class JSONException : public std::exception
  {
  public:
    JSONException(std::string const &message);
    virtual ~JSONException() throw();

    virtual const char *what() const throw();

  private:
    std::string m_message;
  };
}
#endif // !JSONEXCEPTION_HH_