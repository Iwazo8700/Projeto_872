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
include CMakeFiles/Config.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Config.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Config.dir/flags.make

CMakeFiles/Config.dir/src/Controller/ConfigReader.cpp.o: CMakeFiles/Config.dir/flags.make
CMakeFiles/Config.dir/src/Controller/ConfigReader.cpp.o: ../src/Controller/ConfigReader.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/joao/Documents/EAXXX/EA872/Projeto_872/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Config.dir/src/Controller/ConfigReader.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Config.dir/src/Controller/ConfigReader.cpp.o -c /home/joao/Documents/EAXXX/EA872/Projeto_872/src/Controller/ConfigReader.cpp

CMakeFiles/Config.dir/src/Controller/ConfigReader.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Config.dir/src/Controller/ConfigReader.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/joao/Documents/EAXXX/EA872/Projeto_872/src/Controller/ConfigReader.cpp > CMakeFiles/Config.dir/src/Controller/ConfigReader.cpp.i

CMakeFiles/Config.dir/src/Controller/ConfigReader.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Config.dir/src/Controller/ConfigReader.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/joao/Documents/EAXXX/EA872/Projeto_872/src/Controller/ConfigReader.cpp -o CMakeFiles/Config.dir/src/Controller/ConfigReader.cpp.s

# Object files for target Config
Config_OBJECTS = \
"CMakeFiles/Config.dir/src/Controller/ConfigReader.cpp.o"

# External object files for target Config
Config_EXTERNAL_OBJECTS =

libConfig.a: CMakeFiles/Config.dir/src/Controller/ConfigReader.cpp.o
libConfig.a: CMakeFiles/Config.dir/build.make
libConfig.a: CMakeFiles/Config.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/joao/Documents/EAXXX/EA872/Projeto_872/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libConfig.a"
	$(CMAKE_COMMAND) -P CMakeFiles/Config.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Config.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Config.dir/build: libConfig.a

.PHONY : CMakeFiles/Config.dir/build

CMakeFiles/Config.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Config.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Config.dir/clean

CMakeFiles/Config.dir/depend:
	cd /home/joao/Documents/EAXXX/EA872/Projeto_872/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/joao/Documents/EAXXX/EA872/Projeto_872 /home/joao/Documents/EAXXX/EA872/Projeto_872 /home/joao/Documents/EAXXX/EA872/Projeto_872/build /home/joao/Documents/EAXXX/EA872/Projeto_872/build /home/joao/Documents/EAXXX/EA872/Projeto_872/build/CMakeFiles/Config.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Config.dir/depend
