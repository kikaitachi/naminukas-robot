#ifndef NAMINUKAS_BRAIN_LOGGER_H_
#define NAMINUKAS_BRAIN_LOGGER_H_

#include <string>

namespace logger {

  /**
   * Log debug message.
   */
  void debug(std::string format, ...);

  /**
   * Log warning message.
   */
  void warn(std::string format, ...);

  /**
   * Log error message.
   */
  void error(std::string format, ...);

  /**
   * Log information message.
   */
  void info(std::string format, ...);

  /**
   * Log error provided by errno from last system call.
   */
  void last(std::string format, ...);
}

#endif  // NAMINUKAS_BRAIN_LOGGER_H_
