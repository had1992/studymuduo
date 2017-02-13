cmake_minimum_required(VERSION 3.6)
project(muduo)

LINK_DIRECTORIES(./)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES muduo.cpp)

set(reactor_files ./reactor/EventLoop.cpp)

add_library(muduo ${SOURCE_FILES} ${reactor_files})

#target_link_libraries(muduo -lc -lpthread)