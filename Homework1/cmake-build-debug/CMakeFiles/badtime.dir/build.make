# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.20

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2021.2.1\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2021.2.1\bin\cmake\win\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "D:\MS in CS\CSCI E-26\project1\Homework1"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "D:\MS in CS\CSCI E-26\project1\Homework1\cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/badtime.dir/depend.make
# Include the progress variables for this target.
include CMakeFiles/badtime.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/badtime.dir/flags.make

CMakeFiles/badtime.dir/badtime.c.obj: CMakeFiles/badtime.dir/flags.make
CMakeFiles/badtime.dir/badtime.c.obj: ../badtime.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="D:\MS in CS\CSCI E-26\project1\Homework1\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/badtime.dir/badtime.c.obj"
	C:\msys64\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\badtime.dir\badtime.c.obj -c "D:\MS in CS\CSCI E-26\project1\Homework1\badtime.c"

CMakeFiles/badtime.dir/badtime.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/badtime.dir/badtime.c.i"
	C:\msys64\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "D:\MS in CS\CSCI E-26\project1\Homework1\badtime.c" > CMakeFiles\badtime.dir\badtime.c.i

CMakeFiles/badtime.dir/badtime.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/badtime.dir/badtime.c.s"
	C:\msys64\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "D:\MS in CS\CSCI E-26\project1\Homework1\badtime.c" -o CMakeFiles\badtime.dir\badtime.c.s

# Object files for target badtime
badtime_OBJECTS = \
"CMakeFiles/badtime.dir/badtime.c.obj"

# External object files for target badtime
badtime_EXTERNAL_OBJECTS =

badtime.exe: CMakeFiles/badtime.dir/badtime.c.obj
badtime.exe: CMakeFiles/badtime.dir/build.make
badtime.exe: CMakeFiles/badtime.dir/linklibs.rsp
badtime.exe: CMakeFiles/badtime.dir/objects1.rsp
badtime.exe: CMakeFiles/badtime.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="D:\MS in CS\CSCI E-26\project1\Homework1\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable badtime.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\badtime.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/badtime.dir/build: badtime.exe
.PHONY : CMakeFiles/badtime.dir/build

CMakeFiles/badtime.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\badtime.dir\cmake_clean.cmake
.PHONY : CMakeFiles/badtime.dir/clean

CMakeFiles/badtime.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" "D:\MS in CS\CSCI E-26\project1\Homework1" "D:\MS in CS\CSCI E-26\project1\Homework1" "D:\MS in CS\CSCI E-26\project1\Homework1\cmake-build-debug" "D:\MS in CS\CSCI E-26\project1\Homework1\cmake-build-debug" "D:\MS in CS\CSCI E-26\project1\Homework1\cmake-build-debug\CMakeFiles\badtime.dir\DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/badtime.dir/depend
