cmake_minimum_required(VERSION 3.20)
project(LocalMinMax)

set(controller_module_src Main.cpp)

add_executable(moduletest_localminmax_controller ${controller_module_src})

target_link_libraries(moduletest_localminmax_controller PUBLIC 
                      mysqlclient
                      localminmax_common
                      localminmax_measurement
                      localminmax_defectresolver)
