#include "variable.hpp"

#include <iostream>

std::ostream& varia::operator<<(std::ostream& out, const Var& lhs) {
  switch (lhs.type_) {
    case Var::NONE:
      out << "(null)";
      break;
    case Var::INT:
      out << lhs.i;
      break;
    case Var::DOUBLE:
      out << lhs.d;
      break;
    case Var::STRING:
      out << lhs.s;
      break;
    default:
      out << "(var)";
      break;
  }
  return out;
}
