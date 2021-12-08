#include "generator.hpp"

int main(int, char**) {
  // Segfaults?
  pbnp::Generator g(1000);
  auto v = g.getEventsVector();
  auto np = g.getEventsNumpy();
  return 0;
}
