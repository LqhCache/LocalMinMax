cmake_minimum_required(VERSION 3.20)
project(LocalMinMax)

set(defectresolver_src DistDefectResolver.cpp)

add_library(localminmax_defectresolver ${defectresolver_src})

target_link_libraries(localminmax_defectresolver PUBLIC 
                      localminmax_measurement
                      localminmax_common)

add_subdirectory(unittest)