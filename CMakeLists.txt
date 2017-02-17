cmake_minimum_required(VERSION 3.5)
project(muduo)

set(CMAKE_CXX_STANDARD 11)

set(MUDUO_SOURCE_FILES muduo.cpp)

aux_source_directory(reactor REACTOR_SOURCE_FILES)
message("reactor dir: ${REACTOR_SOURCE_FILES}")

aux_source_directory(base BASE_SOURCE_FILES)
message("base dir: ${BASE_SOURCE_FILES}")

add_library(muduo ${MUDUO_SOURCE_FILES} ${REACTOR_SOURCE_FILES} ${BASE_SOURCE_FILES})

add_subdirectory(test)
