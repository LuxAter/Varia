#ifndef VARIA_PYTHON_HPP_
#define VARIA_PYTHON_HPP_
#ifdef VARIA_PYTHON

#include <memory>
#include <string>
#include <vector>

#include "script.hpp"
#include "variable.hpp"

extern "C" {
#include <Python.h>
}

namespace varia {
class Python : public Script {
 public:
  Python();
  explicit Python(const std::string& file);
  Python(const Python& python);

  virtual ~Python();

  virtual bool valid() const;

  virtual bool has(const std::string& val);
  virtual bool hasi(const std::string& val);
  virtual bool hasvi(const std::string& val);
  virtual bool hasd(const std::string& val);
  virtual bool hasvd(const std::string& val);
  virtual bool hass(const std::string& val);
  virtual bool hasvs(const std::string& val);
  virtual bool hasf(const std::string& val);

  virtual Var get(const std::string& val);
  virtual int geti(const std::string& val);
  virtual std::vector<int> getvi(const std::string& val);
  virtual double getd(const std::string& val);
  virtual std::vector<double> getvd(const std::string& val);
  virtual std::string gets(const std::string& val);
  virtual std::vector<std::string> getvs(const std::string& val);

 protected:
  void open_script();

  virtual Var call_func(const std::string& func, const std::vector<Var>& args);

 private:
  std::shared_ptr<int> valid_check_;
  PyObject* module_;
};
}  // namespace varia

#endif  // VARIA_PYTHON
#endif  // VARIA_PYTHON_HPP_
