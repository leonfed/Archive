cmake_minimum_required(VERSION 3.10)
project(my_lib)

set(CMAKE_CXX_STANDARD 17)

set(HEADERS tree.h
            archive.h
            unarchive.h)

set(SOURCES archive.cpp
            unarchive.cpp)

add_library(my_lib ${HEADERS} ${SOURCES})