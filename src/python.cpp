#include "python.hpp"

#include <memory>
#include <string>
#include <vector>

#include <iostream>

#include "script.hpp"
#include "variable.hpp"

#ifdef VARIA_PYTHON

extern "C" {
#include <Python.h>
}

varia::Python::Python() : Script(), valid_check_(nullptr), module_(nullptr) {}

varia::Python::Python(const std::string& file)
    : Script(file), valid_check_(nullptr), module_(nullptr) {
  open_script();
}

varia::Python::Python(const Python& python)
    : Script(python), valid_check_(nullptr), module_(nullptr) {}

varia::Python::~Python() {
  if (valid_check_.use_count() == 1) {
    Py_FinalizeEx();
  }
}

bool varia::Python::valid() const { return valid_check_.use_count() != 0; }

bool varia::Python::has(const std::string& val) {
  return PyObject_HasAttrString(module_, val.c_str());
}
bool varia::Python::hasi(const std::string& val) {
  return PyObject_HasAttrString(module_, val.c_str())
             ? PyLong_Check(PyObject_GetAttrString(module_, val.c_str()))
             : false;
}
bool varia::Python::hasvi(const std::string& val) {
  PyObject* attr;
  return ((attr = PyObject_GetAttrString(module_, val.c_str())) != NULL &&
          PyList_Check(attr) && PyList_Size(attr) != 0 &&
          PyLong_Check(PyList_GetItem(attr, 0)));
}
bool varia::Python::hasd(const std::string& val) {
  return PyObject_HasAttrString(module_, val.c_str())
             ? PyFloat_Check(PyObject_GetAttrString(module_, val.c_str()))
             : false;
}
bool varia::Python::hasvd(const std::string& val) {
  PyObject* attr;
  return ((attr = PyObject_GetAttrString(module_, val.c_str())) != NULL &&
          PyList_Check(attr) && PyList_Size(attr) != 0 &&
          PyFloat_Check(PyList_GetItem(attr, 0)));
}
bool varia::Python::hass(const std::string& val) {
  return PyObject_HasAttrString(module_, val.c_str())
             ? PyUnicode_Check(PyObject_GetAttrString(module_, val.c_str()))
             : false;
}
bool varia::Python::hasvs(const std::string& val) {
  PyObject* attr;
  return ((attr = PyObject_GetAttrString(module_, val.c_str())) != NULL &&
          PyList_Check(attr) && PyList_Size(attr) != 0 &&
          PyUnicode_Check(PyList_GetItem(attr, 0)));
}
bool varia::Python::hasf(const std::string& val) {
  return PyObject_HasAttrString(module_, val.c_str())
             ? PyFunction_Check(PyObject_GetAttrString(module_, val.c_str()))
             : false;
}

varia::Var varia::Python::get(const std::string& val) {
  PyObject* attr = PyObject_GetAttrString(module_, val.c_str());
  if (attr != NULL) {
    if (PyLong_Check(attr)) {
      return Var(static_cast<int>(PyLong_AsLong(attr)));
    } else if (PyFloat_Check(attr)) {
      return Var(static_cast<double>(PyFloat_AsDouble(attr)));
    } else if (PyUnicode_Check(attr)) {
      return Var(PyUnicode_AsUTF8(attr));
    } else if (PyList_Check(attr) && PyList_Size(attr) != 0) {
      if (PyLong_Check(PyList_GetItem(attr, 0))) {
        std::vector<int> vals;
        for (std::size_t i = 0; i < PyList_Size(attr); ++i) {
          vals.push_back(PyLong_AsLong(PyList_GetItem(attr, i)));
        }
        return Var(vals);
      } else if (PyFloat_Check(PyList_GetItem(attr, 0))) {
        std::vector<double> vals;
        for (std::size_t i = 0; i < PyList_Size(attr); ++i) {
          vals.push_back(PyFloat_AsDouble(PyList_GetItem(attr, i)));
        }
        return Var(vals);
      } else if (PyUnicode_Check(PyList_GetItem(attr, 0))) {
        std::vector<std::string> vals;
        for (std::size_t i = 0; i < PyList_Size(attr); ++i) {
          vals.push_back(
              std::string(PyUnicode_AsUTF8(PyList_GetItem(attr, i))));
        }
        return Var(vals);
      }
    } else {
      return Var();
    }
  } else {
    return Var();
  }
}

