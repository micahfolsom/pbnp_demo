cmake_minimum_required(VERSION 3.10)
project(pbnp)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CPP_SOURCE_DIR ${PROJECT_SOURCE_DIR}/src/cpp)
include_directories(${CPP_SOURCE_DIR})
file(GLOB CPP_SOURCES ${CPP_SOURCE_DIR}/*.cpp)

add_subdirectory(lib/pybind11)
# Access in python via `import pbnp.pbnp_cpp`
# or `from .pbnp_cpp import *`
pybind11_add_module(
  pbnp_cpp
  ${CPP_SOURCES}
  ${PROJECT_SOURCE_DIR}/src/pbnp/bindings.cpp)
