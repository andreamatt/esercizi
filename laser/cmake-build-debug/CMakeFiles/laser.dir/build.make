# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.9

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = C:\Users\andrea\AppData\Local\JetBrains\Toolbox\apps\CLion\ch-0\173.3727.114\bin\cmake\bin\cmake.exe

# The command to remove a file.
RM = C:\Users\andrea\AppData\Local\JetBrains\Toolbox\apps\CLion\ch-0\173.3727.114\bin\cmake\bin\cmake.exe -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\andrea\Documents\GitHub\esercizi\laser

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\andrea\Documents\GitHub\esercizi\laser\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/laser.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/laser.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/laser.dir/flags.make

CMakeFiles/laser.dir/main.cpp.obj: CMakeFiles/laser.dir/flags.make
CMakeFiles/laser.dir/main.cpp.obj: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\andrea\Documents\GitHub\esercizi\laser\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/laser.dir/main.cpp.obj"
	C:\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\laser.dir\main.cpp.obj -c C:\Users\andrea\Documents\GitHub\esercizi\laser\main.cpp

CMakeFiles/laser.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/laser.dir/main.cpp.i"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\andrea\Documents\GitHub\esercizi\laser\main.cpp > CMakeFiles\laser.dir\main.cpp.i

CMakeFiles/laser.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/laser.dir/main.cpp.s"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\andrea\Documents\GitHub\esercizi\laser\main.cpp -o CMakeFiles\laser.dir\main.cpp.s

CMakeFiles/laser.dir/main.cpp.obj.requires:

.PHONY : CMakeFiles/laser.dir/main.cpp.obj.requires

CMakeFiles/laser.dir/main.cpp.obj.provides: CMakeFiles/laser.dir/main.cpp.obj.requires
	$(MAKE) -f CMakeFiles\laser.dir\build.make CMakeFiles/laser.dir/main.cpp.obj.provides.build
.PHONY : CMakeFiles/laser.dir/main.cpp.obj.provides

CMakeFiles/laser.dir/main.cpp.obj.provides.build: CMakeFiles/laser.dir/main.cpp.obj


# Object files for target laser
laser_OBJECTS = \
"CMakeFiles/laser.dir/main.cpp.obj"

# External object files for target laser
laser_EXTERNAL_OBJECTS =

laser.exe: CMakeFiles/laser.dir/main.cpp.obj
laser.exe: CMakeFiles/laser.dir/build.make
laser.exe: CMakeFiles/laser.dir/linklibs.rsp
laser.exe: CMakeFiles/laser.dir/objects1.rsp
laser.exe: CMakeFiles/laser.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\andrea\Documents\GitHub\esercizi\laser\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable laser.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\laser.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/laser.dir/build: laser.exe

.PHONY : CMakeFiles/laser.dir/build

CMakeFiles/laser.dir/requires: CMakeFiles/laser.dir/main.cpp.obj.requires

.PHONY : CMakeFiles/laser.dir/requires

CMakeFiles/laser.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\laser.dir\cmake_clean.cmake
.PHONY : CMakeFiles/laser.dir/clean

CMakeFiles/laser.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\andrea\Documents\GitHub\esercizi\laser C:\Users\andrea\Documents\GitHub\esercizi\laser C:\Users\andrea\Documents\GitHub\esercizi\laser\cmake-build-debug C:\Users\andrea\Documents\GitHub\esercizi\laser\cmake-build-debug C:\Users\andrea\Documents\GitHub\esercizi\laser\cmake-build-debug\CMakeFiles\laser.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/laser.dir/depend
