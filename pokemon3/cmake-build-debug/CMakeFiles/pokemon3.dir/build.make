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
CMAKE_COMMAND = C:\Users\andrea\AppData\Local\JetBrains\Toolbox\apps\CLion\ch-1\181.3263.17\bin\cmake\bin\cmake.exe

# The command to remove a file.
RM = C:\Users\andrea\AppData\Local\JetBrains\Toolbox\apps\CLion\ch-1\181.3263.17\bin\cmake\bin\cmake.exe -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\andrea\Documents\GitHub\esercizi\pokemon3

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\andrea\Documents\GitHub\esercizi\pokemon3\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/pokemon3.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/pokemon3.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/pokemon3.dir/flags.make

CMakeFiles/pokemon3.dir/main.cpp.obj: CMakeFiles/pokemon3.dir/flags.make
CMakeFiles/pokemon3.dir/main.cpp.obj: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\andrea\Documents\GitHub\esercizi\pokemon3\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/pokemon3.dir/main.cpp.obj"
	C:\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\pokemon3.dir\main.cpp.obj -c C:\Users\andrea\Documents\GitHub\esercizi\pokemon3\main.cpp

CMakeFiles/pokemon3.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/pokemon3.dir/main.cpp.i"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\andrea\Documents\GitHub\esercizi\pokemon3\main.cpp > CMakeFiles\pokemon3.dir\main.cpp.i

CMakeFiles/pokemon3.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/pokemon3.dir/main.cpp.s"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\andrea\Documents\GitHub\esercizi\pokemon3\main.cpp -o CMakeFiles\pokemon3.dir\main.cpp.s

CMakeFiles/pokemon3.dir/main.cpp.obj.requires:

.PHONY : CMakeFiles/pokemon3.dir/main.cpp.obj.requires

CMakeFiles/pokemon3.dir/main.cpp.obj.provides: CMakeFiles/pokemon3.dir/main.cpp.obj.requires
	$(MAKE) -f CMakeFiles\pokemon3.dir\build.make CMakeFiles/pokemon3.dir/main.cpp.obj.provides.build
.PHONY : CMakeFiles/pokemon3.dir/main.cpp.obj.provides

CMakeFiles/pokemon3.dir/main.cpp.obj.provides.build: CMakeFiles/pokemon3.dir/main.cpp.obj


# Object files for target pokemon3
pokemon3_OBJECTS = \
"CMakeFiles/pokemon3.dir/main.cpp.obj"

# External object files for target pokemon3
pokemon3_EXTERNAL_OBJECTS =

pokemon3.exe: CMakeFiles/pokemon3.dir/main.cpp.obj
pokemon3.exe: CMakeFiles/pokemon3.dir/build.make
pokemon3.exe: CMakeFiles/pokemon3.dir/linklibs.rsp
pokemon3.exe: CMakeFiles/pokemon3.dir/objects1.rsp
pokemon3.exe: CMakeFiles/pokemon3.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\andrea\Documents\GitHub\esercizi\pokemon3\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable pokemon3.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\pokemon3.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/pokemon3.dir/build: pokemon3.exe

.PHONY : CMakeFiles/pokemon3.dir/build

CMakeFiles/pokemon3.dir/requires: CMakeFiles/pokemon3.dir/main.cpp.obj.requires

.PHONY : CMakeFiles/pokemon3.dir/requires

CMakeFiles/pokemon3.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\pokemon3.dir\cmake_clean.cmake
.PHONY : CMakeFiles/pokemon3.dir/clean

CMakeFiles/pokemon3.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\andrea\Documents\GitHub\esercizi\pokemon3 C:\Users\andrea\Documents\GitHub\esercizi\pokemon3 C:\Users\andrea\Documents\GitHub\esercizi\pokemon3\cmake-build-debug C:\Users\andrea\Documents\GitHub\esercizi\pokemon3\cmake-build-debug C:\Users\andrea\Documents\GitHub\esercizi\pokemon3\cmake-build-debug\CMakeFiles\pokemon3.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/pokemon3.dir/depend

