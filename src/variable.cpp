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
    case Var::INT_VECTOR:
      out << '{';
      for (std::size_t i = 0; i < lhs.vi.size(); ++i) {
        out << lhs.vi[i];
        if (i != lhs.vi.size() - 1) {
          out << ", ";
        }
      }
      out << '}';
      break;
    case Var::DOUBLE_VECTOR:
      out << '{';
      for (std::size_t i = 0; i < lhs.vd.size(); ++i) {
        out << lhs.vd[i];
        if (i != lhs.vd.size() - 1) {
          out << ", ";
        }
      }
      out << '}';
      break;
    case Var::STRING_VECTOR:
      out << '{';
      for (std::size_t i = 0; i < lhs.vs.size(); ++i) {
        out << lhs.vs[i];
        if (i != lhs.vs.size() - 1) {
          out << ", ";
        }
      }
      out << '}';
      break;
    default:
      out << "(var)";
      break;
  }
  return out;
}
