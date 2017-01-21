#ifndef GRAPHICEXCEPTION_HPP_
#define GRAPHICEXCEPTION_HPP_

#include <stdexcept>
#include <string>

class GraphicException : public std::exception
{
public:
  GraphicException(std::string const &message);
  virtual ~GraphicException() throw();

  virtual const char *what() const throw();

private:
  std::string m_message;
};

#endif // !GRAPHICEXCEPTION_HPP_