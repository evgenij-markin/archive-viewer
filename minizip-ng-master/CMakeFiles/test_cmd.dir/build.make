# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/evgenij/Downloads/minizip-ng-master

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/evgenij/Downloads/minizip-ng-master

# Include any dependencies generated for this target.
include CMakeFiles/test_cmd.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/test_cmd.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/test_cmd.dir/flags.make

CMakeFiles/test_cmd.dir/test/test.c.o: CMakeFiles/test_cmd.dir/flags.make
CMakeFiles/test_cmd.dir/test/test.c.o: test/test.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/evgenij/Downloads/minizip-ng-master/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/test_cmd.dir/test/test.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/test_cmd.dir/test/test.c.o   -c /home/evgenij/Downloads/minizip-ng-master/test/test.c

CMakeFiles/test_cmd.dir/test/test.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/test_cmd.dir/test/test.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/evgenij/Downloads/minizip-ng-master/test/test.c > CMakeFiles/test_cmd.dir/test/test.c.i

CMakeFiles/test_cmd.dir/test/test.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/test_cmd.dir/test/test.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/evgenij/Downloads/minizip-ng-master/test/test.c -o CMakeFiles/test_cmd.dir/test/test.c.s

# Object files for target test_cmd
test_cmd_OBJECTS = \
"CMakeFiles/test_cmd.dir/test/test.c.o"

# External object files for target test_cmd
test_cmd_EXTERNAL_OBJECTS =

test_cmd: CMakeFiles/test_cmd.dir/test/test.c.o
test_cmd: CMakeFiles/test_cmd.dir/build.make
test_cmd: libminizip.a
test_cmd: CMakeFiles/test_cmd.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/evgenij/Downloads/minizip-ng-master/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable test_cmd"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test_cmd.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/test_cmd.dir/build: test_cmd

.PHONY : CMakeFiles/test_cmd.dir/build

CMakeFiles/test_cmd.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/test_cmd.dir/cmake_clean.cmake
.PHONY : CMakeFiles/test_cmd.dir/clean

CMakeFiles/test_cmd.dir/depend:
	cd /home/evgenij/Downloads/minizip-ng-master && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/evgenij/Downloads/minizip-ng-master /home/evgenij/Downloads/minizip-ng-master /home/evgenij/Downloads/minizip-ng-master /home/evgenij/Downloads/minizip-ng-master /home/evgenij/Downloads/minizip-ng-master/CMakeFiles/test_cmd.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/test_cmd.dir/depend

