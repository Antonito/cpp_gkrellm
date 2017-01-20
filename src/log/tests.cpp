#include <stdio.h>
#include "Logger.hpp"

int	main()
{
  Logger &logger = Logger::Instance();

  logger << "Toto [SHOULD DISPLAY]";
  logger << "Attention, penser a rm ca ! [SHOULD DISPLAY]";
  logger.log(Logger::INFO, "Info ! [SHOULD DISPLAY]");
  logger.log(Logger::CRITICAL, "Critical ![SHOULD DISPLAY]");
  logger.setLogLevel(Logger::ERROR);
  logger << "Error [SHOULD DISPLAY]";
  logger.log(Logger::INFO, "Info ! [SHOULD NOT DISPLAY]");
  return (0);
}
