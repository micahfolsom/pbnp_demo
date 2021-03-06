#include <pybind11/numpy.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl_bind.h>

#include "gadget.hpp"
#include "generator.hpp"
namespace py = pybind11;

// STL containers
PYBIND11_MAKE_OPAQUE(std::vector<pbnp::Event>);

PYBIND11_MODULE(pbnp_cpp, m) {
  m.doc() = "pybind11 with numpy module - just for demonstration";

  // Event struct - just passing data, so readonly
  py::class_<pbnp::Event> event(m, "Event");
  event.def(py::init<>())
      .def_readonly("id", &pbnp::Event::id)
      .def_readonly("timestamp", &pbnp::Event::timestamp)
      .def_readonly("value", &pbnp::Event::value)
      .def_readonly("status", &pbnp::Event::status);

  // std::vectors come out as a pythonic-vector object on the other side
  py::bind_vector<std::vector<pbnp::Event>>(m, "EventStdVector");

  // Make it so we can return a numpy structured array containing our object
  // The fields of the structured array will be the fields of the object
  PYBIND11_NUMPY_DTYPE(pbnp::Event, id, timestamp, value, status);

  // Generator bindings
  py::class_<pbnp::Generator> generator(m, "Generator");
  generator.def(py::init<std::size_t>())
      .def("getEventsVector", &pbnp::Generator::getEventsVector)
      .def("getEventsNumpy", &pbnp::Generator::getEventsNumpy);

  // Gadget bindings
  py::class_<pbnp::Gadget> gadget(m, "Gadget");
  gadget.def(py::init<int>(), py::arg("N") = 100)
      .def_property("data", &pbnp::Gadget::get_data, &pbnp::Gadget::set_data)
      .def_property("data_2d", &pbnp::Gadget::get_data_2d,
                    &pbnp::Gadget::set_data_2d)
      .def_property("data_3d", &pbnp::Gadget::get_data_3d,
                    &pbnp::Gadget::set_data_3d)
      .def("get_data_2d_cmaj", &pbnp::Gadget::get_data_2d_cmaj)
      .def("get_data_3d_cmaj", &pbnp::Gadget::get_data_3d_cmaj);
}
