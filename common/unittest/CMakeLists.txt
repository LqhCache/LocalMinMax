cmake_minimum_required(VERSION 3.20)
project(LocalMinMax)

set(unittest_localminmax_common_src Main.cpp
                                    GeometryAlgoTest.cpp)

enable_testing()

add_executable(unittest_localminmax_common ${unittest_localminmax_common_src})

target_link_libraries(unittest_localminmax_common PUBLIC
                      localminmax_common
                      gtest
                      pthread)
