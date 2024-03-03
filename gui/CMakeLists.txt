cmake_minimum_required(VERSION 3.20)
project(LocalMinMax)

set(gui_src MainWindow.cpp)

add_library(localminmax_gui ${gui_src})

add_subdirectory(unittest)