#include <pybind11/pybind11.h>
#include "generator.hpp"
#include <pybind11/stl_bind.h>
#include <pybind11/numpy.h>
#include "neutron.hpp"
namespace py = pybind11;

// STL containers
PYBIND11_MAKE_OPAQUE(std::vector<pbnp::Event>);
PYBIND11_MAKE_OPAQUE(std::vector<pbnp::Neutron>);

PYBIND11_MODULE(pbnp_cpp, m) {
  m.doc() = "pybind11 with numpy module - just for demonstration";

  // Event struct - just passing data, so readonly
  py::class_<pbnp::Event> event(m, "Event");
  event
    .def(py::init<>())
    .def_readonly("id", &pbnp::Event::id)
    .def_readonly("timestamp", &pbnp::Event::timestamp)
    .def_readonly("value", &pbnp::Event::value)
    .def_readonly("status", &pbnp::Event::status);

  // std::vectors come out as a pythonic-vector object on the other side
  py::bind_vector<std::vector<pbnp::Event>>(m, "EventStdVector");
  py::bind_vector<std::vector<pbnp::Neutron>>(m, "NeutronStdVector");

  // Make it so we can return a numpy structured array containing our object
  // The fields of the structured array will be the fields of the object
  PYBIND11_NUMPY_DTYPE(pbnp::Event, id, timestamp, value, status);

  // Generator bindings
  py::class_<pbnp::Generator> generator(m, "Generator");
  generator
    .def(py::init<std::size_t>())
    .def("getEventsVector", &pbnp::Generator::getEventsVector)
    .def("getEventsNumpy", &pbnp::Generator::getEventsNumpy);

  // Neutron
  py::class_<pbnp::Neutron> neutron(m, "Neutron");
  neutron
    // Default ctor
    .def(py::init<>())
    // With args that have defaults defaults
    .def(py::init<int, float, pbnp::Neutron*, std::vector<pbnp::Neutron> const&>(),
        py::arg("id") = -1, py::arg("data") = 0.f, py::arg("parent") = nullptr,
        py::arg("children") = std::vector<pbnp::Neutron>())
    .def_property("id", &pbnp::Neutron::get_id, &pbnp::Neutron::set_id)
    .def_property("data", &pbnp::Neutron::get_data, &pbnp::Neutron::set_data)
    .def_property("parent", &pbnp::Neutron::get_parent, &pbnp::Neutron::set_parent)
    .def_property("children", &pbnp::Neutron::get_children, &pbnp::Neutron::set_children)
    .def("unfold", &pbnp::Neutron::unfold);
}
