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
include test/CMakeFiles/keyboard.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include test/CMakeFiles/keyboard.dir/compiler_depend.make

# Include the progress variables for this target.
include test/CMakeFiles/keyboard.dir/progress.make

# Include the compile flags for this target's objects.
include test/CMakeFiles/keyboard.dir/flags.make

test/keyboard_ui.cxx: D:/Project/CSC10008_ComputerNetworking/ControlledMachine/Client/Client/giaoDien/fltk/fltk-1.4.0-1/test/keyboard_ui.fl
test/keyboard_ui.cxx: D:/Project/CSC10008_ComputerNetworking/ControlledMachine/Client/Client/giaoDien/fltk/fltk-1.4.0-1/test/keyboard_ui.fl
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --blue --bold --progress-dir=D:\Project\CSC10008_ComputerNetworking\ControlledMachine\Client\Client\giaoDien\fltk\fltk-1.4.0-1\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Generating keyboard_ui.cxx, keyboard_ui.h"
	cd /d D:\Project\CSC10008_ComputerNetworking\ControlledMachine\Client\Client\giaoDien\fltk\fltk-1.4.0-1\build\test && ..\bin\fluid-cmd.exe -c D:/Project/CSC10008_ComputerNetworking/ControlledMachine/Client/Client/giaoDien/fltk/fltk-1.4.0-1/test/keyboard_ui.fl

test/keyboard_ui.h: test/keyboard_ui.cxx
	@$(CMAKE_COMMAND) -E touch_nocreate test\keyboard_ui.h

test/CMakeFiles/keyboard.dir/codegen:
.PHONY : test/CMakeFiles/keyboard.dir/codegen

test/CMakeFiles/keyboard.dir/keyboard.cxx.obj: test/CMakeFiles/keyboard.dir/flags.make
test/CMakeFiles/keyboard.dir/keyboard.cxx.obj: test/CMakeFiles/keyboard.dir/includes_CXX.rsp
test/CMakeFiles/keyboard.dir/keyboard.cxx.obj: D:/Project/CSC10008_ComputerNetworking/ControlledMachine/Client/Client/giaoDien/fltk/fltk-1.4.0-1/test/keyboard.cxx
test/CMakeFiles/keyboard.dir/keyboard.cxx.obj: test/CMakeFiles/keyboard.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=D:\Project\CSC10008_ComputerNetworking\ControlledMachine\Client\Client\giaoDien\fltk\fltk-1.4.0-1\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object test/CMakeFiles/keyboard.dir/keyboard.cxx.obj"
	cd /d D:\Project\CSC10008_ComputerNetworking\ControlledMachine\Client\Client\giaoDien\fltk\fltk-1.4.0-1\build\test && C:\msys64\ucrt64\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT test/CMakeFiles/keyboard.dir/keyboard.cxx.obj -MF CMakeFiles\keyboard.dir\keyboard.cxx.obj.d -o CMakeFiles\keyboard.dir\keyboard.cxx.obj -c D:\Project\CSC10008_ComputerNetworking\ControlledMachine\Client\Client\giaoDien\fltk\fltk-1.4.0-1\test\keyboard.cxx

test/CMakeFiles/keyboard.dir/keyboard.cxx.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/keyboard.dir/keyboard.cxx.i"
	cd /d D:\Project\CSC10008_ComputerNetworking\ControlledMachine\Client\Client\giaoDien\fltk\fltk-1.4.0-1\build\test && C:\msys64\ucrt64\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\Project\CSC10008_ComputerNetworking\ControlledMachine\Client\Client\giaoDien\fltk\fltk-1.4.0-1\test\keyboard.cxx > CMakeFiles\keyboard.dir\keyboard.cxx.i

test/CMakeFiles/keyboard.dir/keyboard.cxx.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/keyboard.dir/keyboard.cxx.s"
	cd /d D:\Project\CSC10008_ComputerNetworking\ControlledMachine\Client\Client\giaoDien\fltk\fltk-1.4.0-1\build\test && C:\msys64\ucrt64\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\Project\CSC10008_ComputerNetworking\ControlledMachine\Client\Client\giaoDien\fltk\fltk-1.4.0-1\test\keyboard.cxx -o CMakeFiles\keyboard.dir\keyboard.cxx.s

