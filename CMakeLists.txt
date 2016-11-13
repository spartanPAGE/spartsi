cmake_minimum_required(VERSION 2.8.7)
project(spartsi)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")

# Includes Catch in the project;
include_directories(external/Catch/single_include)

include_directories(
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/external/boost/config/include
    ${CMAKE_SOURCE_DIR}/external/boost/assert/include
    ${CMAKE_SOURCE_DIR}/external/boost/static_assert/include
    ${CMAKE_SOURCE_DIR}/external/boost/intrusive/include
    ${CMAKE_SOURCE_DIR}/external/boost/type_traits/include
    ${CMAKE_SOURCE_DIR}/external/boost/core/include
    ${CMAKE_SOURCE_DIR}/external/boost/move/include
    ${CMAKE_SOURCE_DIR}/external/boost/variant/include
    ${CMAKE_SOURCE_DIR}/external/boost/container/include
    ${CMAKE_SOURCE_DIR}/external/boost/unordered/include
    ${CMAKE_SOURCE_DIR}/external/boost/functional/include
    ${CMAKE_SOURCE_DIR}/external/boost/iterator/include
    ${CMAKE_SOURCE_DIR}/external/boost/mpl/include
    ${CMAKE_SOURCE_DIR}/external/boost/preprocessor/include
    ${CMAKE_SOURCE_DIR}/external/boost/detail/include
    ${CMAKE_SOURCE_DIR}/external/boost/tuple/include
    ${CMAKE_SOURCE_DIR}/external/boost/throw_exception/include
    ${CMAKE_SOURCE_DIR}/external/boost/integer/include
    ${CMAKE_SOURCE_DIR}/external/boost/utility/include
    ${CMAKE_SOURCE_DIR}/external/boost/variant/include
    ${CMAKE_SOURCE_DIR}/external/boost/type_index/include
    ${CMAKE_SOURCE_DIR}/external/boost/math/include
)

set(SOURCE_FILES
    test/main.cpp
    test/utensils/history_keeping_map_test.cpp
    test/elementary_types_test.cpp
)

add_executable(spartsi ${SOURCE_FILES})


enable_testing(true)