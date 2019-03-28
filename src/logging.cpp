#include "logging.hpp"

#include <iostream>
#include <string>

void varia::logging::console_callback(const std::string& file,
                                      const std::string& msg) {
  std::cout << "\033[91;1m[ERROR](" << file << ") " << msg << "\033[0m\n";
}
