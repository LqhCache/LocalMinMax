cmake_minimum_required(VERSION 3.20)
project(LocalMinMax)

include_directories($(CMAKE_CURRENT_BINARY_DIR))

set(CMAKE_PREFIX_PATH /home/liuqianhua/Qt/6.6.2/gcc_64)

add_subdirectory(common)
add_subdirectory(defectresolver)
add_subdirectory(measurement)
add_subdirectory(controller)
add_subdirectory(logger)
add_subdirectory(mysql)
add_subdirectory(parser)
add_subdirectory(gui)
