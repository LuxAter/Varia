#include "varia.hpp"

#include <iostream>

int main(int argc, char* argv[]) {
  varia::Script* pyscript = varia::load_script("pyscript.py");
  varia::Script* luascript = varia::load_script("luascript.lua");

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

  std::cout << pyscript->vcall("func", 5) << ":" << luascript->vcall("func", 5)
            << "\n";
  auto tmp = pyscript->vfunc<int>("func");
  std::cout << tmp(10) << '\n';


  delete pyscript;
  delete luascript;
  return 0;
}
