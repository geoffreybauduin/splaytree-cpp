cmake_minimum_required(VERSION 2.6)

project(run)

include_directories(
    GLOB_RECURSE
    ${CMAKE_CURRENT_SOURCE_DIR}/headers/
)

file(
    GLOB_RECURSE
    source_files
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*
)

SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -std=c++11 -g -ggdb")
SET(CMAKE_CXX_COMPILER "g++")

list(REMOVE_ITEM source_files ${CMAKE_CURRENT_SOURCE_DIR}/src/Tester.cpp)

add_executable(
	splaytree
	${source_files}
	${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
)

add_executable(
	unit_test
	${source_files}
	${CMAKE_CURRENT_SOURCE_DIR}/test.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/Tester.cpp
)
