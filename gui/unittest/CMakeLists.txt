cmake_minimum_required(VERSION 3.20)
project(LocalMinMax)

set(unittest_localminmax_gui_src Main.cpp)

enable_testing()

add_executable(unittest_localminmax_gui ${unittest_localminmax_gui_src})

find_package(Qt6 COMPONENTS Widgets Core Gui REQUIRED)
target_link_libraries(unittest_localminmax_gui PUBLIC
                      localminmax_gui
                      gtest
                      pthread
		              Qt6::Widgets
                      Qt6::Core
                      Qt6::Gui)
