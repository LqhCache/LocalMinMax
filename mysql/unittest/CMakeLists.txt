cmake_minimum_required(VERSION 3.20)
project(LocalMinMax)

set(unittest_localminmax_mysql_src Main.cpp
                                   MysqlTest.cpp)

enable_testing()

add_executable(unittest_localminmax_mysql ${unittest_localminmax_mysql_src})

target_link_libraries(unittest_localminmax_mysql PUBLIC
                      localminmax_mysql
                      gtest
                      pthread)
