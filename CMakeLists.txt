cmake_minimum_required(VERSION 3.23)
project(learncpp)

set(CMAKE_CXX_STANDARD 20)

add_executable(learncpp main.cpp)
add_executable(hellocpp hello/hello.cpp)
add_executable(helloc hello/hello.c)
add_executable(week1 week1/main.cpp week1/add.cpp)
add_executable(project1 project1/source.cpp)
add_executable(project2 project2/main.cpp)

add_executable(lab4_1 week4/lab/1/main.cpp week4/lab/1/stufun.cpp)
add_executable(lab4_2 week4/lab/2/main.cpp week4/lab/2/travel.cpp)