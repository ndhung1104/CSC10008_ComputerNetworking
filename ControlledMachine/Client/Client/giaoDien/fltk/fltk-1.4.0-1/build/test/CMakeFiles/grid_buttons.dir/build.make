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
include test/CMakeFiles/grid_buttons.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include test/CMakeFiles/grid_buttons.dir/compiler_depend.make

# Include the progress variables for this target.
include test/CMakeFiles/grid_buttons.dir/progress.make

# Include the compile flags for this target's objects.
include test/CMakeFiles/grid_buttons.dir/flags.make

test/CMakeFiles/grid_buttons.dir/codegen:
.PHONY : test/CMakeFiles/grid_buttons.dir/codegen

test/CMakeFiles/grid_buttons.dir/grid_buttons.cxx.obj: test/CMakeFiles/grid_buttons.dir/flags.make
test/CMakeFiles/grid_buttons.dir/grid_buttons.cxx.obj: test/CMakeFiles/grid_buttons.dir/includes_CXX.rsp
test/CMakeFiles/grid_buttons.dir/grid_buttons.cxx.obj: D:/Project/CSC10008_ComputerNetworking/ControlledMachine/Client/Client/giaoDien/fltk/fltk-1.4.0-1/test/grid_buttons.cxx
test/CMakeFiles/grid_buttons.dir/grid_buttons.cxx.obj: test/CMakeFiles/grid_buttons.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=D:\Project\CSC10008_ComputerNetworking\ControlledMachine\Client\Client\giaoDien\fltk\fltk-1.4.0-1\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object test/CMakeFiles/grid_buttons.dir/grid_buttons.cxx.obj"
	cd /d D:\Project\CSC10008_ComputerNetworking\ControlledMachine\Client\Client\giaoDien\fltk\fltk-1.4.0-1\build\test && C:\msys64\ucrt64\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT test/CMakeFiles/grid_buttons.dir/grid_buttons.cxx.obj -MF CMakeFiles\grid_buttons.dir\grid_buttons.cxx.obj.d -o CMakeFiles\grid_buttons.dir\grid_buttons.cxx.obj -c D:\Project\CSC10008_ComputerNetworking\ControlledMachine\Client\Client\giaoDien\fltk\fltk-1.4.0-1\test\grid_buttons.cxx

test/CMakeFiles/grid_buttons.dir/grid_buttons.cxx.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/grid_buttons.dir/grid_buttons.cxx.i"
	cd /d D:\Project\CSC10008_ComputerNetworking\ControlledMachine\Client\Client\giaoDien\fltk\fltk-1.4.0-1\build\test && C:\msys64\ucrt64\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\Project\CSC10008_ComputerNetworking\ControlledMachine\Client\Client\giaoDien\fltk\fltk-1.4.0-1\test\grid_buttons.cxx > CMakeFiles\grid_buttons.dir\grid_buttons.cxx.i

test/CMakeFiles/grid_buttons.dir/grid_buttons.cxx.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/grid_buttons.dir/grid_buttons.cxx.s"
	cd /d D:\Project\CSC10008_ComputerNetworking\ControlledMachine\Client\Client\giaoDien\fltk\fltk-1.4.0-1\build\test && C:\msys64\ucrt64\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\Project\CSC10008_ComputerNetworking\ControlledMachine\Client\Client\giaoDien\fltk\fltk-1.4.0-1\test\grid_buttons.cxx -o CMakeFiles\grid_buttons.dir\grid_buttons.cxx.s

# Object files for target grid_buttons
grid_buttons_OBJECTS = \
"CMakeFiles/grid_buttons.dir/grid_buttons.cxx.obj"

# External object files for target grid_buttons
grid_buttons_EXTERNAL_OBJECTS =

bin/test/grid_buttons.exe: test/CMakeFiles/grid_buttons.dir/grid_buttons.cxx.obj
bin/test/grid_buttons.exe: test/CMakeFiles/grid_buttons.dir/build.make
bin/test/grid_buttons.exe: lib/libfltk.a
bin/test/grid_buttons.exe: test/CMakeFiles/grid_buttons.dir/linkLibs.rsp
bin/test/grid_buttons.exe: test/CMakeFiles/grid_buttons.dir/objects1.rsp
bin/test/grid_buttons.exe: test/CMakeFiles/grid_buttons.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=D:\Project\CSC10008_ComputerNetworking\ControlledMachine\Client\Client\giaoDien\fltk\fltk-1.4.0-1\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ..\bin\test\grid_buttons.exe"
	cd /d D:\Project\CSC10008_ComputerNetworking\ControlledMachine\Client\Client\giaoDien\fltk\fltk-1.4.0-1\build\test && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\grid_buttons.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
test/CMakeFiles/grid_buttons.dir/build: bin/test/grid_buttons.exe
.PHONY : test/CMakeFiles/grid_buttons.dir/build

test/CMakeFiles/grid_buttons.dir/clean:
	cd /d D:\Project\CSC10008_ComputerNetworking\ControlledMachine\Client\Client\giaoDien\fltk\fltk-1.4.0-1\build\test && $(CMAKE_COMMAND) -P CMakeFiles\grid_buttons.dir\cmake_clean.cmake
.PHONY : test/CMakeFiles/grid_buttons.dir/clean

test/CMakeFiles/grid_buttons.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\Project\CSC10008_ComputerNetworking\ControlledMachine\Client\Client\giaoDien\fltk\fltk-1.4.0-1 D:\Project\CSC10008_ComputerNetworking\ControlledMachine\Client\Client\giaoDien\fltk\fltk-1.4.0-1\test D:\Project\CSC10008_ComputerNetworking\ControlledMachine\Client\Client\giaoDien\fltk\fltk-1.4.0-1\build D:\Project\CSC10008_ComputerNetworking\ControlledMachine\Client\Client\giaoDien\fltk\fltk-1.4.0-1\build\test D:\Project\CSC10008_ComputerNetworking\ControlledMachine\Client\Client\giaoDien\fltk\fltk-1.4.0-1\build\test\CMakeFiles\grid_buttons.dir\DependInfo.cmake "--color=$(COLOR)"
.PHONY : test/CMakeFiles/grid_buttons.dir/depend
