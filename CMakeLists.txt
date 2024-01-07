cmake_minimum_required(VERSION 3.20)
project(LocalMinMax)

include_directories($(CMAKE_CURRENT_BINARY_DIR))

add_subdirectory(common)
add_subdirectory(defectresolver)
add_subdirectory(measurement)
