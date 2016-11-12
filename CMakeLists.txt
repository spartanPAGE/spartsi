cmake_minimum_required(VERSION 2.8.7)
project(spartsi)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")

# Includes Catch in the project;
include_directories(external/Catch/single_include)

include_directories(${CMAKE_SOURCE_DIR})
include_directories(${CMAKE_SOURCE_DIR}/src)

set(SOURCE_FILES
    test/main.cpp
    test/utensils/history_keeping_map_test.cpp
)

add_executable(spartsi ${SOURCE_FILES})


enable_testing(true)