#include "generator.hpp"

#include <iostream>

using namespace std;
namespace pbnp {
Generator::Generator(size_t n) {
  cout << "Creating Generator and generating data...";
  m_vecEvents = vector<Event>(n);
  m_npEvents = pybind11::array_t<Event>(n);
  auto ptr = static_cast<Event*>(m_npEvents.request().ptr);
  for (size_t i = 0; i < n; ++i) {
    Event event = {(uint8_t)(i % 255), i, 10.f * (float)i,
                   (i % 2 == 0 ? true : false)};
    m_vecEvents[i] = event;
    ptr[i] = event;
  }
  cout << "done. Generated " << n << " events" << endl;
}

Generator::~Generator() {}

vector<Event> Generator::getEventsVector() { return m_vecEvents; }

pybind11::array_t<Event> Generator::getEventsNumpy() { return m_npEvents; }
}  // namespace pbnp
