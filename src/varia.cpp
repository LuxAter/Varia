#include "varia.hpp"

#include <string>

#include "lua.hpp"
#include "python.hpp"
#include "script.hpp"

varia::Script* varia::load_script(const std::string& file) {
  if (file.compare(file.find_last_of('.'), 3, ".py") == 0) {
    return new varia::Python(file.substr(0, file.find_last_of('.')));
  } else if (file.compare(file.find_last_of('.'), 4, ".lua") == 0) {
    return new varia::Lua(file);
  }
}
