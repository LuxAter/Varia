#include "lua.hpp"

#include <memory>
#include <string>

#include "script.hpp"
#include "variable.hpp"

extern "C" {
#include <lua5.3/lauxlib.h>
#include <lua5.3/lua.h>
#include <lua5.3/lualib.h>
}

varia::Lua::Lua() : Script(), valid_check_(nullptr), state_(nullptr) {}
varia::Lua::Lua(const std::string& file)
    : Script(file), valid_check_(nullptr), state_(nullptr) {
  open_script();
}
varia::Lua::Lua(const Lua& lua)
    : Script(lua), valid_check_(lua.valid_check_), state_(lua.state_) {}

varia::Lua::~Lua() {
  if (valid_check_.use_count() == 1) {
    lua_close(state_);
    valid_check_ = nullptr;
  }
  state_ = nullptr;
  valid_check_ = nullptr;
}

bool varia::Lua::valid() const { return valid_check_.use_count() != 0; }

bool varia::Lua::has(const std::string& val) {
  lua_getglobal(state_, val.c_str());
  bool res = !lua_isnil(state_, -1);
  lua_pop(state_, -1);
  return res;
}
bool varia::Lua::hasi(const std::string& val) {
  lua_getglobal(state_, val.c_str());
  bool res = lua_isnumber(state_, -1);
  lua_pop(state_, -1);
  return res;
}
bool varia::Lua::hasvi(const std::string& val) {
  lua_getglobal(state_, val.c_str());
  if (lua_istable(state_, -1)) {
    lua_pushnil(state_);
    lua_next(state_, -2);
    bool res = lua_isnumber(state_, -1);
    int n = lua_gettop(state_);
    lua_pop(state_, n);
    return res;
  } else {
    lua_pop(state_, -1);
    return false;
  }
}
bool varia::Lua::hasd(const std::string& val) {
  lua_getglobal(state_, val.c_str());
  bool res = lua_isnumber(state_, -1);
  lua_pop(state_, -1);
  return res;
}
bool varia::Lua::hasvd(const std::string& val) {
  lua_getglobal(state_, val.c_str());
  if (lua_istable(state_, -1)) {
    lua_pushnil(state_);
    lua_next(state_, -2);
    bool res = lua_isnumber(state_, -1);
    int n = lua_gettop(state_);
    lua_pop(state_, n);
    return res;
  } else {
    lua_pop(state_, -1);
    return false;
  }
}
bool varia::Lua::hass(const std::string& val) {
  lua_getglobal(state_, val.c_str());
  bool res = lua_isstring(state_, -1);
  lua_pop(state_, -1);
  return res;
}
bool varia::Lua::hasvs(const std::string& val) {
  lua_getglobal(state_, val.c_str());
  if (lua_istable(state_, -1)) {
    lua_pushnil(state_);
    lua_next(state_, -2);
    bool res = lua_isstring(state_, -1);
    int n = lua_gettop(state_);
    lua_pop(state_, n);
    return res;
  } else {
    lua_pop(state_, -1);
    return false;
  }
}
bool varia::Lua::hasf(const std::string& val) {
  lua_getglobal(state_, val.c_str());
  bool res = lua_isfunction(state_, -1);
  lua_pop(state_, -1);
  return res;
}

varia::Var varia::Lua::get(const std::string& val){
  lua_getglobal(state_, val.c_str());
  if (lua_isnil(state_, -1)) {
    return Var();
  } else if (lua_isnumber(state_, -1)) {
    return Var(lua_tonumber(state_, -1));
  } else if (lua_isstring(state_, -1)) {
    return Var(lua_tostring(state_, -1));
  } else if (lua_istable(state_, -1)) {
    lua_pushnil(state_);
    lua_next(state_, -2);
    if (lua_isnumber(state_, -1)) {
      std::vector<double> vec;
      vec.push_back(static_cast<double>(lua_tonumber(state_, -1)));
      lua_pop(state_, 1);
      while (lua_next(state_, -2)) {
        vec.push_back(static_cast<double>(lua_tonumber(state_, -1)));
        lua_pop(state_, 1);
      }
      int n = lua_gettop(state_);
      lua_pop(state_, n);
      return vec;
    } else if (lua_isstring(state_, -1)) {
      std::vector<std::string> vec;
      vec.push_back(std::string(lua_tostring(state_, -1)));
      lua_pop(state_, 1);
      while (lua_next(state_, -2)) {
        vec.push_back(std::string(lua_tostring(state_, -1)));
        lua_pop(state_, 1);
      }
      int n = lua_gettop(state_);
      lua_pop(state_, n);
      return vec;
    } else {
      return Var();
    }
  } else {
    return Var();
  }
}

