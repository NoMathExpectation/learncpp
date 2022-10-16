cmake_minimum_required(VERSION 3.23)
project(calculator)

# cpp standard
set(CMAKE_CXX_STANDARD 11)

# build
add_executable(${CMAKE_PROJECT_NAME} main.cpp)

# link library gmp and mpfr
target_link_libraries(${CMAKE_PROJECT_NAME} "-lgmp" "-lmpfr")
