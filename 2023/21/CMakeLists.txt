cmake_minimum_required(VERSION 3.20)

project(21)
set(CMAKE_CXX_STANDARD 17)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input.txt
	       ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)

add_executable(1_Step_Counter main.cpp)
add_executable(2_Step_Counter main2.cpp)
