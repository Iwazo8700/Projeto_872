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
include CMakeFiles/Image.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Image.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Image.dir/flags.make

CMakeFiles/Image.dir/src/Model/Image.cpp.o: CMakeFiles/Image.dir/flags.make
CMakeFiles/Image.dir/src/Model/Image.cpp.o: ../src/Model/Image.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/joao/Documents/EAXXX/EA872/Projeto_872/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Image.dir/src/Model/Image.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Image.dir/src/Model/Image.cpp.o -c /home/joao/Documents/EAXXX/EA872/Projeto_872/src/Model/Image.cpp

CMakeFiles/Image.dir/src/Model/Image.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Image.dir/src/Model/Image.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/joao/Documents/EAXXX/EA872/Projeto_872/src/Model/Image.cpp > CMakeFiles/Image.dir/src/Model/Image.cpp.i

CMakeFiles/Image.dir/src/Model/Image.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Image.dir/src/Model/Image.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/joao/Documents/EAXXX/EA872/Projeto_872/src/Model/Image.cpp -o CMakeFiles/Image.dir/src/Model/Image.cpp.s

# Object files for target Image
Image_OBJECTS = \
"CMakeFiles/Image.dir/src/Model/Image.cpp.o"

# External object files for target Image
Image_EXTERNAL_OBJECTS =

libImage.a: CMakeFiles/Image.dir/src/Model/Image.cpp.o
libImage.a: CMakeFiles/Image.dir/build.make
libImage.a: CMakeFiles/Image.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/joao/Documents/EAXXX/EA872/Projeto_872/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libImage.a"
	$(CMAKE_COMMAND) -P CMakeFiles/Image.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Image.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Image.dir/build: libImage.a

.PHONY : CMakeFiles/Image.dir/build

CMakeFiles/Image.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Image.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Image.dir/clean

CMakeFiles/Image.dir/depend:
	cd /home/joao/Documents/EAXXX/EA872/Projeto_872/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/joao/Documents/EAXXX/EA872/Projeto_872 /home/joao/Documents/EAXXX/EA872/Projeto_872 /home/joao/Documents/EAXXX/EA872/Projeto_872/build /home/joao/Documents/EAXXX/EA872/Projeto_872/build /home/joao/Documents/EAXXX/EA872/Projeto_872/build/CMakeFiles/Image.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Image.dir/depend

