# Create a library target for your C++ library
add_library(calculator_lib Calculator.cpp)

# Make sure the compiler can find the include files
target_include_directories(calculator_lib PUBLIC ../include)
