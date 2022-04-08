cmake_minimum_required(VERSION 3.10)
project(pbnp_cpp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-g -pthread -O2 -Wall -Wextra -Wpedantic -fvisibility=hidden")

include_directories(${PROJECT_SOURCE_DIR})
file(GLOB CPP_SOURCES ${PROJECT_SOURCE_DIR}/*.cpp)

add_subdirectory(../../lib/pybind11 pybind11)

## Tests
add_executable(test ${PROJECT_SOURCE_DIR}/tests/test.cpp ${CPP_SOURCES})
target_link_libraries(test pybind11::embed)
add_executable(test_neutron ${PROJECT_SOURCE_DIR}/tests/test_neutron.cpp ${CPP_SOURCES})
target_link_libraries(test_neutron pybind11::embed)
