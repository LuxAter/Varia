#ifndef VARIA_SCRIPT_HPP_
#define VARIA_SCRIPT_HPP_

#include <functional>
#include <string>
#include <vector>

#include "logging.hpp"
#include "variable.hpp"

namespace varia {
class Script {
 public:
  enum ScriptType {
    NULL_SCRIPT,
    LUA_SCRIPT,
    PYTHON_SCRIPT,
  };

  Script() : file_name_(), _error_(logging::console_callback) {}
  explicit Script(const std::string& file)
      : file_name_(file), _error_(logging::console_callback) {}
  virtual ~Script() {}

  virtual bool valid() const { return false; }

  virtual bool has(const std::string& val) { return false; }
  virtual bool hasi(const std::string& val) { return false; }
  virtual bool hasvi(const std::string& val) { return false; }
  virtual bool hasd(const std::string& val) { return false; }
  virtual bool hasvd(const std::string& val) { return false; }
  virtual bool hass(const std::string& val) { return false; }
  virtual bool hasvs(const std::string& val) { return false; }
  virtual bool hasf(const std::string& val) { return false; }

  virtual Var get(const std::string& val) { return Var(); }
  virtual int geti(const std::string& val) { return int(); }
  virtual std::vector<int> getvi(const std::string& val) {
    return std::vector<int>();
  }
  virtual double getd(const std::string& val) { return float(); }
  virtual std::vector<double> getvd(const std::string& val) {
    return std::vector<double>();
  }
  virtual std::string gets(const std::string& val) { return std::string(); }
  virtual std::vector<std::string> getvs(const std::string& val) {
    return std::vector<std::string>();
  }

  template <typename _R>
  _R call(const std::string& func) {
    std::vector<Var> params;
    return _R(call_func(func, params));
  }
  template <typename _R, typename... _ARGS>
  _R call(const std::string& func, const _ARGS&... args) {
    std::vector<Var> params = construct_args(args...);
    return _R(call_func(func, params));
  }
  template <typename _R, typename... _ARGS>
  std::function<_R(const _ARGS&...)> func(const std::string& func) {
    return [func, this](const _ARGS&... args) {
      return _R(this->vcall(func, args...));
    };
  }

  Var vcall(const std::string& func) {
    std::vector<Var> params;
    return call_func(func, params);
  }
  template <typename... _ARGS>
  Var vcall(const std::string& func, const _ARGS&... args) {
    std::vector<Var> params = construct_args(args...);
    return call_func(func, params);
  }
  std::function<Var()> vfunc(const std::string& func) {
    return [func, this]() { return this->vcall(func); };
  }
  template <typename... _ARGS>
  std::function<Var(const _ARGS&...)> vfunc(const std::string& func) {
    return [func, this](const _ARGS&... args) {
      return this->vcall(func, args...);
    };
  }

  void set_error_callback(
      const std::function<void(const std::string&, const std::string&)>&
          callback) {
    _error_ = callback;
  }

 protected:
  inline void error(const std::string& msg) const { _error_(file_name_, msg); }

  virtual Var call_func(const std::string& func, const std::vector<Var>& args) {
    return Var();
  }

  ScriptType type_;
  std::string file_name_;
  std::function<void(const std::string&, const std::string&)> _error_;

 private:
};
}  // namespace varia

#endif  // VARIA_SCRIPT_HPP_
