# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.31

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
CMAKE_COMMAND = "C:\Program Files\CMake\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\CMake\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = D:\Project\CSC10008_ComputerNetworking\ControlledMachine\Client\Client\giaoDien\fltk\fltk-1.4.0-1

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:\Project\CSC10008_ComputerNetworking\ControlledMachine\Client\Client\giaoDien\fltk\fltk-1.4.0-1\build

# Include any dependencies generated for this target.
include test/CMakeFiles/input_choice.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include test/CMakeFiles/input_choice.dir/compiler_depend.make

# Include the progress variables for this target.
include test/CMakeFiles/input_choice.dir/progress.make

# Include the compile flags for this target's objects.
include test/CMakeFiles/input_choice.dir/flags.make

test/CMakeFiles/input_choice.dir/codegen:
.PHONY : test/CMakeFiles/input_choice.dir/codegen

test/CMakeFiles/input_choice.dir/input_choice.cxx.obj: test/CMakeFiles/input_choice.dir/flags.make
test/CMakeFiles/input_choice.dir/input_choice.cxx.obj: test/CMakeFiles/input_choice.dir/includes_CXX.rsp
test/CMakeFiles/input_choice.dir/input_choice.cxx.obj: D:/Project/CSC10008_ComputerNetworking/ControlledMachine/Client/Client/giaoDien/fltk/fltk-1.4.0-1/test/input_choice.cxx
test/CMakeFiles/input_choice.dir/input_choice.cxx.obj: test/CMakeFiles/input_choice.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=D:\Project\CSC10008_ComputerNetworking\ControlledMachine\Client\Client\giaoDien\fltk\fltk-1.4.0-1\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object test/CMakeFiles/input_choice.dir/input_choice.cxx.obj"
	cd /d D:\Project\CSC10008_ComputerNetworking\ControlledMachine\Client\Client\giaoDien\fltk\fltk-1.4.0-1\build\test && C:\msys64\ucrt64\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT test/CMakeFiles/input_choice.dir/input_choice.cxx.obj -MF CMakeFiles\input_choice.dir\input_choice.cxx.obj.d -o CMakeFiles\input_choice.dir\input_choice.cxx.obj -c D:\Project\CSC10008_ComputerNetworking\ControlledMachine\Client\Client\giaoDien\fltk\fltk-1.4.0-1\test\input_choice.cxx

test/CMakeFiles/input_choice.dir/input_choice.cxx.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/input_choice.dir/input_choice.cxx.i"
	cd /d D:\Project\CSC10008_ComputerNetworking\ControlledMachine\Client\Client\giaoDien\fltk\fltk-1.4.0-1\build\test && C:\msys64\ucrt64\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\Project\CSC10008_ComputerNetworking\ControlledMachine\Client\Client\giaoDien\fltk\fltk-1.4.0-1\test\input_choice.cxx > CMakeFiles\input_choice.dir\input_choice.cxx.i

test/CMakeFiles/input_choice.dir/input_choice.cxx.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/input_choice.dir/input_choice.cxx.s"
	cd /d D:\Project\CSC10008_ComputerNetworking\ControlledMachine\Client\Client\giaoDien\fltk\fltk-1.4.0-1\build\test && C:\msys64\ucrt64\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\Project\CSC10008_ComputerNetworking\ControlledMachine\Client\Client\giaoDien\fltk\fltk-1.4.0-1\test\input_choice.cxx -o CMakeFiles\input_choice.dir\input_choice.cxx.s

# Object files for target input_choice
input_choice_OBJECTS = \
"CMakeFiles/input_choice.dir/input_choice.cxx.obj"

# External object files for target input_choice
input_choice_EXTERNAL_OBJECTS =

bin/test/input_choice.exe: test/CMakeFiles/input_choice.dir/input_choice.cxx.obj
bin/test/input_choice.exe: test/CMakeFiles/input_choice.dir/build.make
bin/test/input_choice.exe: lib/libfltk.a
bin/test/input_choice.exe: test/CMakeFiles/input_choice.dir/linkLibs.rsp
bin/test/input_choice.exe: test/CMakeFiles/input_choice.dir/objects1.rsp
bin/test/input_choice.exe: test/CMakeFiles/input_choice.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=D:\Project\CSC10008_ComputerNetworking\ControlledMachine\Client\Client\giaoDien\fltk\fltk-1.4.0-1\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ..\bin\test\input_choice.exe"
	cd /d D:\Project\CSC10008_ComputerNetworking\ControlledMachine\Client\Client\giaoDien\fltk\fltk-1.4.0-1\build\test && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\input_choice.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
test/CMakeFiles/input_choice.dir/build: bin/test/input_choice.exe
.PHONY : test/CMakeFiles/input_choice.dir/build

test/CMakeFiles/input_choice.dir/clean:
	cd /d D:\Project\CSC10008_ComputerNetworking\ControlledMachine\Client\Client\giaoDien\fltk\fltk-1.4.0-1\build\test && $(CMAKE_COMMAND) -P CMakeFiles\input_choice.dir\cmake_clean.cmake
.PHONY : test/CMakeFiles/input_choice.dir/clean

test/CMakeFiles/input_choice.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\Project\CSC10008_ComputerNetworking\ControlledMachine\Client\Client\giaoDien\fltk\fltk-1.4.0-1 D:\Project\CSC10008_ComputerNetworking\ControlledMachine\Client\Client\giaoDien\fltk\fltk-1.4.0-1\test D:\Project\CSC10008_ComputerNetworking\ControlledMachine\Client\Client\giaoDien\fltk\fltk-1.4.0-1\build D:\Project\CSC10008_ComputerNetworking\ControlledMachine\Client\Client\giaoDien\fltk\fltk-1.4.0-1\build\test D:\Project\CSC10008_ComputerNetworking\ControlledMachine\Client\Client\giaoDien\fltk\fltk-1.4.0-1\build\test\CMakeFiles\input_choice.dir\DependInfo.cmake "--color=$(COLOR)"
.PHONY : test/CMakeFiles/input_choice.dir/depend

