cmake_minimum_required(VERSION 3.5)
project(test1)

set(CMAKE_CXX_STANDARD 11)

add_executable(test1 test.cpp)

LINK_LIBRARIES(../cmake-build-debug)

target_link_libraries(test1 muduo)