#include "Logger.hpp"

Logger Logger::m_instance = Logger();

Logger &Logger::Instance()
{
  return (m_instance);
}

void Logger::setStream(std::ostream &stream)
{
  m_stream = &stream;
}

void Logger::setLogLevel(Logger::LogLevel lvl)
{
  m_level = lvl;
}

Logger::LogLevel Logger::getLogLevel() const
{
  return (m_level);
}

void Logger::log(LogLevel lvl, std::string const &msg)
{
  if (lvl >= m_level)
    {
      _writeLog(msg, lvl);
    }
}

Logger &Logger::operator<<(std::string const &msg)
{
  _writeLog(msg, m_level);
  return (*this);
}

std::ostream &operator<<(std::ostream &stream, Logger const &)
{
  return (stream);
}


// Private methods

// This one writes to the specified stream, thread safe.
void Logger::_writeLog(std::string const &msg, LogLevel lvl)
{
  static std::string _lvl[] = {"DEBUG", "INFO", "WARNING", "ERROR",
                               "CRITICAL"};
  m_mut.lock();
  (*m_stream) << "[" << _lvl[lvl] << "] ";
  (*m_stream) << msg;
  (*m_stream) << std::endl;
  m_mut.unlock();
}

Logger::Logger() : m_level(DEBUG), m_stream(&std::clog)
{
}

Logger::~Logger()
{
}

Logger::Logger(Logger const &)
{
}

Logger &Logger::operator=(Logger const &)
{
  return (*this);
}
