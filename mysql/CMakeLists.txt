cmake_minimum_required(VERSION 3.20)
project(LocalMinMax)

set(mysql_src Mysql.cpp)

add_library(localminmax_mysql ${mysql_src})

target_link_libraries(localminmax_mysql PUBLIC 
                      mysqlclient)

add_subdirectory(unittest)