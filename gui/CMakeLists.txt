cmake_minimum_required(VERSION 3.20)
project(LocalMinMax)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(gui_src MainWindow.cpp
            forms/MainWindow.ui)

add_library(localminmax_gui ${gui_src})

find_package(Qt5 COMPONENTS Widgets Core Gui REQUIRED)
target_link_libraries(localminmax_gui PUBLIC
                      gtest
                      pthread
		              Qt5::Widgets
                      Qt5::Core
                      Qt5::Gui)

add_subdirectory(unittest)