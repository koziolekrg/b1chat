# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

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
CMAKE_SOURCE_DIR = /home/pako/b1communicator/client_test

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/pako/b1communicator/client_test-build

# Include any dependencies generated for this target.
include CMakeFiles/b1comm.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/b1comm.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/b1comm.dir/flags.make

CMakeFiles/b1comm.dir/main.cpp.o: CMakeFiles/b1comm.dir/flags.make
CMakeFiles/b1comm.dir/main.cpp.o: /home/pako/b1communicator/client_test/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pako/b1communicator/client_test-build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/b1comm.dir/main.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/b1comm.dir/main.cpp.o -c /home/pako/b1communicator/client_test/main.cpp

CMakeFiles/b1comm.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/b1comm.dir/main.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/pako/b1communicator/client_test/main.cpp > CMakeFiles/b1comm.dir/main.cpp.i

CMakeFiles/b1comm.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/b1comm.dir/main.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/pako/b1communicator/client_test/main.cpp -o CMakeFiles/b1comm.dir/main.cpp.s

CMakeFiles/b1comm.dir/main.cpp.o.requires:

.PHONY : CMakeFiles/b1comm.dir/main.cpp.o.requires

CMakeFiles/b1comm.dir/main.cpp.o.provides: CMakeFiles/b1comm.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/b1comm.dir/build.make CMakeFiles/b1comm.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/b1comm.dir/main.cpp.o.provides

CMakeFiles/b1comm.dir/main.cpp.o.provides.build: CMakeFiles/b1comm.dir/main.cpp.o


CMakeFiles/b1comm.dir/src/client.cpp.o: CMakeFiles/b1comm.dir/flags.make
CMakeFiles/b1comm.dir/src/client.cpp.o: /home/pako/b1communicator/client_test/src/client.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pako/b1communicator/client_test-build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/b1comm.dir/src/client.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/b1comm.dir/src/client.cpp.o -c /home/pako/b1communicator/client_test/src/client.cpp

CMakeFiles/b1comm.dir/src/client.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/b1comm.dir/src/client.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/pako/b1communicator/client_test/src/client.cpp > CMakeFiles/b1comm.dir/src/client.cpp.i

CMakeFiles/b1comm.dir/src/client.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/b1comm.dir/src/client.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/pako/b1communicator/client_test/src/client.cpp -o CMakeFiles/b1comm.dir/src/client.cpp.s

CMakeFiles/b1comm.dir/src/client.cpp.o.requires:

.PHONY : CMakeFiles/b1comm.dir/src/client.cpp.o.requires

CMakeFiles/b1comm.dir/src/client.cpp.o.provides: CMakeFiles/b1comm.dir/src/client.cpp.o.requires
	$(MAKE) -f CMakeFiles/b1comm.dir/build.make CMakeFiles/b1comm.dir/src/client.cpp.o.provides.build
.PHONY : CMakeFiles/b1comm.dir/src/client.cpp.o.provides

CMakeFiles/b1comm.dir/src/client.cpp.o.provides.build: CMakeFiles/b1comm.dir/src/client.cpp.o


CMakeFiles/b1comm.dir/src/receive.cpp.o: CMakeFiles/b1comm.dir/flags.make
CMakeFiles/b1comm.dir/src/receive.cpp.o: /home/pako/b1communicator/client_test/src/receive.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pako/b1communicator/client_test-build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/b1comm.dir/src/receive.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/b1comm.dir/src/receive.cpp.o -c /home/pako/b1communicator/client_test/src/receive.cpp

CMakeFiles/b1comm.dir/src/receive.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/b1comm.dir/src/receive.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/pako/b1communicator/client_test/src/receive.cpp > CMakeFiles/b1comm.dir/src/receive.cpp.i

CMakeFiles/b1comm.dir/src/receive.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/b1comm.dir/src/receive.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/pako/b1communicator/client_test/src/receive.cpp -o CMakeFiles/b1comm.dir/src/receive.cpp.s

CMakeFiles/b1comm.dir/src/receive.cpp.o.requires:

.PHONY : CMakeFiles/b1comm.dir/src/receive.cpp.o.requires

CMakeFiles/b1comm.dir/src/receive.cpp.o.provides: CMakeFiles/b1comm.dir/src/receive.cpp.o.requires
	$(MAKE) -f CMakeFiles/b1comm.dir/build.make CMakeFiles/b1comm.dir/src/receive.cpp.o.provides.build
.PHONY : CMakeFiles/b1comm.dir/src/receive.cpp.o.provides

CMakeFiles/b1comm.dir/src/receive.cpp.o.provides.build: CMakeFiles/b1comm.dir/src/receive.cpp.o


# Object files for target b1comm
b1comm_OBJECTS = \
"CMakeFiles/b1comm.dir/main.cpp.o" \
"CMakeFiles/b1comm.dir/src/client.cpp.o" \
"CMakeFiles/b1comm.dir/src/receive.cpp.o"

# External object files for target b1comm
b1comm_EXTERNAL_OBJECTS =

b1comm: CMakeFiles/b1comm.dir/main.cpp.o
b1comm: CMakeFiles/b1comm.dir/src/client.cpp.o
b1comm: CMakeFiles/b1comm.dir/src/receive.cpp.o
b1comm: CMakeFiles/b1comm.dir/build.make
b1comm: CMakeFiles/b1comm.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/pako/b1communicator/client_test-build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable b1comm"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/b1comm.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/b1comm.dir/build: b1comm

.PHONY : CMakeFiles/b1comm.dir/build

CMakeFiles/b1comm.dir/requires: CMakeFiles/b1comm.dir/main.cpp.o.requires
CMakeFiles/b1comm.dir/requires: CMakeFiles/b1comm.dir/src/client.cpp.o.requires
CMakeFiles/b1comm.dir/requires: CMakeFiles/b1comm.dir/src/receive.cpp.o.requires

.PHONY : CMakeFiles/b1comm.dir/requires

CMakeFiles/b1comm.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/b1comm.dir/cmake_clean.cmake
.PHONY : CMakeFiles/b1comm.dir/clean

CMakeFiles/b1comm.dir/depend:
	cd /home/pako/b1communicator/client_test-build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/pako/b1communicator/client_test /home/pako/b1communicator/client_test /home/pako/b1communicator/client_test-build /home/pako/b1communicator/client_test-build /home/pako/b1communicator/client_test-build/CMakeFiles/b1comm.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/b1comm.dir/depend

