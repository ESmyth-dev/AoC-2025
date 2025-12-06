cmake_minimum_required(VERSION 3.10)
project(MyProject LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

configure_file(./input.txt ./Debug/input.txt COPYONLY)
configure_file(./sample.txt ./Debug/sample.txt COPYONLY)
add_executable(MyProject main.cpp)