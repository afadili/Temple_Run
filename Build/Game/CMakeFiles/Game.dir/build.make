# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

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
CMAKE_SOURCE_DIR = "/home/amina/Desktop/Temple Run"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/home/amina/Desktop/Temple Run/Build"

# Include any dependencies generated for this target.
include Game/CMakeFiles/Game.dir/depend.make

# Include the progress variables for this target.
include Game/CMakeFiles/Game.dir/progress.make

# Include the compile flags for this target's objects.
include Game/CMakeFiles/Game.dir/flags.make

Game/CMakeFiles/Game.dir/src/Game.cpp.o: Game/CMakeFiles/Game.dir/flags.make
Game/CMakeFiles/Game.dir/src/Game.cpp.o: ../Game/src/Game.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/amina/Desktop/Temple Run/Build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object Game/CMakeFiles/Game.dir/src/Game.cpp.o"
	cd "/home/amina/Desktop/Temple Run/Build/Game" && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Game.dir/src/Game.cpp.o -c "/home/amina/Desktop/Temple Run/Game/src/Game.cpp"

Game/CMakeFiles/Game.dir/src/Game.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Game.dir/src/Game.cpp.i"
	cd "/home/amina/Desktop/Temple Run/Build/Game" && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/amina/Desktop/Temple Run/Game/src/Game.cpp" > CMakeFiles/Game.dir/src/Game.cpp.i

Game/CMakeFiles/Game.dir/src/Game.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Game.dir/src/Game.cpp.s"
	cd "/home/amina/Desktop/Temple Run/Build/Game" && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/amina/Desktop/Temple Run/Game/src/Game.cpp" -o CMakeFiles/Game.dir/src/Game.cpp.s

Game/CMakeFiles/Game.dir/src/Game.cpp.o.requires:

.PHONY : Game/CMakeFiles/Game.dir/src/Game.cpp.o.requires

Game/CMakeFiles/Game.dir/src/Game.cpp.o.provides: Game/CMakeFiles/Game.dir/src/Game.cpp.o.requires
	$(MAKE) -f Game/CMakeFiles/Game.dir/build.make Game/CMakeFiles/Game.dir/src/Game.cpp.o.provides.build
.PHONY : Game/CMakeFiles/Game.dir/src/Game.cpp.o.provides

Game/CMakeFiles/Game.dir/src/Game.cpp.o.provides.build: Game/CMakeFiles/Game.dir/src/Game.cpp.o


# Object files for target Game
Game_OBJECTS = \
"CMakeFiles/Game.dir/src/Game.cpp.o"

# External object files for target Game
Game_EXTERNAL_OBJECTS =

Game/libGame.a: Game/CMakeFiles/Game.dir/src/Game.cpp.o
Game/libGame.a: Game/CMakeFiles/Game.dir/build.make
Game/libGame.a: Game/CMakeFiles/Game.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/home/amina/Desktop/Temple Run/Build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libGame.a"
	cd "/home/amina/Desktop/Temple Run/Build/Game" && $(CMAKE_COMMAND) -P CMakeFiles/Game.dir/cmake_clean_target.cmake
	cd "/home/amina/Desktop/Temple Run/Build/Game" && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Game.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
Game/CMakeFiles/Game.dir/build: Game/libGame.a

.PHONY : Game/CMakeFiles/Game.dir/build

Game/CMakeFiles/Game.dir/requires: Game/CMakeFiles/Game.dir/src/Game.cpp.o.requires

.PHONY : Game/CMakeFiles/Game.dir/requires

Game/CMakeFiles/Game.dir/clean:
	cd "/home/amina/Desktop/Temple Run/Build/Game" && $(CMAKE_COMMAND) -P CMakeFiles/Game.dir/cmake_clean.cmake
.PHONY : Game/CMakeFiles/Game.dir/clean

Game/CMakeFiles/Game.dir/depend:
	cd "/home/amina/Desktop/Temple Run/Build" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/amina/Desktop/Temple Run" "/home/amina/Desktop/Temple Run/Game" "/home/amina/Desktop/Temple Run/Build" "/home/amina/Desktop/Temple Run/Build/Game" "/home/amina/Desktop/Temple Run/Build/Game/CMakeFiles/Game.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : Game/CMakeFiles/Game.dir/depend
