cmake_minimum_required(VERSION 3.8)
project(sorting)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp oldMergeSort.h)
add_executable(sorting ${SOURCE_FILES})