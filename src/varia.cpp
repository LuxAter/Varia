#include "varia.hpp"

#include <string>

#include "lua.hpp"
#include "python.hpp"
#include "script.hpp"

varia::Script* varia::load_script(const std::string& file) {
  if (file.compare(file.find_last_of('.'), 3, ".py") == 0) {
#ifdef VARIA_PYTHON
    return new varia::Python(file.substr(0, file.find_last_of('.')));
#else
    return new varia::Script();
#endif
  } else if (file.compare(file.find_last_of('.'), 4, ".lua") == 0) {
#ifdef VARIA_LUA
    return new varia::Lua(file);
#else
    return new varia::Script();
#endif
  }
  return new varia::Script();
}
