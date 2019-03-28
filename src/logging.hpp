#ifndef VARIA_LOGGING_HPP_
#define VARIA_LOGGING_HPP_

#include <string>

namespace varia {
namespace logging {
  void console_callback(const std::string& file, const std::string& msg);
}  // namespace logging
}  // namespace varia

#endif  // VARIA_LOGGING_HPP_
