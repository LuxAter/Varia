#include "varia.hpp"

#include <iostream>

int main(int argc, char* argv[]) {
  varia::Script* pyscript = new varia::Python("pyscript");
  varia::Script* luascript = new varia::Lua("luascript.lua");

  std::cout << pyscript->has("func") << "::" << pyscript->hasi("func") << ":"
            << pyscript->hasvi("func") << ":" << pyscript->hasd("func") << ":"
            << pyscript->hasvd("func") << ":" << pyscript->hass("func") << ":"
            << pyscript->hasvs("func") << ":" << pyscript->hasf("func") << "\n";

  std::cout << luascript->has("func") << "::" << luascript->hasi("func") << ":"
            << luascript->hasvi("func") << ":" << luascript->hasd("func") << ":"
            << luascript->hasvd("func") << ":" << luascript->hass("func") << ":"
            << luascript->hasvs("func") << ":" << luascript->hasf("func")
            << "\n";

  std::cout << pyscript->get("func") << ":" << luascript->get("func") << "\n";

  std::cout << pyscript->call("func", 5) << ":" << luascript->call("func", 5)
            << "\n";

  delete pyscript;
  delete luascript;
  return 0;
}
