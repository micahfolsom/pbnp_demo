#ifndef GENERATOR_HPP
#define GENERATOR_HPP
#include <pybind11/numpy.h>

#include <cstdint>
#include <vector>

namespace pbnp {
// A generic event structure with some primitive attributes
// TODO: what if one attribute is an array or vector?
struct Event {
  std::uint8_t id;
  std::uint64_t timestamp;
  float value;
  bool status;
};

// This class just makes a bunch of fake Events, then provides accessors to
// test the performance of the different options
class Generator {
 public:
  Generator(std::size_t n);
  ~Generator();

  std::vector<Event> getEventsVector();
  pybind11::array_t<Event> getEventsNumpy();

 private:
  std::vector<Event> m_vecEvents;
  pybind11::array_t<Event> m_npEvents;
};
}  // namespace pbnp

#endif
