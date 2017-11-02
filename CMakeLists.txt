cmake_minimum_required(VERSION 3.8)
project(Systems)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES
        main.c
        Euler/euler.c
        test.c
        ArrayPointers/arrays_pointers.c
        Shell/shell.c
        StringFunctionDemonstrations/string_function_demos.c
        Strings/string_funcs.c
        Strings/string_tests.c
        Strings/fb.h
        Strings/alias.c
        Strings/io.c
        Strings/python.c
        BackupStrings/string_funcs.c
        BackupStrings/string_tests.c
        LinkedList/linked_list.c LinkedList/linked_list_test.c LinkedList/linked_list_test.h MusicLibraryOrganizer/song_node.c MusicLibraryOrganizer/song_node.h MusicLibraryOrganizer/song_library.c MusicLibraryOrganizer/song_library.h MusicLibraryOrganizer/song.c MusicLibraryOrganizer/song.h MusicLibraryOrganizer/main.c MusicLibraryOrganizer/main.h Stacktrace/stacktrace.c Stacktrace/stacktrace.h GccStrncpyBug/gcc_strncpy_bypass_bug.c GccStrncpyBug/gcc_strncpy_cause_bug.c DevRandom/read_random.c)
add_executable(Systems ${SOURCE_FILES})