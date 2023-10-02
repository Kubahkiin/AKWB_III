cmake_minimum_required(VERSION 3.21)
project(akwb3)

set(CMAKE_CXX_STANDARD 20)

add_executable(akwb3 main.cpp instance.hpp Node.h Graph.h)
