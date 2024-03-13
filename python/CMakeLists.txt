# Assuming the pybind11 directory is correctly found and included
pybind11_add_module(calculator pybind_module.cpp)

# Link the Python module with the C++ library we defined
target_link_libraries(calculator PRIVATE calculator_lib)

# Include the directory where our header files are located
target_include_directories(calculator PRIVATE ../include)
