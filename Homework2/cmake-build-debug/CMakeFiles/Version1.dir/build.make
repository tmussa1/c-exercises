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
include CMakeFiles/Version1.dir/depend.make
# Include the progress variables for this target.
include CMakeFiles/Version1.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Version1.dir/flags.make

CMakeFiles/Version1.dir/tt2ht1.c.obj: CMakeFiles/Version1.dir/flags.make
CMakeFiles/Version1.dir/tt2ht1.c.obj: ../tt2ht1.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="D:\MS in CS\CSCI E-26\projects\Homework2\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/Version1.dir/tt2ht1.c.obj"
	C:\msys64\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\Version1.dir\tt2ht1.c.obj -c "D:\MS in CS\CSCI E-26\projects\Homework2\tt2ht1.c"

CMakeFiles/Version1.dir/tt2ht1.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Version1.dir/tt2ht1.c.i"
	C:\msys64\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "D:\MS in CS\CSCI E-26\projects\Homework2\tt2ht1.c" > CMakeFiles\Version1.dir\tt2ht1.c.i

CMakeFiles/Version1.dir/tt2ht1.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Version1.dir/tt2ht1.c.s"
	C:\msys64\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "D:\MS in CS\CSCI E-26\projects\Homework2\tt2ht1.c" -o CMakeFiles\Version1.dir\tt2ht1.c.s

# Object files for target Version1
Version1_OBJECTS = \
"CMakeFiles/Version1.dir/tt2ht1.c.obj"

# External object files for target Version1
Version1_EXTERNAL_OBJECTS =

Version1.exe: CMakeFiles/Version1.dir/tt2ht1.c.obj
Version1.exe: CMakeFiles/Version1.dir/build.make
Version1.exe: CMakeFiles/Version1.dir/linklibs.rsp
Version1.exe: CMakeFiles/Version1.dir/objects1.rsp
Version1.exe: CMakeFiles/Version1.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="D:\MS in CS\CSCI E-26\projects\Homework2\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable Version1.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\Version1.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Version1.dir/build: Version1.exe
.PHONY : CMakeFiles/Version1.dir/build

CMakeFiles/Version1.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\Version1.dir\cmake_clean.cmake
.PHONY : CMakeFiles/Version1.dir/clean

CMakeFiles/Version1.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" "D:\MS in CS\CSCI E-26\projects\Homework2" "D:\MS in CS\CSCI E-26\projects\Homework2" "D:\MS in CS\CSCI E-26\projects\Homework2\cmake-build-debug" "D:\MS in CS\CSCI E-26\projects\Homework2\cmake-build-debug" "D:\MS in CS\CSCI E-26\projects\Homework2\cmake-build-debug\CMakeFiles\Version1.dir\DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/Version1.dir/depend

