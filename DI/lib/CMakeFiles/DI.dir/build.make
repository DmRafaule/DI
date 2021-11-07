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

#Suppress display of executed commands.
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
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/dimond/Projects/ForOpenGL/DI_GameEngine

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/dimond/Projects/ForOpenGL/DI_GameEngine/build

# Include any dependencies generated for this target.
include ../DI/lib/CMakeFiles/DI.dir/depend.make

# Include the progress variables for this target.
include ../DI/lib/CMakeFiles/DI.dir/progress.make

# Include the compile flags for this target's objects.
include ../DI/lib/CMakeFiles/DI.dir/flags.make

../DI/lib/CMakeFiles/DI.dir/src/core/App.cpp.o: ../DI/lib/CMakeFiles/DI.dir/flags.make
../DI/lib/CMakeFiles/DI.dir/src/core/App.cpp.o: ../DI/src/core/App.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dimond/Projects/ForOpenGL/DI_GameEngine/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object ../DI/lib/CMakeFiles/DI.dir/src/core/App.cpp.o"
	cd /home/dimond/Projects/ForOpenGL/DI_GameEngine/DI/lib && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/DI.dir/src/core/App.cpp.o -c /home/dimond/Projects/ForOpenGL/DI_GameEngine/DI/src/core/App.cpp

../DI/lib/CMakeFiles/DI.dir/src/core/App.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/DI.dir/src/core/App.cpp.i"
	cd /home/dimond/Projects/ForOpenGL/DI_GameEngine/DI/lib && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/dimond/Projects/ForOpenGL/DI_GameEngine/DI/src/core/App.cpp > CMakeFiles/DI.dir/src/core/App.cpp.i

../DI/lib/CMakeFiles/DI.dir/src/core/App.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/DI.dir/src/core/App.cpp.s"
	cd /home/dimond/Projects/ForOpenGL/DI_GameEngine/DI/lib && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/dimond/Projects/ForOpenGL/DI_GameEngine/DI/src/core/App.cpp -o CMakeFiles/DI.dir/src/core/App.cpp.s

../DI/lib/CMakeFiles/DI.dir/src/core/Core.cpp.o: ../DI/lib/CMakeFiles/DI.dir/flags.make
../DI/lib/CMakeFiles/DI.dir/src/core/Core.cpp.o: ../DI/src/core/Core.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dimond/Projects/ForOpenGL/DI_GameEngine/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object ../DI/lib/CMakeFiles/DI.dir/src/core/Core.cpp.o"
	cd /home/dimond/Projects/ForOpenGL/DI_GameEngine/DI/lib && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/DI.dir/src/core/Core.cpp.o -c /home/dimond/Projects/ForOpenGL/DI_GameEngine/DI/src/core/Core.cpp

../DI/lib/CMakeFiles/DI.dir/src/core/Core.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/DI.dir/src/core/Core.cpp.i"
	cd /home/dimond/Projects/ForOpenGL/DI_GameEngine/DI/lib && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/dimond/Projects/ForOpenGL/DI_GameEngine/DI/src/core/Core.cpp > CMakeFiles/DI.dir/src/core/Core.cpp.i

../DI/lib/CMakeFiles/DI.dir/src/core/Core.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/DI.dir/src/core/Core.cpp.s"
	cd /home/dimond/Projects/ForOpenGL/DI_GameEngine/DI/lib && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/dimond/Projects/ForOpenGL/DI_GameEngine/DI/src/core/Core.cpp -o CMakeFiles/DI.dir/src/core/Core.cpp.s

