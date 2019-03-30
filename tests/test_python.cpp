#include "gtest/gtest.h"

#include <cmath>

#include "../src/varia.hpp"

TEST(PythonTest, LoadScript) {
  varia::Script* script = varia::load_script("test_python.py");
  EXPECT_EQ(script->valid(), true);
  delete script;
}

TEST(PythonTest, HasVar) {
  varia::Script* script = varia::load_script("test_python.py");
  EXPECT_EQ(script->has("int_var"), true);
  EXPECT_EQ(script->hasi("int_var"), true);
  EXPECT_EQ(script->hasd("int_var"), false);
  EXPECT_EQ(script->hass("int_var"), false);
  EXPECT_EQ(script->hasvi("int_var"), false);
  EXPECT_EQ(script->hasvd("int_var"), false);
  EXPECT_EQ(script->hasvs("int_var"), false);
  EXPECT_EQ(script->hasf("int_var"), false);

  EXPECT_EQ(script->has("int_vec_var"), true);
  EXPECT_EQ(script->hasi("int_vec_var"), false);
  EXPECT_EQ(script->hasd("int_vec_var"), false);
  EXPECT_EQ(script->hass("int_vec_var"), false);
  EXPECT_EQ(script->hasvi("int_vec_var"), true);
  EXPECT_EQ(script->hasvd("int_vec_var"), false);
  EXPECT_EQ(script->hasvs("int_vec_var"), false);
  EXPECT_EQ(script->hasf("int_vec_var"), false);

  EXPECT_EQ(script->has("float_var"), true);
  EXPECT_EQ(script->hasi("float_var"), false);
  EXPECT_EQ(script->hasd("float_var"), true);
  EXPECT_EQ(script->hass("float_var"), false);
  EXPECT_EQ(script->hasvi("float_var"), false);
  EXPECT_EQ(script->hasvd("float_var"), false);
  EXPECT_EQ(script->hasvs("float_var"), false);
  EXPECT_EQ(script->hasf("float_var"), false);

  EXPECT_EQ(script->has("float_vec_var"), true);
  EXPECT_EQ(script->hasi("float_vec_var"), false);
  EXPECT_EQ(script->hasd("float_vec_var"), false);
  EXPECT_EQ(script->hass("float_vec_var"), false);
  EXPECT_EQ(script->hasvi("float_vec_var"), false);
  EXPECT_EQ(script->hasvd("float_vec_var"), true);
  EXPECT_EQ(script->hasvs("float_vec_var"), false);
  EXPECT_EQ(script->hasf("float_vec_var"), false);

  EXPECT_EQ(script->has("string_var"), true);
  EXPECT_EQ(script->hasi("string_var"), false);
  EXPECT_EQ(script->hasd("string_var"), false);
  EXPECT_EQ(script->hass("string_var"), true);
  EXPECT_EQ(script->hasvi("string_var"), false);
  EXPECT_EQ(script->hasvd("string_var"), false);
  EXPECT_EQ(script->hasvs("string_var"), false);
  EXPECT_EQ(script->hasf("string_var"), false);

  EXPECT_EQ(script->has("string_vec_var"), true);
  EXPECT_EQ(script->hasi("string_vec_var"), false);
  EXPECT_EQ(script->hasd("string_vec_var"), false);
  EXPECT_EQ(script->hass("string_vec_var"), false);
  EXPECT_EQ(script->hasvi("string_vec_var"), false);
  EXPECT_EQ(script->hasvd("string_vec_var"), false);
  EXPECT_EQ(script->hasvs("string_vec_var"), true);
  EXPECT_EQ(script->hasf("string_vec_var"), false);

  EXPECT_EQ(script->has("func0"), true);
  EXPECT_EQ(script->hasi("func0"), false);
  EXPECT_EQ(script->hasd("func0"), false);
  EXPECT_EQ(script->hass("func0"), false);
  EXPECT_EQ(script->hasvi("func0"), false);
  EXPECT_EQ(script->hasvd("func0"), false);
  EXPECT_EQ(script->hasvs("func0"), false);
  EXPECT_EQ(script->hasf("func0"), true);
  delete script;
}

