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
CMAKE_SOURCE_DIR = "D:\MS in CS\CSCI E-26\projects\Homework2"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "D:\MS in CS\CSCI E-26\projects\Homework2\cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/Homework2.dir/depend.make
# Include the progress variables for this target.
include CMakeFiles/Homework2.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Homework2.dir/flags.make

CMakeFiles/Homework2.dir/main.c.obj: CMakeFiles/Homework2.dir/flags.make
CMakeFiles/Homework2.dir/main.c.obj: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="D:\MS in CS\CSCI E-26\projects\Homework2\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/Homework2.dir/main.c.obj"
	C:\msys64\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\Homework2.dir\main.c.obj -c "D:\MS in CS\CSCI E-26\projects\Homework2\main.c"

CMakeFiles/Homework2.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Homework2.dir/main.c.i"
	C:\msys64\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "D:\MS in CS\CSCI E-26\projects\Homework2\main.c" > CMakeFiles\Homework2.dir\main.c.i

CMakeFiles/Homework2.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Homework2.dir/main.c.s"
	C:\msys64\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "D:\MS in CS\CSCI E-26\projects\Homework2\main.c" -o CMakeFiles\Homework2.dir\main.c.s

# Object files for target Homework2
Homework2_OBJECTS = \
"CMakeFiles/Homework2.dir/main.c.obj"

# External object files for target Homework2
Homework2_EXTERNAL_OBJECTS =

Homework2.exe: CMakeFiles/Homework2.dir/main.c.obj
Homework2.exe: CMakeFiles/Homework2.dir/build.make
Homework2.exe: CMakeFiles/Homework2.dir/linklibs.rsp
Homework2.exe: CMakeFiles/Homework2.dir/objects1.rsp
Homework2.exe: CMakeFiles/Homework2.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="D:\MS in CS\CSCI E-26\projects\Homework2\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable Homework2.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\Homework2.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Homework2.dir/build: Homework2.exe
.PHONY : CMakeFiles/Homework2.dir/build

CMakeFiles/Homework2.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\Homework2.dir\cmake_clean.cmake
.PHONY : CMakeFiles/Homework2.dir/clean

CMakeFiles/Homework2.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" "D:\MS in CS\CSCI E-26\projects\Homework2" "D:\MS in CS\CSCI E-26\projects\Homework2" "D:\MS in CS\CSCI E-26\projects\Homework2\cmake-build-debug" "D:\MS in CS\CSCI E-26\projects\Homework2\cmake-build-debug" "D:\MS in CS\CSCI E-26\projects\Homework2\cmake-build-debug\CMakeFiles\Homework2.dir\DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/Homework2.dir/depend

