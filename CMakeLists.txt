cmake_minimum_required(VERSION 3.22)

#include(ubuntu-arm64-clang.cmake)

project(grpc-test
        VERSION 1.0.0
        DESCRIPTION "How grpc works"
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED 23)
set(CMAKE_POSITION_INDEPENDENT_CODE TRUE)

add_executable(client)

target_sources(client
        PRIVATE
        main.cpp)