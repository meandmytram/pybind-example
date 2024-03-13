# Creating a C++ Library with Python Bindings Using Pybind11

This guide walks you through setting up a simple C++ library and creating Python bindings for it using pybind11. We'll create a `Calculator` class with basic arithmetic operations and expose it to Python.

## Prerequisites

- Git installed on your system.
- CMake (version 3.12 or higher recommended).
- A C++ compiler compatible with C++11 or later.

## Project Structure

Your project directory will look something like this:

```
pybind-example/
├── CMakeLists.txt
├── README.md
├── .gitignore
├── .gitmodules
├── build/
├── extern/
│   └── pybind11/ (pybind11 submodule)
├── include/
│   └── Calculator.hpp
├── src/
│   └── Calculator.cpp
└── python/
    ├── CMakeLists.txt
    └── pybind_module.cpp
```

## Step 1: Initialize Your Project

1. Create a new directory for your project and navigate into it:

   ```bash
   mkdir pybind-example && cd pybind-example
   ```

2. Initialize the directory as a Git repository:

   ```bash
   git init
   ```

## Step 2: Add Pybind11 as a Submodule

1. Add `pybind11` as a Git submodule:

   ```bash
   git submodule add https://github.com/pybind/pybind11.git extern/pybind11
   ```

2. Initialize and update the submodule:

   ```bash
   git submodule update --init --recursive
   ```

## Step 3: Create Your C++ Library

1. **Define the `Calculator` class in `include/Calculator.hpp`:**

   ```cpp
   #ifndef CALCULATOR_HPP
   #define CALCULATOR_HPP

   class Calculator {
   public:
       Calculator() = default;
       int add(int a, int b);
       int subtract(int a, int b);
   };

   #endif // CALCULATOR_HPP
   ```

2. **Implement the `Calculator` class in `src/Calculator.cpp`:**

   ```cpp
   #include "Calculator.hpp"

   int Calculator::add(int a, int b) {
       return a + b;
   }

   int Calculator::subtract(int a, int b) {
       return a - b;
   }
   ```

## Step 4: Bind Your C++ Code to Python

Create `python/pybind_module.cpp`:

```cpp
#include <pybind11/pybind11.h>
#include "Calculator.hpp"

namespace py = pybind11;

PYBIND11_MODULE(calculator, m) {
    py::class_<Calculator>(m, "Calculator")
        .def(py::init<>())
        .def("add", &Calculator::add)
        .def("subtract", &Calculator::subtract);
}
```

## Step 5: Configure CMake

1. **Root `CMakeLists.txt`:**

   ```cmake
   cmake_minimum_required(VERSION 3.12)
   project(CalculatorExample)

   add_subdirectory(extern/pybind11)
   add_subdirectory(src)
   add_subdirectory(python)
   ```

2. **Python `CMakeLists.txt` in the `python` directory:**

   ```cmake
   pybind11_add_module(calculator pybind_module.cpp)

   target_link_libraries(calculator PRIVATE calculator_lib)
   target_include_directories(calculator PRIVATE ../include)
   ```

3. **`CMakeLists.txt` in the `src` directory:**

   ```cmake
   add_library(calculator_lib Calculator.cpp)

   target_include_directories(calculator_lib PUBLIC ../include)
   ```

## Step 6: Build Your Project

1. Create a build directory and navigate into it:

   ```bash
   mkdir build && cd build
   ```

2. Run CMake to configure your project:

   ```bash
   cmake ..
   ```

3. Build the project:

   ```bash
   make
   ```

## Using Your Python Bindings

After building, you'll find a Python module (e.g., `calculator.so` or `calculator.pyd` depending on your platform) in your build directory. You can import this module in Python:

```python
import calculator

calc = calculator.Calculator()
print(calc.add(5, 3))  # Output: 8
print(calc.subtract(10, 4))  # Output: 6
```

## Conclusion

You've now created a simple C++ library with Python bindings using pybind11. This setup allows you to easily extend your Python projects with high-performance C++ code.
