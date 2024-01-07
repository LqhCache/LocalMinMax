cmake_minimum_required(VERSION 3.20)
project(LocalMinMax)

set(controller_src Controller.cpp)

add_library(localminmax_controller ${controller_src})

target_link_libraries(localminmax_controller PUBLIC 
                      localminmax_common
                      localminmax_measurement
                      localminmax_defectresolver)

add_subdirectory(unittest)
add_subdirectory(moduletest)