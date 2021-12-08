# `pybind11` / `numpy` Demo #

Demonstration of using `pybind11` C++-to-python bindings with `numpy`. This
is a python module, `pbnp`, that can be installed with the usual methods.
Inside, there's a sub-module, `pbnp_cpp`, which contains the C++ code.

The test code is written to generate a sizeable chunk of data and benchmark
passing it from C++ to python via different mechanisms.
