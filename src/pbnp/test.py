#!/usr/bin/env python
"""Run the test on the python side."""
from .pbnp_cpp import Generator


class PYGenerator(object):
    """Wrapper to test pass-through performance."""

    def __init__(self, n=100000):
        self.generator = Generator(n)

    def get_events_vec(self):
        return self.generator.getEventsVector()

    def get_events_numpy(self):
        return self.generator.getEventsNumpy()


def run_test():
    # TODO
    print("Running test in python")
