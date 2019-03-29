#ifndef VARIA_VARIABLE_HPP_
#define VARIA_VARIABLE_HPP_

#include <string>
#include <vector>

namespace varia {
struct Var {
  enum VariableType {
    NONE,
    INT,
    DOUBLE,
    STRING,
    INT_VECTOR,
    DOUBLE_VECTOR,
    STRING_VECTOR
  };

  Var() : vs(), vd(), vi(), s(), d(), i(), type_(NONE) {}
  Var(const int& v) : vs(), vd(), vi(), s(), d(), i(v), type_(INT) {}
  Var(const double& v) : vs(), vd(), vi(), s(), d(v), i(), type_(DOUBLE) {}
  Var(const std::string& v) : vs(), vd(), vi(), s(v), d(), i(), type_(STRING) {}
  Var(const char* v) : vs(), vd(), vi(), s(v), d(), i(), type_(STRING) {}
  Var(const std::vector<int>& v)
      : vs(), vd(), vi(v), s(), d(), i(), type_(INT_VECTOR) {}
  Var(const std::vector<double>& v)
      : vs(), vd(v), vi(), s(), d(), i(), type_(DOUBLE_VECTOR) {}
  Var(const std::vector<std::string>& v)
      : vs(v), vd(), vi(), s(), d(), i(), type_(STRING_VECTOR) {}

  inline operator int() const {
    if (type_ == DOUBLE) return static_cast<int>(d);
    return i;
  }
  inline operator double() const {
    if (type_ == INT) return static_cast<double>(i);
    return d;
  }
  inline operator std::string() const { return s; }
  inline operator std::vector<int>() const { return vi; }
  inline operator std::vector<double>() const { return vd; }
  inline operator std::vector<std::string>() const { return vs; }

  std::vector<std::string> vs;
  std::vector<double> vd;
  std::vector<int> vi;
  std::string s;
  double d;
  int i;
  VariableType type_;
};

std::ostream& operator<<(std::ostream& out, const Var& lhs);

template <typename _T>
std::vector<Var> construct_args(const _T& v) {
  return {Var(v)};
}
template <typename _T, typename... _ARGS>
std::vector<Var> construct_args(const _T& v, const _ARGS&... args) {
  std::vector<Var> params = construct_args(args...);
  params.insert(params.begin(), Var(v));
  return params;
}
}  // namespace varia

#endif  // VARIA_VARIABLE_HPP_
