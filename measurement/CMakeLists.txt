cmake_minimum_required(VERSION 3.20)
project(LocalMinMax)

set(measurement_src MeasurePath.cpp
                    MeasurePoint.cpp)

add_library(localminmax_measurement ${measurement_src})

target_link_libraries(localminmax_measurement PUBLIC 
                      localminmax_common)

add_subdirectory(unittest)