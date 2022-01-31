cmake_minimum_required(VERSION 2.8.12)
project(cnake)

add_subdirectory(pybind11-master)

if( $ENV{BUILD_TARGET} STREQUAL "linux")
    pybind11_add_module(c_writter lin_source.cpp)
else()
    pybind11_add_module(c_writter win_source.cpp)
endif()
