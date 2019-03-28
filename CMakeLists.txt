cmake_minimum_required(VERSION 3.10 FATAL_ERROR)
option(TESTS "build tests" OFF)
project(Varia CXX C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# PYTHON {{{
find_package(PythonLibs)
if(PYTHONLIBS_FOUND)
  include_directories(${PYTHON_INCLUDE_DIRS})
  link_libraries(${PYTHON_LIBRARIES})
  add_definitions(-DVARIA_PYTHON)
endif()
# }}}

# LUA {{{
find_package(Lua)
if(LUA_FOUND)
  include_directories(${LUA_INCLUDE_DIRS})
  link_libraries(${LUA_LIBRARIES})
  add_definitions(-DVARIA_LUA)
endif()
# }}}

# LIBVARIA.A {{{
file(GLOB_RECURSE lib_src "${CMAKE_CURRENT_SOURCE_DIR}" "src/*.cpp")
list(REMOVE_ITEM lib_src "${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp")
add_library(varia ${lib_src})
# }}}

# VARIA.EXE {{{
add_executable(varia.exe "src/main.cpp")
target_link_libraries(varia.exe varia)
# }}}

# TESTS {{{
if(TESTS)
  enable_testing()
  add_subdirectory(external/googletest)
  include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
  include_directories(${gmock_SOURCE_DIR}/include ${gmock_SOURCE_DIR})
  file(GLOB_RECURSE test_src "${CMAKE_CURRENT_SOURCE_DIR}" "tests/*.cpp")
  add_executable(tests ${test_src})
  target_link_libraries(tests pthread gtest gtest_main varia)
endif()
# }}}
