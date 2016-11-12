cmake_minimum_required(VERSION 2.8.7)
project(spartsi)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y")

# Includes Catch in the project;
include_directories(external/Catch)
enable_testing(true)

include_directories(
    ${PROJECT_SOURCE_DIR}/src
)
set(SOURCE_FILES main.cpp test/example_test.cpp)

add_executable(spartsi ${SOURCE_FILES})