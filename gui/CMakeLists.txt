cmake_minimum_required(VERSION 3.20)
project(LocalMinMax)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(gui_src MainWindow.cpp
            SlidePage.cpp
            GuiWidgets.cpp
            ScrollContainer.cpp
            View.cpp
            forms/MainWindow.ui)

add_library(localminmax_gui ${gui_src})

find_package(Qt6 COMPONENTS Widgets Core Gui Svg REQUIRED)
target_link_libraries(localminmax_gui PUBLIC
                      gtest
                      pthread
		              Qt6::Widgets
                      Qt6::Core
                      Qt6::Gui
                      Qt6::Svg)

add_subdirectory(unittest)