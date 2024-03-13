#include <pybind11/pybind11.h>
#include "Calculator.hpp"

namespace py = pybind11;

PYBIND11_MODULE(calculator, m) {
    py::class_<Calculator>(m, "Calculator")
        .def(py::init<>())
        .def("add", &Calculator::add)
        .def("subtract", &Calculator::subtract);
}
