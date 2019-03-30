#ifndef VARIA_HPP_
#define VARIA_HPP_

#include <string>

#include "script.hpp"
#include "lua.hpp"
#include "python.hpp"
#include "variable.hpp"

namespace varia {
  Script* load_script(const std::string& file);
} // namespace varia

#endif  // VARIA_HPP_
