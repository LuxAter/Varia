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

bool varia::operator==(const Var& lhs, const Var& rhs){
  if(lhs.type_ != rhs.type_) return false;
  switch(lhs.type_){
    case Var::NONE:
      return true;
    case Var::INT:
      return lhs.i == rhs.i;
    case Var::DOUBLE:
      return lhs.d == rhs.d;
    case Var::STRING:
      return lhs.s == rhs.s;
    case Var::INT_VECTOR:
      return lhs.vi == rhs.vi;
    case Var::DOUBLE_VECTOR:
      return lhs.vd == rhs.vd;
    case Var::STRING_VECTOR:
      return lhs.vs == rhs.vs;
    default:
      return false;
  }
}
