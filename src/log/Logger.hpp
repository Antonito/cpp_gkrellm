#ifndef LOGGER_HPP_
#define LOGGER_HPP_

#include <iostream>
#include "Mutex.hpp"

// Singleton
class Logger
{
public:
  enum LogLevel
  {
    Debug = 0,
    Info,
    Warning,
    Error,
    Critical
  };
  static Logger &Instance();

  void setStream(std::ostream &stream);
  void setLogLevel(LogLevel lvl);
  LogLevel getLogLevel() const;

  void log(LogLevel lvl, std::string const &);

  // Log at current level
  Logger &operator<<(std::string const &);

private:
  Logger();
  Logger(Logger const &);
  Logger &operator=(Logger const &);
  ~Logger();
  static Logger m_instance;
  void _writeLog(std::string const &msg, LogLevel lvl);

  LogLevel      m_level;
  std::ostream *m_stream;
  Mutex         m_mut;
};

std::ostream &operator<<(std::ostream &stream, Logger const &);

#endif // !LOGGER_HPP_
