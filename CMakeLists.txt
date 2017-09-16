cmake_minimum_required(VERSION 3.8)
project(Systems)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES
        main.c
        Euler/euler.c)
add_executable(Systems ${SOURCE_FILES})