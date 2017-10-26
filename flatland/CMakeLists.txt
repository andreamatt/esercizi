cmake_minimum_required(VERSION 3.8)
project(flatland)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp helpers.h)
add_executable(flatland ${SOURCE_FILES})