TEST(PythonTest, GetVar) {
  varia::Script* script = varia::load_script("test_python.py");
  EXPECT_EQ(script->geti("int_var"), 2019);
  EXPECT_EQ(script->getd("int_var"), 0.0);
  EXPECT_EQ(script->gets("int_var"), "");
  EXPECT_EQ(script->getvi("int_var"), std::vector<int>());
  EXPECT_EQ(script->getvd("int_var"), std::vector<double>());
  EXPECT_EQ(script->getvs("int_var"), std::vector<std::string>());

  EXPECT_EQ(script->geti("float_var"), 0);
  EXPECT_EQ(script->getd("float_var"), 3.1415);
  EXPECT_EQ(script->gets("float_var"), "");
  EXPECT_EQ(script->getvi("float_var"), std::vector<int>());
  EXPECT_EQ(script->getvd("float_var"), std::vector<double>());
  EXPECT_EQ(script->getvs("float_var"), std::vector<std::string>());

  EXPECT_EQ(script->geti("string_var"), 0);
  EXPECT_EQ(script->getd("string_var"), 0.0);
  EXPECT_EQ(script->gets("string_var"), "Hello, World!");
  EXPECT_EQ(script->getvi("string_var"), std::vector<int>());
  EXPECT_EQ(script->getvd("string_var"), std::vector<double>());
  EXPECT_EQ(script->getvs("string_var"), std::vector<std::string>());

  EXPECT_EQ(script->geti("int_vec_var"), 0);
  EXPECT_EQ(script->getd("int_vec_var"), 0.0);
  EXPECT_EQ(script->gets("int_vec_var"), "");
  EXPECT_EQ(script->getvi("int_vec_var"), std::vector<int>({10, 20, 30}));
  EXPECT_EQ(script->getvd("int_vec_var"), std::vector<double>());
  EXPECT_EQ(script->getvs("int_vec_var"), std::vector<std::string>());

  EXPECT_EQ(script->geti("float_vec_var"), 0);
  EXPECT_EQ(script->getd("float_vec_var"), 0.0);
  EXPECT_EQ(script->gets("float_vec_var"), "");
  EXPECT_EQ(script->getvi("float_vec_var"), std::vector<int>());
  EXPECT_EQ(script->getvd("float_vec_var"),
            std::vector<double>({1.0, 1.5, 2.0}));
  EXPECT_EQ(script->getvs("float_vec_var"), std::vector<std::string>());

  EXPECT_EQ(script->geti("string_vec_var"), 0);
  EXPECT_EQ(script->getd("string_vec_var"), 0.0);
  EXPECT_EQ(script->gets("string_vec_var"), "");
  EXPECT_EQ(script->getvi("string_vec_var"), std::vector<int>());
  EXPECT_EQ(script->getvd("string_vec_var"), std::vector<double>());
  EXPECT_EQ(script->getvs("string_vec_var"),
            std::vector<std::string>({"A", "B", "C"}));
  delete script;
}

TEST(PythonTest, FunctionCall) {
  varia::Script* script = varia::load_script("test_python.py");
  EXPECT_EQ(script->call("func0"), varia::Var());
  EXPECT_EQ(script->call("func1", 1.0), varia::Var());
  EXPECT_EQ(script->call("func2", 1.0, 2.0), varia::Var());
  EXPECT_EQ(script->call("func0r"), varia::Var(3.1415));
  EXPECT_EQ(script->call("func1r", 1.0), varia::Var(std::sin(1.0)));
  EXPECT_EQ(script->call("func2r", 1.0, 2.0),
            varia::Var(std::sin(1.0) * std::cos(2.0)));
  delete script;
}

TEST(PythonTest, Functional) {
  varia::Script* script = varia::load_script("test_python.py");
  auto func = script->func<double, double>("func2r");
  EXPECT_EQ(func(1.0, 2.0), varia::Var(std::sin(1.0) * std::cos(2.0)));
  EXPECT_EQ(func(2.0, 1.0), varia::Var(std::sin(2.0) * std::cos(1.0)));
  delete script;
}
