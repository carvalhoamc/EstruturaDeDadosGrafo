# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.7

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
CMAKE_COMMAND = /home/amc/clion-2017.1.2/bin/cmake/bin/cmake

# The command to remove a file.
RM = /home/amc/clion-2017.1.2/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/amc/Dropbox/src/uri1270

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/amc/Dropbox/src/uri1270/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/uri1270.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/uri1270.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/uri1270.dir/flags.make

CMakeFiles/uri1270.dir/main.cpp.o: CMakeFiles/uri1270.dir/flags.make
CMakeFiles/uri1270.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/amc/Dropbox/src/uri1270/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/uri1270.dir/main.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/uri1270.dir/main.cpp.o -c /home/amc/Dropbox/src/uri1270/main.cpp

CMakeFiles/uri1270.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/uri1270.dir/main.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/amc/Dropbox/src/uri1270/main.cpp > CMakeFiles/uri1270.dir/main.cpp.i

CMakeFiles/uri1270.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/uri1270.dir/main.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/amc/Dropbox/src/uri1270/main.cpp -o CMakeFiles/uri1270.dir/main.cpp.s

CMakeFiles/uri1270.dir/main.cpp.o.requires:

.PHONY : CMakeFiles/uri1270.dir/main.cpp.o.requires

CMakeFiles/uri1270.dir/main.cpp.o.provides: CMakeFiles/uri1270.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/uri1270.dir/build.make CMakeFiles/uri1270.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/uri1270.dir/main.cpp.o.provides

CMakeFiles/uri1270.dir/main.cpp.o.provides.build: CMakeFiles/uri1270.dir/main.cpp.o


# Object files for target uri1270
uri1270_OBJECTS = \
"CMakeFiles/uri1270.dir/main.cpp.o"

# External object files for target uri1270
uri1270_EXTERNAL_OBJECTS =

uri1270: CMakeFiles/uri1270.dir/main.cpp.o
uri1270: CMakeFiles/uri1270.dir/build.make
uri1270: CMakeFiles/uri1270.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/amc/Dropbox/src/uri1270/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable uri1270"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/uri1270.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/uri1270.dir/build: uri1270

.PHONY : CMakeFiles/uri1270.dir/build

CMakeFiles/uri1270.dir/requires: CMakeFiles/uri1270.dir/main.cpp.o.requires

.PHONY : CMakeFiles/uri1270.dir/requires

CMakeFiles/uri1270.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/uri1270.dir/cmake_clean.cmake
.PHONY : CMakeFiles/uri1270.dir/clean

CMakeFiles/uri1270.dir/depend:
	cd /home/amc/Dropbox/src/uri1270/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/amc/Dropbox/src/uri1270 /home/amc/Dropbox/src/uri1270 /home/amc/Dropbox/src/uri1270/cmake-build-debug /home/amc/Dropbox/src/uri1270/cmake-build-debug /home/amc/Dropbox/src/uri1270/cmake-build-debug/CMakeFiles/uri1270.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/uri1270.dir/depend
