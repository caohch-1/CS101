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
CMAKE_SOURCE_DIR = /mnt/d/Project/CLionProjects/CS101/cs101_hw3

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/d/Project/CLionProjects/CS101/cs101_hw3/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/hw3.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/hw3.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/hw3.dir/flags.make

CMakeFiles/hw3.dir/q3.cpp.o: CMakeFiles/hw3.dir/flags.make
CMakeFiles/hw3.dir/q3.cpp.o: ../q3.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/d/Project/CLionProjects/CS101/cs101_hw3/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/hw3.dir/q3.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/hw3.dir/q3.cpp.o -c /mnt/d/Project/CLionProjects/CS101/cs101_hw3/q3.cpp

CMakeFiles/hw3.dir/q3.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/hw3.dir/q3.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/d/Project/CLionProjects/CS101/cs101_hw3/q3.cpp > CMakeFiles/hw3.dir/q3.cpp.i

CMakeFiles/hw3.dir/q3.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/hw3.dir/q3.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/d/Project/CLionProjects/CS101/cs101_hw3/q3.cpp -o CMakeFiles/hw3.dir/q3.cpp.s

# Object files for target hw3
hw3_OBJECTS = \
"CMakeFiles/hw3.dir/q3.cpp.o"

# External object files for target hw3
hw3_EXTERNAL_OBJECTS =

hw3: CMakeFiles/hw3.dir/q3.cpp.o
hw3: CMakeFiles/hw3.dir/build.make
hw3: CMakeFiles/hw3.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/d/Project/CLionProjects/CS101/cs101_hw3/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable hw3"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/hw3.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/hw3.dir/build: hw3

.PHONY : CMakeFiles/hw3.dir/build

CMakeFiles/hw3.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/hw3.dir/cmake_clean.cmake
.PHONY : CMakeFiles/hw3.dir/clean

CMakeFiles/hw3.dir/depend:
	cd /mnt/d/Project/CLionProjects/CS101/cs101_hw3/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/d/Project/CLionProjects/CS101/cs101_hw3 /mnt/d/Project/CLionProjects/CS101/cs101_hw3 /mnt/d/Project/CLionProjects/CS101/cs101_hw3/cmake-build-debug /mnt/d/Project/CLionProjects/CS101/cs101_hw3/cmake-build-debug /mnt/d/Project/CLionProjects/CS101/cs101_hw3/cmake-build-debug/CMakeFiles/hw3.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/hw3.dir/depend
