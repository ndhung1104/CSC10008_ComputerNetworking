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
include test/CMakeFiles/terminal.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include test/CMakeFiles/terminal.dir/compiler_depend.make

# Include the progress variables for this target.
include test/CMakeFiles/terminal.dir/progress.make

# Include the compile flags for this target's objects.
include test/CMakeFiles/terminal.dir/flags.make

test/terminal.cxx: D:/Project/CSC10008_ComputerNetworking/ControlledMachine/Client/Client/giaoDien/fltk/fltk-1.4.0-1/test/terminal.fl
test/terminal.cxx: D:/Project/CSC10008_ComputerNetworking/ControlledMachine/Client/Client/giaoDien/fltk/fltk-1.4.0-1/test/terminal.fl
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --blue --bold --progress-dir=D:\Project\CSC10008_ComputerNetworking\ControlledMachine\Client\Client\giaoDien\fltk\fltk-1.4.0-1\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Generating terminal.cxx, terminal.h"
	cd /d D:\Project\CSC10008_ComputerNetworking\ControlledMachine\Client\Client\giaoDien\fltk\fltk-1.4.0-1\build\test && ..\bin\fluid-cmd.exe -c D:/Project/CSC10008_ComputerNetworking/ControlledMachine/Client/Client/giaoDien/fltk/fltk-1.4.0-1/test/terminal.fl

test/terminal.h: test/terminal.cxx
	@$(CMAKE_COMMAND) -E touch_nocreate test\terminal.h

test/CMakeFiles/terminal.dir/codegen:
.PHONY : test/CMakeFiles/terminal.dir/codegen

test/CMakeFiles/terminal.dir/terminal.cxx.obj: test/CMakeFiles/terminal.dir/flags.make
test/CMakeFiles/terminal.dir/terminal.cxx.obj: test/CMakeFiles/terminal.dir/includes_CXX.rsp
test/CMakeFiles/terminal.dir/terminal.cxx.obj: test/terminal.cxx
test/CMakeFiles/terminal.dir/terminal.cxx.obj: test/CMakeFiles/terminal.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=D:\Project\CSC10008_ComputerNetworking\ControlledMachine\Client\Client\giaoDien\fltk\fltk-1.4.0-1\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object test/CMakeFiles/terminal.dir/terminal.cxx.obj"
	cd /d D:\Project\CSC10008_ComputerNetworking\ControlledMachine\Client\Client\giaoDien\fltk\fltk-1.4.0-1\build\test && C:\msys64\ucrt64\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT test/CMakeFiles/terminal.dir/terminal.cxx.obj -MF CMakeFiles\terminal.dir\terminal.cxx.obj.d -o CMakeFiles\terminal.dir\terminal.cxx.obj -c D:\Project\CSC10008_ComputerNetworking\ControlledMachine\Client\Client\giaoDien\fltk\fltk-1.4.0-1\build\test\terminal.cxx

test/CMakeFiles/terminal.dir/terminal.cxx.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/terminal.dir/terminal.cxx.i"
	cd /d D:\Project\CSC10008_ComputerNetworking\ControlledMachine\Client\Client\giaoDien\fltk\fltk-1.4.0-1\build\test && C:\msys64\ucrt64\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\Project\CSC10008_ComputerNetworking\ControlledMachine\Client\Client\giaoDien\fltk\fltk-1.4.0-1\build\test\terminal.cxx > CMakeFiles\terminal.dir\terminal.cxx.i

test/CMakeFiles/terminal.dir/terminal.cxx.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/terminal.dir/terminal.cxx.s"
	cd /d D:\Project\CSC10008_ComputerNetworking\ControlledMachine\Client\Client\giaoDien\fltk\fltk-1.4.0-1\build\test && C:\msys64\ucrt64\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\Project\CSC10008_ComputerNetworking\ControlledMachine\Client\Client\giaoDien\fltk\fltk-1.4.0-1\build\test\terminal.cxx -o CMakeFiles\terminal.dir\terminal.cxx.s

# Object files for target terminal
terminal_OBJECTS = \
"CMakeFiles/terminal.dir/terminal.cxx.obj"

# External object files for target terminal
terminal_EXTERNAL_OBJECTS =

bin/test/terminal.exe: test/CMakeFiles/terminal.dir/terminal.cxx.obj
bin/test/terminal.exe: test/CMakeFiles/terminal.dir/build.make
bin/test/terminal.exe: lib/libfltk.a
bin/test/terminal.exe: test/CMakeFiles/terminal.dir/linkLibs.rsp
bin/test/terminal.exe: test/CMakeFiles/terminal.dir/objects1.rsp
bin/test/terminal.exe: test/CMakeFiles/terminal.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=D:\Project\CSC10008_ComputerNetworking\ControlledMachine\Client\Client\giaoDien\fltk\fltk-1.4.0-1\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable ..\bin\test\terminal.exe"
	cd /d D:\Project\CSC10008_ComputerNetworking\ControlledMachine\Client\Client\giaoDien\fltk\fltk-1.4.0-1\build\test && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\terminal.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
test/CMakeFiles/terminal.dir/build: bin/test/terminal.exe
.PHONY : test/CMakeFiles/terminal.dir/build

test/CMakeFiles/terminal.dir/clean:
	cd /d D:\Project\CSC10008_ComputerNetworking\ControlledMachine\Client\Client\giaoDien\fltk\fltk-1.4.0-1\build\test && $(CMAKE_COMMAND) -P CMakeFiles\terminal.dir\cmake_clean.cmake
.PHONY : test/CMakeFiles/terminal.dir/clean

test/CMakeFiles/terminal.dir/depend: test/terminal.cxx
test/CMakeFiles/terminal.dir/depend: test/terminal.h
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\Project\CSC10008_ComputerNetworking\ControlledMachine\Client\Client\giaoDien\fltk\fltk-1.4.0-1 D:\Project\CSC10008_ComputerNetworking\ControlledMachine\Client\Client\giaoDien\fltk\fltk-1.4.0-1\test D:\Project\CSC10008_ComputerNetworking\ControlledMachine\Client\Client\giaoDien\fltk\fltk-1.4.0-1\build D:\Project\CSC10008_ComputerNetworking\ControlledMachine\Client\Client\giaoDien\fltk\fltk-1.4.0-1\build\test D:\Project\CSC10008_ComputerNetworking\ControlledMachine\Client\Client\giaoDien\fltk\fltk-1.4.0-1\build\test\CMakeFiles\terminal.dir\DependInfo.cmake "--color=$(COLOR)"
.PHONY : test/CMakeFiles/terminal.dir/depend

