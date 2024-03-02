cmake_minimum_required(VERSION 3.20)
project(LocalMinMax)

set(logger_src Logger.cpp)

add_library(localminmax_logger ${logger_src})

target_link_libraries(localminmax_logger PUBLIC 
                      localminmax_common)

add_subdirectory(unittest)