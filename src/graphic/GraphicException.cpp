#include "GraphicException.hpp"

GraphicException::GraphicException(std::string const &message)
    : m_message(message)
{
}

GraphicException::~GraphicException() throw()
{
}

const char *GraphicException::what() const throw()
{
  return (m_message.c_str());
}