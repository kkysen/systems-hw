cmake_minimum_required(VERSION 3.8)
project(Shell)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        aliases.c
        aliases.h
        builtins/builtins.c
        builtins/builtins.h
        builtins/cd.c
        builtins/cd.h
        shell.c
        shell.h
        shell_utils.c
        shell_utils.h
        util/sigaction.h
        util/stacktrace.c
        util/stacktrace.h
        test/test_argv.c
        util/utils.c
        util/utils.h
        argvv.c
        argvv.h
        preprocessing.c
        preprocessing.h
        util/str_utils.c
        util/str_utils.h
        shell_io.c
        shell_io.h
        builtins/exit.c
        builtins/exit.h
        builtins/alias.c
        builtins/alias.h
        builtins/unalias.c
        builtins/unalias.h
        builtins/source.c
        builtins/source.h
        util/io_utils.c
        util/io_utils.h
        test/test_str_utils.c
        run_commands.c
        run_commands.h
        util/pipes.c
        util/pipes.h
        util/semaphores.c
        util/semaphores.h
        util/shared_memory.c
        util/shared_memory.h
        util/shared_locks.c
        util/shared_locks.h
        util/string_builder.c
        util/string_builder.h
        test/test_string_builder.c
        builtins/pid.c
        builtins/pid.h
        chars.c
        )

add_executable(Shell ${SOURCE_FILES})

set(WIN_SOURCE_FILES
        aliases.c
        aliases.h
        builtins/builtins.c
        builtins/builtins.h
        builtins/cd.c
        builtins/cd.h
        shell.c
        shell.h
        shell_utils.c
        shell_utils.h
        util/utils.c
        util/utils.h
        argvv.c
        argvv.h
        preprocessing.c
        preprocessing.h
        util/str_utils.c
        util/str_utils.h
        shell_io.c
        shell_io.h
        builtins/exit.c
        builtins/exit.h
        builtins/alias.c
        builtins/alias.h
        builtins/unalias.c
        builtins/unalias.h
        builtins/source.c
        builtins/source.h
        util/io_utils.c
        util/io_utils.h
        )

add_executable(WinShell ${WIN_SOURCE_FILES})

add_executable(test_str_utils test/test_str_utils.c util/str_utils.c util/str_utils.h)