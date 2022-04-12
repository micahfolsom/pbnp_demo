#!/usr/bin/env python
import pbnp  # noqa
import numpy as np  # noqa
import timeit

# Number of elements in arrays, per dimension
N = 100
NTRIALS = 1000

# 1D
dur = timeit.timeit(
    f"g = pbnp.Gadget({N})", setup="import pbnp", number=NTRIALS
)
print(f"\nTook {dur} sec to create Gadget")

# 2D
dur = timeit.timeit(
    "d1 = g.data",
    setup=f"import pbnp;N = {N};g = pbnp.Gadget({N})",
    number=NTRIALS,
)
print(f"\nTook {dur} sec to get 1D")
dur = timeit.timeit(
    f"g.data = np.ones(({N}))",
    setup=f"import pbnp;import numpy as np;N = {N};g = pbnp.Gadget({N})",
    number=NTRIALS,
)
print(f"\nTook {dur} sec to set 1D")

dur = timeit.timeit(
    "d2 = g.data_2d",
    setup=f"import pbnp;N = {N};g = pbnp.Gadget({N})",
    number=NTRIALS,
)
print(f"\nTook {dur} sec to get 2D (row-major)")
dur = timeit.timeit(
    "d2 = g.get_data_2d_cmaj()",
    setup=f"import pbnp;N = {N};g = pbnp.Gadget({N})",
    number=NTRIALS,
)
print(f"\nTook {dur} sec to get 2D (column-major)")
dur = timeit.timeit(
    f"g.data_2d = np.ones(({N, N}), dtype=int)",
    setup=f"import pbnp;import numpy as np;N = {N};g = pbnp.Gadget({N})",
    number=NTRIALS,
)
print(f"\nTook {dur} sec to set 2D (row-major)")

dur = timeit.timeit(
    "d3 = g.data_3d",
    setup=f"import pbnp;N = {N};g = pbnp.Gadget({N})",
    number=NTRIALS,
)
print(f"\nTook {dur} sec to get 3D (row-major)")
dur = timeit.timeit(
    "d3 = g.get_data_3d_cmaj()",
    setup=f"import pbnp;N = {N};g = pbnp.Gadget({N})",
    number=NTRIALS,
)
print(f"\nTook {dur} sec to get 3D (column-major)")
dur = timeit.timeit(
    f"g.data_3d = np.ones(({N}, {N}, {N}), dtype=int)",
    setup=f"import pbnp;import numpy as np;N = {N};g = pbnp.Gadget({N})",
    number=NTRIALS,
)
print(f"\nTook {dur} sec to set 3D (row-major)")
