# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.18

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Disable VCS-based implicit rules.
% : %,v


# Disable VCS-based implicit rules.
% : RCS/%


# Disable VCS-based implicit rules.
% : RCS/%,v


# Disable VCS-based implicit rules.
% : SCCS/s.%


# Disable VCS-based implicit rules.
% : s.%


.SUFFIXES: .hpux_make_needs_suffix_list


# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

# Suppress display of executed commands.
$$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/joao/Documents/EAXXX/EA872/Projeto_872

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/joao/Documents/EAXXX/EA872/Projeto_872/build

# Include any dependencies generated for this target.
include CMakeFiles/Collisions.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Collisions.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Collisions.dir/flags.make

CMakeFiles/Collisions.dir/src/Controller/Collision.cpp.o: CMakeFiles/Collisions.dir/flags.make
CMakeFiles/Collisions.dir/src/Controller/Collision.cpp.o: ../src/Controller/Collision.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/joao/Documents/EAXXX/EA872/Projeto_872/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Collisions.dir/src/Controller/Collision.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Collisions.dir/src/Controller/Collision.cpp.o -c /home/joao/Documents/EAXXX/EA872/Projeto_872/src/Controller/Collision.cpp

CMakeFiles/Collisions.dir/src/Controller/Collision.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Collisions.dir/src/Controller/Collision.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/joao/Documents/EAXXX/EA872/Projeto_872/src/Controller/Collision.cpp > CMakeFiles/Collisions.dir/src/Controller/Collision.cpp.i

CMakeFiles/Collisions.dir/src/Controller/Collision.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Collisions.dir/src/Controller/Collision.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/joao/Documents/EAXXX/EA872/Projeto_872/src/Controller/Collision.cpp -o CMakeFiles/Collisions.dir/src/Controller/Collision.cpp.s

# Object files for target Collisions
Collisions_OBJECTS = \
"CMakeFiles/Collisions.dir/src/Controller/Collision.cpp.o"

# External object files for target Collisions
Collisions_EXTERNAL_OBJECTS =

libCollisions.a: CMakeFiles/Collisions.dir/src/Controller/Collision.cpp.o
libCollisions.a: CMakeFiles/Collisions.dir/build.make
libCollisions.a: CMakeFiles/Collisions.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/joao/Documents/EAXXX/EA872/Projeto_872/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libCollisions.a"
	$(CMAKE_COMMAND) -P CMakeFiles/Collisions.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Collisions.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Collisions.dir/build: libCollisions.a

.PHONY : CMakeFiles/Collisions.dir/build

CMakeFiles/Collisions.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Collisions.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Collisions.dir/clean

CMakeFiles/Collisions.dir/depend:
	cd /home/joao/Documents/EAXXX/EA872/Projeto_872/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/joao/Documents/EAXXX/EA872/Projeto_872 /home/joao/Documents/EAXXX/EA872/Projeto_872 /home/joao/Documents/EAXXX/EA872/Projeto_872/build /home/joao/Documents/EAXXX/EA872/Projeto_872/build /home/joao/Documents/EAXXX/EA872/Projeto_872/build/CMakeFiles/Collisions.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Collisions.dir/depend
