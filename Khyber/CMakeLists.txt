cmake_minimum_required(VERSION 3.8)
project(Khyber)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        alias.c
        alias.h
        fb.h
        io.c
        io.h
        python.c
        python.h)

add_executable(Khyber ${SOURCE_FILES})