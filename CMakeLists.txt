cmake_minimum_required(VERSION 3.6)
project(muduo)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES muduo.cpp)

add_library(muduo ${SOURCE_FILES})

#target_link_libraries(muduo -lc -lpthread)