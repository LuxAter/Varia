#include "varia.hpp"

#include <iostream>

int main(int argc, char* argv[]) {
  varia::Script* script = new varia::Lua("test.lua");
  // varia::Script* script = new varia::Script("test.lua");
  std::cout << script->has("testing") << "::" << script->hasf("testing") << ":"
            << script->hass("testing") << ":" << script->hasi("testing") << ":"
            << script->hasd("testing") << "\n";
  std::cout << script->hasvi("testv") << "\n";
  std::cout << script->geti("testi") << "\n";
  std::cout << script->gets("testing") << "\n";
  auto iv = script->getvs("testv");
  for(auto& it : iv){
    std::cout << it << ",";
  }
  std::cout << '\n';
  std::cout << script->call("test", 7) << '\n';
  delete script;
  return 0;
}
