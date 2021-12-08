#!/usr/bin/env python
import pbnp
import numpy as np
import time


# Helper
def tstamp():
    return time.perf_counter_ns() * 1e-9


# How many?
N = 10000000

# Pre-allocate numpy structured arrays that will hold the event data
data = np.zeros(
    shape=(N,),
    dtype=[
        ("id", np.uint8),
        ("timestamp", np.uint64),
        ("value", float),
        ("status", bool),
    ],
)

start = tstamp()
# Generate fake data
g = pbnp.Generator(N)
print(f"\nTook {tstamp() - start} sec to generate data")

start = tstamp()
ev_vec = g.getEventsVector()
print(f"Took {tstamp() - start} sec to get data container object")

print(f"\nGot {len(ev_vec)} std::vector events")
print(f"Returned std::vector type: {type(ev_vec)}")

# Get data items from vector
start = tstamp()
for i, ev in enumerate(ev_vec):
    data["id"][i] = ev.id
    data["timestamp"][i] = ev.timestamp
    data["value"][i] = ev.value
    data["status"][i] = ev.status
print(f"\nTook {tstamp() - start} sec to copy values from Event objects")
print(data)

# Get a pre-filled numpy structured array
start = tstamp()
data2 = g.getEventsNumpy()
print(f"\nTook {tstamp() - start} sec to get numpy structured array directly")
print(data2)

# Confirm that the data is the same
print()
for k in ("id", "timestamp", "value", "status"):
    print(f"All equal for {k}?: {np.all(data[k] == data2[k])}")
