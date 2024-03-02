cmake_minimum_required(VERSION 3.20)
project(LocalMinMax)

set(parser_src Parser.cpp)

add_library(localminmax_parser ${parser_src})

add_subdirectory(unittest)