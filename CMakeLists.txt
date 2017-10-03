cmake_minimum_required(VERSION 3.8)
project(Systems)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES
        main.c
        Euler/euler.c
        Strings/strings.c test.c ArrayPointers/arrays_pointers.c Shell/shell.c StringFunctionDemonstrations/string_function_demos.c)
add_executable(Systems ${SOURCE_FILES})