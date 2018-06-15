cmake_minimum_required(VERSION 3.10)
project(myArchive)

set(CMAKE_CXX_STANDARD 17)

if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11 -pedantic")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fsanitize=address,undefined -D_GLIBCXX_DEBUG")
    set(CMAKE_CXX_FLAGS_COVERAGE "${CMAKE_CXX_FLAGS} -Wall -std=c++11 -O3 -fprofile-arcs -ftest-coverage -pedantic")
    set(CMAKE_CXX_OUTPUT_EXTENSION_REPLACE ON)
endif()


add_subdirectory(my_lib)

add_executable(myArchive_testing
               myArchive_testing.cpp
               gtest/gtest.h
               gtest/gtest-all.cc
               gtest/gtest_main.cc)

add_executable(myArchive
               my_utility.cpp)


target_link_libraries(myArchive my_lib)

target_link_libraries(myArchive_testing my_lib -fprofile-arcs -lpthread)
