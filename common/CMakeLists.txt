cmake_minimum_required(VERSION 3.20)
project(LocalMinMax)

set(common_src GeometryAlgo.cpp)

add_library(localminmax_common ${common_src})

add_subdirectory(unittest)