int varia::Python::geti(const std::string& val) {
  PyObject* attr = PyObject_GetAttrString(module_, val.c_str());
  if (attr != NULL && PyLong_Check(attr)) {
    return static_cast<int>(PyLong_AsLong(attr));
  }
  return int();
}
std::vector<int> varia::Python::getvi(const std::string& val) {
  PyObject* attr = PyObject_GetAttrString(module_, val.c_str());
  if (attr != NULL && PyList_Check(attr) && PyList_Size(attr) != 0 &&
      PyLong_Check(PyList_GetItem(attr, 0))) {
    std::vector<int> ret;
    for (std::size_t i = 0; i < PyList_Size(attr); ++i) {
      ret.push_back(PyLong_AsLong(PyList_GetItem(attr, i)));
    }
    return ret;
  }
  return std::vector<int>();
}
double varia::Python::getd(const std::string& val) {
  PyObject* attr = PyObject_GetAttrString(module_, val.c_str());
  if (attr != NULL && PyFloat_Check(attr)) {
    return static_cast<double>(PyFloat_AsDouble(attr));
  }
  return double();
}
std::vector<double> varia::Python::getvd(const std::string& val) {
  PyObject* attr = PyObject_GetAttrString(module_, val.c_str());
  if (attr != NULL && PyList_Check(attr) && PyList_Size(attr) != 0 &&
      PyFloat_Check(PyList_GetItem(attr, 0))) {
    std::vector<double> ret;
    for (std::size_t i = 0; i < PyList_Size(attr); ++i) {
      ret.push_back(PyFloat_AsDouble(PyList_GetItem(attr, i)));
    }
    return ret;
  }
  return std::vector<double>();
}
std::string varia::Python::gets(const std::string& val) {
  PyObject* attr = PyObject_GetAttrString(module_, val.c_str());
  if (attr != NULL && PyUnicode_Check(attr)) {
    return std::string(PyUnicode_AsUTF8(attr));
  }
  return std::string();
}
std::vector<std::string> varia::Python::getvs(const std::string& val) {
  PyObject* attr = PyObject_GetAttrString(module_, val.c_str());
  if (attr != NULL && PyList_Check(attr) && PyList_Size(attr) != 0 &&
      PyUnicode_Check(PyList_GetItem(attr, 0))) {
    std::vector<std::string> ret;
    for (std::size_t i = 0; i < PyList_Size(attr); ++i) {
      ret.push_back(std::string(PyUnicode_AsUTF8(PyList_GetItem(attr, i))));
    }
    return ret;
  }
  return std::vector<std::string>();
}

void varia::Python::open_script() {
  Py_Initialize();
  PyRun_SimpleString("import sys; sys.path.append('.')");
  module_ = PyImport_ImportModule(this->file_name_.c_str());
  if (module_ != nullptr) {
    valid_check_ = std::make_shared<int>(1);
  } else {
    this->error("Failed to open script file");
  }
}

varia::Var varia::Python::call_func(const std::string& func,
                                    const std::vector<Var>& args) {
  PyObject* py_func = PyObject_GetAttrString(module_, func.c_str());
  if (py_func != NULL && PyFunction_Check(py_func)) {
    PyObject* params = PyTuple_New(args.size());
    for (std::size_t i = 0; i < args.size(); ++i) {
      switch (args[i].type_) {
        case Var::INT:
          PyTuple_SetItem(params, i, PyLong_FromLong(args[i].i));
          break;
        case Var::DOUBLE:
          PyTuple_SetItem(params, i, PyFloat_FromDouble(args[i].d));
          break;
        case Var::STRING:
          PyTuple_SetItem(params, i, PyUnicode_FromString(args[i].s.c_str()));
          break;
        case Var::INT_VECTOR: {
          PyObject* list_var = PyList_New(0);
          for (std::size_t j = 0; j < args[i].vi.size(); ++j) {
            PyList_Append(list_var, PyLong_FromLong(args[i].vi[j]));
          }
          PyTuple_SetItem(params, i, list_var);
          break;
        }
        case Var::DOUBLE_VECTOR: {
          PyObject* list_var = PyList_New(0);
          for (std::size_t j = 0; j < args[i].vd.size(); ++j) {
            PyList_Append(list_var, PyFloat_FromDouble(args[i].vd[j]));
          }
          PyTuple_SetItem(params, i, list_var);
          break;
        }
        case Var::STRING_VECTOR: {
          PyObject* list_var = PyList_New(0);
          for (std::size_t j = 0; j < args[i].vs.size(); ++j) {
            PyList_Append(list_var,
                          PyUnicode_FromString(args[i].vs[j].c_str()));
          }
          PyTuple_SetItem(params, i, list_var);
          break;
        }
        default:
          break;
      }
    }
    PyObject* res = PyObject_CallObject(py_func, params);
    if (res != NULL) {
      if (PyLong_Check(res)) {
        return Var(static_cast<int>(PyLong_AsLong(res)));
      } else if (PyFloat_Check(res)) {
        return Var(static_cast<double>(PyFloat_AsDouble(res)));
      } else if (PyUnicode_Check(res)) {
        return Var(PyUnicode_AsUTF8(res));
      } else if (PyList_Check(res) && PyList_Size(res) != 0) {
        if (PyLong_Check(PyList_GetItem(res, 0))) {
          std::vector<int> vals;
          for (std::size_t i = 0; i < PyList_Size(res); ++i) {
            vals.push_back(PyLong_AsLong(PyList_GetItem(res, i)));
          }
          return Var(vals);
        } else if (PyFloat_Check(PyList_GetItem(res, 0))) {
          std::vector<double> vals;
          for (std::size_t i = 0; i < PyList_Size(res); ++i) {
            vals.push_back(PyFloat_AsDouble(PyList_GetItem(res, i)));
          }
          return Var(vals);
        } else if (PyUnicode_Check(PyList_GetItem(res, 0))) {
          std::vector<std::string> vals;
          for (std::size_t i = 0; i < PyList_Size(res); ++i) {
            vals.push_back(
                std::string(PyUnicode_AsUTF8(PyList_GetItem(res, i))));
          }
          return Var(vals);
        }
      } else {
        return Var();
      }
    } else {
      return Var();
    }

  } else {
    return Var();
  }
}
#endif  // VARIA_PYTHON