test/CMakeFiles/keyboard.dir/keyboard_ui.cxx.obj: test/CMakeFiles/keyboard.dir/flags.make
test/CMakeFiles/keyboard.dir/keyboard_ui.cxx.obj: test/CMakeFiles/keyboard.dir/includes_CXX.rsp
test/CMakeFiles/keyboard.dir/keyboard_ui.cxx.obj: test/keyboard_ui.cxx
test/CMakeFiles/keyboard.dir/keyboard_ui.cxx.obj: test/CMakeFiles/keyboard.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=D:\Project\CSC10008_ComputerNetworking\ControlledMachine\Client\Client\giaoDien\fltk\fltk-1.4.0-1\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object test/CMakeFiles/keyboard.dir/keyboard_ui.cxx.obj"
	cd /d D:\Project\CSC10008_ComputerNetworking\ControlledMachine\Client\Client\giaoDien\fltk\fltk-1.4.0-1\build\test && C:\msys64\ucrt64\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT test/CMakeFiles/keyboard.dir/keyboard_ui.cxx.obj -MF CMakeFiles\keyboard.dir\keyboard_ui.cxx.obj.d -o CMakeFiles\keyboard.dir\keyboard_ui.cxx.obj -c D:\Project\CSC10008_ComputerNetworking\ControlledMachine\Client\Client\giaoDien\fltk\fltk-1.4.0-1\build\test\keyboard_ui.cxx

test/CMakeFiles/keyboard.dir/keyboard_ui.cxx.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/keyboard.dir/keyboard_ui.cxx.i"
	cd /d D:\Project\CSC10008_ComputerNetworking\ControlledMachine\Client\Client\giaoDien\fltk\fltk-1.4.0-1\build\test && C:\msys64\ucrt64\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\Project\CSC10008_ComputerNetworking\ControlledMachine\Client\Client\giaoDien\fltk\fltk-1.4.0-1\build\test\keyboard_ui.cxx > CMakeFiles\keyboard.dir\keyboard_ui.cxx.i

test/CMakeFiles/keyboard.dir/keyboard_ui.cxx.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/keyboard.dir/keyboard_ui.cxx.s"
	cd /d D:\Project\CSC10008_ComputerNetworking\ControlledMachine\Client\Client\giaoDien\fltk\fltk-1.4.0-1\build\test && C:\msys64\ucrt64\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\Project\CSC10008_ComputerNetworking\ControlledMachine\Client\Client\giaoDien\fltk\fltk-1.4.0-1\build\test\keyboard_ui.cxx -o CMakeFiles\keyboard.dir\keyboard_ui.cxx.s

# Object files for target keyboard
keyboard_OBJECTS = \
"CMakeFiles/keyboard.dir/keyboard.cxx.obj" \
"CMakeFiles/keyboard.dir/keyboard_ui.cxx.obj"

# External object files for target keyboard
keyboard_EXTERNAL_OBJECTS =

bin/test/keyboard.exe: test/CMakeFiles/keyboard.dir/keyboard.cxx.obj
bin/test/keyboard.exe: test/CMakeFiles/keyboard.dir/keyboard_ui.cxx.obj
bin/test/keyboard.exe: test/CMakeFiles/keyboard.dir/build.make
bin/test/keyboard.exe: lib/libfltk.a
bin/test/keyboard.exe: test/CMakeFiles/keyboard.dir/linkLibs.rsp
bin/test/keyboard.exe: test/CMakeFiles/keyboard.dir/objects1.rsp
bin/test/keyboard.exe: test/CMakeFiles/keyboard.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=D:\Project\CSC10008_ComputerNetworking\ControlledMachine\Client\Client\giaoDien\fltk\fltk-1.4.0-1\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable ..\bin\test\keyboard.exe"
	cd /d D:\Project\CSC10008_ComputerNetworking\ControlledMachine\Client\Client\giaoDien\fltk\fltk-1.4.0-1\build\test && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\keyboard.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
test/CMakeFiles/keyboard.dir/build: bin/test/keyboard.exe
.PHONY : test/CMakeFiles/keyboard.dir/build

test/CMakeFiles/keyboard.dir/clean:
	cd /d D:\Project\CSC10008_ComputerNetworking\ControlledMachine\Client\Client\giaoDien\fltk\fltk-1.4.0-1\build\test && $(CMAKE_COMMAND) -P CMakeFiles\keyboard.dir\cmake_clean.cmake
.PHONY : test/CMakeFiles/keyboard.dir/clean

test/CMakeFiles/keyboard.dir/depend: test/keyboard_ui.cxx
test/CMakeFiles/keyboard.dir/depend: test/keyboard_ui.h
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\Project\CSC10008_ComputerNetworking\ControlledMachine\Client\Client\giaoDien\fltk\fltk-1.4.0-1 D:\Project\CSC10008_ComputerNetworking\ControlledMachine\Client\Client\giaoDien\fltk\fltk-1.4.0-1\test D:\Project\CSC10008_ComputerNetworking\ControlledMachine\Client\Client\giaoDien\fltk\fltk-1.4.0-1\build D:\Project\CSC10008_ComputerNetworking\ControlledMachine\Client\Client\giaoDien\fltk\fltk-1.4.0-1\build\test D:\Project\CSC10008_ComputerNetworking\ControlledMachine\Client\Client\giaoDien\fltk\fltk-1.4.0-1\build\test\CMakeFiles\keyboard.dir\DependInfo.cmake "--color=$(COLOR)"
.PHONY : test/CMakeFiles/keyboard.dir/depend
