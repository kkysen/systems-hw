# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.8

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /cygdrive/c/Users/kkyse/.CLion2017.2/system/cygwin_cmake/bin/cmake.exe

# The command to remove a file.
RM = /cygdrive/c/Users/kkyse/.CLion2017.2/system/cygwin_cmake/bin/cmake.exe -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /cygdrive/c/Users/kkyse/workspace/Systems/Khyber

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /cygdrive/c/Users/kkyse/workspace/Systems/Khyber/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/Khyber.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Khyber.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Khyber.dir/flags.make

CMakeFiles/Khyber.dir/alias.c.o: CMakeFiles/Khyber.dir/flags.make
CMakeFiles/Khyber.dir/alias.c.o: ../alias.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/cygdrive/c/Users/kkyse/workspace/Systems/Khyber/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/Khyber.dir/alias.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Khyber.dir/alias.c.o   -c /cygdrive/c/Users/kkyse/workspace/Systems/Khyber/alias.c

CMakeFiles/Khyber.dir/alias.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Khyber.dir/alias.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /cygdrive/c/Users/kkyse/workspace/Systems/Khyber/alias.c > CMakeFiles/Khyber.dir/alias.c.i

CMakeFiles/Khyber.dir/alias.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Khyber.dir/alias.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /cygdrive/c/Users/kkyse/workspace/Systems/Khyber/alias.c -o CMakeFiles/Khyber.dir/alias.c.s

CMakeFiles/Khyber.dir/alias.c.o.requires:

.PHONY : CMakeFiles/Khyber.dir/alias.c.o.requires

CMakeFiles/Khyber.dir/alias.c.o.provides: CMakeFiles/Khyber.dir/alias.c.o.requires
	$(MAKE) -f CMakeFiles/Khyber.dir/build.make CMakeFiles/Khyber.dir/alias.c.o.provides.build
.PHONY : CMakeFiles/Khyber.dir/alias.c.o.provides

CMakeFiles/Khyber.dir/alias.c.o.provides.build: CMakeFiles/Khyber.dir/alias.c.o


CMakeFiles/Khyber.dir/io.c.o: CMakeFiles/Khyber.dir/flags.make
CMakeFiles/Khyber.dir/io.c.o: ../io.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/cygdrive/c/Users/kkyse/workspace/Systems/Khyber/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/Khyber.dir/io.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Khyber.dir/io.c.o   -c /cygdrive/c/Users/kkyse/workspace/Systems/Khyber/io.c

CMakeFiles/Khyber.dir/io.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Khyber.dir/io.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /cygdrive/c/Users/kkyse/workspace/Systems/Khyber/io.c > CMakeFiles/Khyber.dir/io.c.i

CMakeFiles/Khyber.dir/io.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Khyber.dir/io.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /cygdrive/c/Users/kkyse/workspace/Systems/Khyber/io.c -o CMakeFiles/Khyber.dir/io.c.s

CMakeFiles/Khyber.dir/io.c.o.requires:

.PHONY : CMakeFiles/Khyber.dir/io.c.o.requires

CMakeFiles/Khyber.dir/io.c.o.provides: CMakeFiles/Khyber.dir/io.c.o.requires
	$(MAKE) -f CMakeFiles/Khyber.dir/build.make CMakeFiles/Khyber.dir/io.c.o.provides.build
.PHONY : CMakeFiles/Khyber.dir/io.c.o.provides

CMakeFiles/Khyber.dir/io.c.o.provides.build: CMakeFiles/Khyber.dir/io.c.o


CMakeFiles/Khyber.dir/python.c.o: CMakeFiles/Khyber.dir/flags.make
CMakeFiles/Khyber.dir/python.c.o: ../python.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/cygdrive/c/Users/kkyse/workspace/Systems/Khyber/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/Khyber.dir/python.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Khyber.dir/python.c.o   -c /cygdrive/c/Users/kkyse/workspace/Systems/Khyber/python.c

CMakeFiles/Khyber.dir/python.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Khyber.dir/python.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /cygdrive/c/Users/kkyse/workspace/Systems/Khyber/python.c > CMakeFiles/Khyber.dir/python.c.i

CMakeFiles/Khyber.dir/python.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Khyber.dir/python.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /cygdrive/c/Users/kkyse/workspace/Systems/Khyber/python.c -o CMakeFiles/Khyber.dir/python.c.s

CMakeFiles/Khyber.dir/python.c.o.requires:

.PHONY : CMakeFiles/Khyber.dir/python.c.o.requires

CMakeFiles/Khyber.dir/python.c.o.provides: CMakeFiles/Khyber.dir/python.c.o.requires
	$(MAKE) -f CMakeFiles/Khyber.dir/build.make CMakeFiles/Khyber.dir/python.c.o.provides.build
.PHONY : CMakeFiles/Khyber.dir/python.c.o.provides

CMakeFiles/Khyber.dir/python.c.o.provides.build: CMakeFiles/Khyber.dir/python.c.o


# Object files for target Khyber
Khyber_OBJECTS = \
"CMakeFiles/Khyber.dir/alias.c.o" \
"CMakeFiles/Khyber.dir/io.c.o" \
"CMakeFiles/Khyber.dir/python.c.o"

# External object files for target Khyber
Khyber_EXTERNAL_OBJECTS =

Khyber.exe: CMakeFiles/Khyber.dir/alias.c.o
Khyber.exe: CMakeFiles/Khyber.dir/io.c.o
Khyber.exe: CMakeFiles/Khyber.dir/python.c.o
Khyber.exe: CMakeFiles/Khyber.dir/build.make
Khyber.exe: CMakeFiles/Khyber.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/cygdrive/c/Users/kkyse/workspace/Systems/Khyber/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking C executable Khyber.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Khyber.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Khyber.dir/build: Khyber.exe

.PHONY : CMakeFiles/Khyber.dir/build

CMakeFiles/Khyber.dir/requires: CMakeFiles/Khyber.dir/alias.c.o.requires
CMakeFiles/Khyber.dir/requires: CMakeFiles/Khyber.dir/io.c.o.requires
CMakeFiles/Khyber.dir/requires: CMakeFiles/Khyber.dir/python.c.o.requires

.PHONY : CMakeFiles/Khyber.dir/requires

CMakeFiles/Khyber.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Khyber.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Khyber.dir/clean

CMakeFiles/Khyber.dir/depend:
	cd /cygdrive/c/Users/kkyse/workspace/Systems/Khyber/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /cygdrive/c/Users/kkyse/workspace/Systems/Khyber /cygdrive/c/Users/kkyse/workspace/Systems/Khyber /cygdrive/c/Users/kkyse/workspace/Systems/Khyber/cmake-build-debug /cygdrive/c/Users/kkyse/workspace/Systems/Khyber/cmake-build-debug /cygdrive/c/Users/kkyse/workspace/Systems/Khyber/cmake-build-debug/CMakeFiles/Khyber.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Khyber.dir/depend
