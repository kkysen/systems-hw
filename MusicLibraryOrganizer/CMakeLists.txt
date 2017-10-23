cmake_minimum_required(VERSION 3.8)
project(MusicLibraryOrganizer)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        main.c
        main.h
        song.c
        song.h
        song_library.c
        song_library.h
        song_node.c
        song_node.h)

add_executable(MusicLibraryOrganizer ${SOURCE_FILES})