int varia::Lua::geti(const std::string& val) {
  int res = int();
  lua_getglobal(state_, val.c_str());
  if (lua_isnumber(state_, -1)) {
    res = static_cast<int>(lua_tonumber(state_, -1));
  }
  lua_pop(state_, 1);
  return res;
}
std::vector<int> varia::Lua::getvi(const std::string& val) {
  lua_getglobal(state_, val.c_str());
  std::vector<int> res;
  if (lua_istable(state_, -1)) {
    lua_pushnil(state_);
    while (lua_next(state_, -2)) {
      res.push_back(static_cast<int>(lua_tonumber(state_, -1)));
      lua_pop(state_, 1);
    }
    int n = lua_gettop(state_);
    lua_pop(state_, n);
  }
  return res;
}
double varia::Lua::getd(const std::string& val) {
  double res = double();
  lua_getglobal(state_, val.c_str());
  if (lua_isnumber(state_, -1)) {
    res = static_cast<double>(lua_tonumber(state_, -1));
  }
  lua_pop(state_, 1);
  return res;
}
std::vector<double> varia::Lua::getvd(const std::string& val) {
  lua_getglobal(state_, val.c_str());
  std::vector<double> res;
  if (lua_istable(state_, -1)) {
    lua_pushnil(state_);
    while (lua_next(state_, -2)) {
      res.push_back(static_cast<double>(lua_tonumber(state_, -1)));
      lua_pop(state_, 1);
    }
    int n = lua_gettop(state_);
    lua_pop(state_, n);
  }
  return res;
}
std::string varia::Lua::gets(const std::string& val) {
  std::string res = std::string();
  lua_getglobal(state_, val.c_str());
  if (lua_isstring(state_, -1)) {
    res = std::string(lua_tostring(state_, -1));
  }
  lua_pop(state_, 1);
  return res;
}
std::vector<std::string> varia::Lua::getvs(const std::string& val) {
  lua_getglobal(state_, val.c_str());
  std::vector<std::string> res;
  if (lua_istable(state_, -1)) {
    lua_pushnil(state_);
    while (lua_next(state_, -2)) {
      res.push_back(std::string(lua_tostring(state_, -1)));
      lua_pop(state_, 1);
    }
    int n = lua_gettop(state_);
    lua_pop(state_, n);
  }
  return res;
}

void varia::Lua::open_script() {
  state_ = luaL_newstate();
  luaL_openlibs(state_);
  if (luaL_loadfile(state_, this->file_name_.c_str()) ||
      lua_pcall(state_, 0, 0, 0)) {
    state_ = nullptr;
    this->error("Failed to open script file");
  } else {
    valid_check_ = std::make_shared<int>(1);
  }
}

varia::Var varia::Lua::call_func(const std::string& func,
                                 const std::vector<Var>& args) {
  lua_getglobal(state_, func.c_str());
  if (!lua_isfunction(state_, -1)) {
    return Var();
  }
  for (auto& arg : args) {
    switch (arg.type_) {
      case Var::INT: {
        lua_pushnumber(state_, arg.i);
        break;
      }
      case Var::DOUBLE: {
        lua_pushnumber(state_, arg.d);
        break;
      }
      case Var::STRING: {
        lua_pushstring(state_, arg.s.c_str());
        break;
      }
      case Var::INT_VECTOR: {
        lua_newtable(state_);
        for (std::size_t i = 0; i < arg.vi.size(); ++i) {
          lua_pushnumber(state_, i);
          lua_pushnumber(state_, arg.vi[i]);
          lua_settable(state_, -3);
        }
        break;
      }
      case Var::DOUBLE_VECTOR: {
        lua_newtable(state_);
        for (std::size_t i = 0; i < arg.vd.size(); ++i) {
          lua_pushnumber(state_, i);
          lua_pushnumber(state_, arg.vd[i]);
          lua_settable(state_, -3);
        }
        break;
      }
      case Var::STRING_VECTOR: {
        lua_newtable(state_);
        for (std::size_t i = 0; i < arg.vs.size(); ++i) {
          lua_pushnumber(state_, i);
          lua_pushstring(state_, arg.vs[i].c_str());
          lua_settable(state_, -3);
        }
        break;
      }
      default:
        break;
    }
  }
  lua_call(state_, args.size(), 1);
  if (lua_isnil(state_, -1)) {
    return Var();
  } else if (lua_isnumber(state_, -1)) {
    return Var(lua_tonumber(state_, -1));
  } else if (lua_isstring(state_, -1)) {
    return Var(lua_tostring(state_, -1));
  } else if (lua_istable(state_, -1)) {
    lua_pushnil(state_);
    lua_next(state_, -2);
    if (lua_isnumber(state_, -1)) {
      std::vector<double> vec;
      vec.push_back(static_cast<double>(lua_tonumber(state_, -1)));
      lua_pop(state_, 1);
      while (lua_next(state_, -2)) {
        vec.push_back(static_cast<double>(lua_tonumber(state_, -1)));
        lua_pop(state_, 1);
      }
      int n = lua_gettop(state_);
      lua_pop(state_, n);
      return vec;
    } else if (lua_isstring(state_, -1)) {
      std::vector<std::string> vec;
      vec.push_back(std::string(lua_tostring(state_, -1)));
      lua_pop(state_, 1);
      while (lua_next(state_, -2)) {
        vec.push_back(std::string(lua_tostring(state_, -1)));
        lua_pop(state_, 1);
      }
      int n = lua_gettop(state_);
      lua_pop(state_, n);
      return vec;
    } else {
      return Var();
    }
  } else {
    return Var();
  }
}
