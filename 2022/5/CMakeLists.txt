cmake_minimum_required(VERSION 3.20)

project(5)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input.txt
	       ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)

add_executable(1_supply_stacks main.cpp)
add_executable(2_supply_stacks main2.cpp)
