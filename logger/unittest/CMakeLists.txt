cmake_minimum_required(VERSION 3.20)
project(LocalMinMax)

set(unittest_localminmax_logger_src Main.cpp
                                    LoggerTest.cpp)

enable_testing()

add_executable(unittest_localminmax_logger ${unittest_localminmax_logger_src})

target_link_libraries(unittest_localminmax_logger PUBLIC
                      localminmax_logger
                      localminmax_common
                      gtest
                      pthread)
