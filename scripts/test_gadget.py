#!/usr/bin/env python
import pbnp
import numpy as np
import time

# Helper
def tstamp():
    return time.perf_counter_ns() * 1e-9

start = tstamp()
g = pbnp.Gadget(100)
print(f"\nTook {tstamp() - start} sec to create Gadget")

start = tstamp()
d1 = g.data
print(f"\nTook {tstamp() - start} sec to get 1D")
d1[50] = -50
start = tstamp()
g.data = d1
print(f"\nTook {tstamp() - start} sec to set 1D")

start = tstamp()
d2 = g.data_2d
print(f"\nTook {tstamp() - start} sec to get 2D")
d2[50, 50] = -50
start = tstamp()
g.data_2d = d2
print(f"\nTook {tstamp() - start} sec to set 2D")

start = tstamp()
d3 = g.data_3d
print(f"\nTook {tstamp() - start} sec to get 3D")
d3[50, 50, 50] = -50
start = tstamp()
g.data_3d = d3
print(f"\nTook {tstamp() - start} sec to set 3D")
