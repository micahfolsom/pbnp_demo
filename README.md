# `pybind11` / `numpy` Demo #

## Introduction ##

[`pybind11`](https://pybind11.readthedocs.io/en/stable/) is really cool. I
can write explicitly typed and performant C++ code that is accessible from
python. Usually this means doing a bunch of heavy lifting in C++ and then
providing a python interface to get data, check status, etc.

In some cases, I require that I be able to pass large amounts of structured
data quickly - for example, when collecting data from a high-throughput
sensor. In this case, it really matters that my communication of these data
from C++ to python is performant.

`pybind11` has a fairly easy way to pass a `std::vector<T>` and some other
built-in STL containers, which is the natural way to accomplish this, at least
to my lizard brain. For my case, `T` would be a struct that just holds some data
I want to pass around. More info can be found [here](
https://pybind11.readthedocs.io/en/stable/advanced/cast/stl.html?highlight=STL)
.

This approach ends up being slow, since the vector's underlying data is
copied when passed into python. You'll typically then perform another
copy when converting to a `numpy` array. This is slow - we'd rather get
a `numpy.ndarray` directly, and ideally, in a way that it knows to copy
the reference to the underlying data, and not the data itself.

This repo demonstrates how to build the `numpy` structured array in C++ and
then pass it directly into python. This avoids the copies and results in
very good performance. A single function call and then you've got a `numpy`
object, ready to go. Great!

The test code is written to generate a sizeable chunk of data and benchmark
passing it from C++ to python via the two different mechanisms.

There's also a `Gadget` showing how to pass multidimensional `numpy` arrays
both ways, from python to C++, and vice-versa.

## Instructions ##

Install with `pip install --user .` from the base of this repo. Test with
`python scripts/test_generator.py` or `python scripts/test_gadget.py`.
