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
CMAKE_SOURCE_DIR = /home/ctrlz/workSpace/MyServer

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ctrlz/workSpace/MyServer/build

# Include any dependencies generated for this target.
include CMakeFiles/Client.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Client.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Client.dir/flags.make

CMakeFiles/Client.dir/src/Client.cpp.o: CMakeFiles/Client.dir/flags.make
CMakeFiles/Client.dir/src/Client.cpp.o: ../src/Client.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ctrlz/workSpace/MyServer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Client.dir/src/Client.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Client.dir/src/Client.cpp.o -c /home/ctrlz/workSpace/MyServer/src/Client.cpp

CMakeFiles/Client.dir/src/Client.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Client.dir/src/Client.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ctrlz/workSpace/MyServer/src/Client.cpp > CMakeFiles/Client.dir/src/Client.cpp.i

CMakeFiles/Client.dir/src/Client.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Client.dir/src/Client.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ctrlz/workSpace/MyServer/src/Client.cpp -o CMakeFiles/Client.dir/src/Client.cpp.s

# Object files for target Client
Client_OBJECTS = \
"CMakeFiles/Client.dir/src/Client.cpp.o"

# External object files for target Client
Client_EXTERNAL_OBJECTS =

Client: CMakeFiles/Client.dir/src/Client.cpp.o
Client: CMakeFiles/Client.dir/build.make
Client: libISock_library.so
Client: CMakeFiles/Client.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/ctrlz/workSpace/MyServer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Client"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Client.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Client.dir/build: Client

.PHONY : CMakeFiles/Client.dir/build

CMakeFiles/Client.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Client.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Client.dir/clean

CMakeFiles/Client.dir/depend:
	cd /home/ctrlz/workSpace/MyServer/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ctrlz/workSpace/MyServer /home/ctrlz/workSpace/MyServer /home/ctrlz/workSpace/MyServer/build /home/ctrlz/workSpace/MyServer/build /home/ctrlz/workSpace/MyServer/build/CMakeFiles/Client.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Client.dir/depend

