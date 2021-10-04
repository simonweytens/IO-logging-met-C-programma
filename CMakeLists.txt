cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
project(Opdracht1)

add_executable(Opdracht1 test.c)
include_directories(/usr/include/mariadb /usr/include/mariadb/mysql)

target_link_libraries(Opdracht1 mariadb)
target_link_libraries(Opdracht1 PJ_RPI)