../DI/lib/CMakeFiles/DI.dir/src/core/Log.cpp.o: ../DI/lib/CMakeFiles/DI.dir/flags.make
../DI/lib/CMakeFiles/DI.dir/src/core/Log.cpp.o: ../DI/src/core/Log.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dimond/Projects/ForOpenGL/DI_GameEngine/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object ../DI/lib/CMakeFiles/DI.dir/src/core/Log.cpp.o"
	cd /home/dimond/Projects/ForOpenGL/DI_GameEngine/DI/lib && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/DI.dir/src/core/Log.cpp.o -c /home/dimond/Projects/ForOpenGL/DI_GameEngine/DI/src/core/Log.cpp

../DI/lib/CMakeFiles/DI.dir/src/core/Log.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/DI.dir/src/core/Log.cpp.i"
	cd /home/dimond/Projects/ForOpenGL/DI_GameEngine/DI/lib && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/dimond/Projects/ForOpenGL/DI_GameEngine/DI/src/core/Log.cpp > CMakeFiles/DI.dir/src/core/Log.cpp.i

../DI/lib/CMakeFiles/DI.dir/src/core/Log.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/DI.dir/src/core/Log.cpp.s"
	cd /home/dimond/Projects/ForOpenGL/DI_GameEngine/DI/lib && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/dimond/Projects/ForOpenGL/DI_GameEngine/DI/src/core/Log.cpp -o CMakeFiles/DI.dir/src/core/Log.cpp.s

# Object files for target DI
DI_OBJECTS = \
"CMakeFiles/DI.dir/src/core/App.cpp.o" \
"CMakeFiles/DI.dir/src/core/Core.cpp.o" \
"CMakeFiles/DI.dir/src/core/Log.cpp.o"

# External object files for target DI
DI_EXTERNAL_OBJECTS =

../DI/lib/libDI.so: ../DI/lib/CMakeFiles/DI.dir/src/core/App.cpp.o
../DI/lib/libDI.so: ../DI/lib/CMakeFiles/DI.dir/src/core/Core.cpp.o
../DI/lib/libDI.so: ../DI/lib/CMakeFiles/DI.dir/src/core/Log.cpp.o
../DI/lib/libDI.so: ../DI/lib/CMakeFiles/DI.dir/build.make
../DI/lib/libDI.so: ../DI/dep/SDL2/build/libSDL2-2.0.so
../DI/lib/libDI.so: ../DI/dep/SDL2/build/libSDL2-2.0.so.0
../DI/lib/libDI.so: ../DI/dep/SDL2/build/libSDL2-2.0.so.0.17.0
../DI/lib/libDI.so: ../DI/dep/GLEW/lib/libglew-shared.so
../DI/lib/libDI.so: ../DI/dep/GLEW/lib/libglew-shared.so.2.2.0
../DI/lib/libDI.so: ../DI/lib/CMakeFiles/DI.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/dimond/Projects/ForOpenGL/DI_GameEngine/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX shared library libDI.so"
	cd /home/dimond/Projects/ForOpenGL/DI_GameEngine/DI/lib && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/DI.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
../DI/lib/CMakeFiles/DI.dir/build: ../DI/lib/libDI.so

.PHONY : ../DI/lib/CMakeFiles/DI.dir/build

../DI/lib/CMakeFiles/DI.dir/clean:
	cd /home/dimond/Projects/ForOpenGL/DI_GameEngine/DI/lib && $(CMAKE_COMMAND) -P CMakeFiles/DI.dir/cmake_clean.cmake
.PHONY : ../DI/lib/CMakeFiles/DI.dir/clean

../DI/lib/CMakeFiles/DI.dir/depend:
	cd /home/dimond/Projects/ForOpenGL/DI_GameEngine/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/dimond/Projects/ForOpenGL/DI_GameEngine /home/dimond/Projects/ForOpenGL/DI_GameEngine/DI /home/dimond/Projects/ForOpenGL/DI_GameEngine/build /home/dimond/Projects/ForOpenGL/DI_GameEngine/DI/lib /home/dimond/Projects/ForOpenGL/DI_GameEngine/DI/lib/CMakeFiles/DI.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : ../DI/lib/CMakeFiles/DI.dir/depend

