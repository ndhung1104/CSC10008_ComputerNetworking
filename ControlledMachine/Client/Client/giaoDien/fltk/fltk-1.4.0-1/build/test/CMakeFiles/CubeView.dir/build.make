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
include test/CMakeFiles/CubeView.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include test/CMakeFiles/CubeView.dir/compiler_depend.make

# Include the progress variables for this target.
include test/CMakeFiles/CubeView.dir/progress.make

# Include the compile flags for this target's objects.
include test/CMakeFiles/CubeView.dir/flags.make

test/CubeViewUI.cxx: D:/Project/CSC10008_ComputerNetworking/ControlledMachine/Client/Client/giaoDien/fltk/fltk-1.4.0-1/test/CubeViewUI.fl
test/CubeViewUI.cxx: D:/Project/CSC10008_ComputerNetworking/ControlledMachine/Client/Client/giaoDien/fltk/fltk-1.4.0-1/test/CubeViewUI.fl
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --blue --bold --progress-dir=D:\Project\CSC10008_ComputerNetworking\ControlledMachine\Client\Client\giaoDien\fltk\fltk-1.4.0-1\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Generating CubeViewUI.cxx, CubeViewUI.h"
	cd /d D:\Project\CSC10008_ComputerNetworking\ControlledMachine\Client\Client\giaoDien\fltk\fltk-1.4.0-1\build\test && ..\bin\fluid-cmd.exe -c D:/Project/CSC10008_ComputerNetworking/ControlledMachine/Client/Client/giaoDien/fltk/fltk-1.4.0-1/test/CubeViewUI.fl

test/CubeViewUI.h: test/CubeViewUI.cxx
	@$(CMAKE_COMMAND) -E touch_nocreate test\CubeViewUI.h

test/CMakeFiles/CubeView.dir/codegen:
.PHONY : test/CMakeFiles/CubeView.dir/codegen

test/CMakeFiles/CubeView.dir/CubeMain.cxx.obj: test/CMakeFiles/CubeView.dir/flags.make
test/CMakeFiles/CubeView.dir/CubeMain.cxx.obj: test/CMakeFiles/CubeView.dir/includes_CXX.rsp
test/CMakeFiles/CubeView.dir/CubeMain.cxx.obj: D:/Project/CSC10008_ComputerNetworking/ControlledMachine/Client/Client/giaoDien/fltk/fltk-1.4.0-1/test/CubeMain.cxx
test/CMakeFiles/CubeView.dir/CubeMain.cxx.obj: test/CMakeFiles/CubeView.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=D:\Project\CSC10008_ComputerNetworking\ControlledMachine\Client\Client\giaoDien\fltk\fltk-1.4.0-1\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object test/CMakeFiles/CubeView.dir/CubeMain.cxx.obj"
	cd /d D:\Project\CSC10008_ComputerNetworking\ControlledMachine\Client\Client\giaoDien\fltk\fltk-1.4.0-1\build\test && C:\msys64\ucrt64\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT test/CMakeFiles/CubeView.dir/CubeMain.cxx.obj -MF CMakeFiles\CubeView.dir\CubeMain.cxx.obj.d -o CMakeFiles\CubeView.dir\CubeMain.cxx.obj -c D:\Project\CSC10008_ComputerNetworking\ControlledMachine\Client\Client\giaoDien\fltk\fltk-1.4.0-1\test\CubeMain.cxx

test/CMakeFiles/CubeView.dir/CubeMain.cxx.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/CubeView.dir/CubeMain.cxx.i"
	cd /d D:\Project\CSC10008_ComputerNetworking\ControlledMachine\Client\Client\giaoDien\fltk\fltk-1.4.0-1\build\test && C:\msys64\ucrt64\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\Project\CSC10008_ComputerNetworking\ControlledMachine\Client\Client\giaoDien\fltk\fltk-1.4.0-1\test\CubeMain.cxx > CMakeFiles\CubeView.dir\CubeMain.cxx.i

test/CMakeFiles/CubeView.dir/CubeMain.cxx.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/CubeView.dir/CubeMain.cxx.s"
	cd /d D:\Project\CSC10008_ComputerNetworking\ControlledMachine\Client\Client\giaoDien\fltk\fltk-1.4.0-1\build\test && C:\msys64\ucrt64\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\Project\CSC10008_ComputerNetworking\ControlledMachine\Client\Client\giaoDien\fltk\fltk-1.4.0-1\test\CubeMain.cxx -o CMakeFiles\CubeView.dir\CubeMain.cxx.s

test/CMakeFiles/CubeView.dir/CubeView.cxx.obj: test/CMakeFiles/CubeView.dir/flags.make
test/CMakeFiles/CubeView.dir/CubeView.cxx.obj: test/CMakeFiles/CubeView.dir/includes_CXX.rsp
test/CMakeFiles/CubeView.dir/CubeView.cxx.obj: D:/Project/CSC10008_ComputerNetworking/ControlledMachine/Client/Client/giaoDien/fltk/fltk-1.4.0-1/test/CubeView.cxx
test/CMakeFiles/CubeView.dir/CubeView.cxx.obj: test/CMakeFiles/CubeView.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=D:\Project\CSC10008_ComputerNetworking\ControlledMachine\Client\Client\giaoDien\fltk\fltk-1.4.0-1\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object test/CMakeFiles/CubeView.dir/CubeView.cxx.obj"
	cd /d D:\Project\CSC10008_ComputerNetworking\ControlledMachine\Client\Client\giaoDien\fltk\fltk-1.4.0-1\build\test && C:\msys64\ucrt64\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT test/CMakeFiles/CubeView.dir/CubeView.cxx.obj -MF CMakeFiles\CubeView.dir\CubeView.cxx.obj.d -o CMakeFiles\CubeView.dir\CubeView.cxx.obj -c D:\Project\CSC10008_ComputerNetworking\ControlledMachine\Client\Client\giaoDien\fltk\fltk-1.4.0-1\test\CubeView.cxx

test/CMakeFiles/CubeView.dir/CubeView.cxx.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/CubeView.dir/CubeView.cxx.i"
	cd /d D:\Project\CSC10008_ComputerNetworking\ControlledMachine\Client\Client\giaoDien\fltk\fltk-1.4.0-1\build\test && C:\msys64\ucrt64\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\Project\CSC10008_ComputerNetworking\ControlledMachine\Client\Client\giaoDien\fltk\fltk-1.4.0-1\test\CubeView.cxx > CMakeFiles\CubeView.dir\CubeView.cxx.i

test/CMakeFiles/CubeView.dir/CubeView.cxx.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/CubeView.dir/CubeView.cxx.s"
	cd /d D:\Project\CSC10008_ComputerNetworking\ControlledMachine\Client\Client\giaoDien\fltk\fltk-1.4.0-1\build\test && C:\msys64\ucrt64\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\Project\CSC10008_ComputerNetworking\ControlledMachine\Client\Client\giaoDien\fltk\fltk-1.4.0-1\test\CubeView.cxx -o CMakeFiles\CubeView.dir\CubeView.cxx.s

test/CMakeFiles/CubeView.dir/CubeViewUI.cxx.obj: test/CMakeFiles/CubeView.dir/flags.make
test/CMakeFiles/CubeView.dir/CubeViewUI.cxx.obj: test/CMakeFiles/CubeView.dir/includes_CXX.rsp
test/CMakeFiles/CubeView.dir/CubeViewUI.cxx.obj: test/CubeViewUI.cxx
test/CMakeFiles/CubeView.dir/CubeViewUI.cxx.obj: test/CMakeFiles/CubeView.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=D:\Project\CSC10008_ComputerNetworking\ControlledMachine\Client\Client\giaoDien\fltk\fltk-1.4.0-1\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object test/CMakeFiles/CubeView.dir/CubeViewUI.cxx.obj"
	cd /d D:\Project\CSC10008_ComputerNetworking\ControlledMachine\Client\Client\giaoDien\fltk\fltk-1.4.0-1\build\test && C:\msys64\ucrt64\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT test/CMakeFiles/CubeView.dir/CubeViewUI.cxx.obj -MF CMakeFiles\CubeView.dir\CubeViewUI.cxx.obj.d -o CMakeFiles\CubeView.dir\CubeViewUI.cxx.obj -c D:\Project\CSC10008_ComputerNetworking\ControlledMachine\Client\Client\giaoDien\fltk\fltk-1.4.0-1\build\test\CubeViewUI.cxx

test/CMakeFiles/CubeView.dir/CubeViewUI.cxx.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/CubeView.dir/CubeViewUI.cxx.i"
	cd /d D:\Project\CSC10008_ComputerNetworking\ControlledMachine\Client\Client\giaoDien\fltk\fltk-1.4.0-1\build\test && C:\msys64\ucrt64\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\Project\CSC10008_ComputerNetworking\ControlledMachine\Client\Client\giaoDien\fltk\fltk-1.4.0-1\build\test\CubeViewUI.cxx > CMakeFiles\CubeView.dir\CubeViewUI.cxx.i

test/CMakeFiles/CubeView.dir/CubeViewUI.cxx.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/CubeView.dir/CubeViewUI.cxx.s"
	cd /d D:\Project\CSC10008_ComputerNetworking\ControlledMachine\Client\Client\giaoDien\fltk\fltk-1.4.0-1\build\test && C:\msys64\ucrt64\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\Project\CSC10008_ComputerNetworking\ControlledMachine\Client\Client\giaoDien\fltk\fltk-1.4.0-1\build\test\CubeViewUI.cxx -o CMakeFiles\CubeView.dir\CubeViewUI.cxx.s

# Object files for target CubeView
CubeView_OBJECTS = \
"CMakeFiles/CubeView.dir/CubeMain.cxx.obj" \
"CMakeFiles/CubeView.dir/CubeView.cxx.obj" \
"CMakeFiles/CubeView.dir/CubeViewUI.cxx.obj"

# External object files for target CubeView
CubeView_EXTERNAL_OBJECTS =

bin/test/CubeView.exe: test/CMakeFiles/CubeView.dir/CubeMain.cxx.obj
bin/test/CubeView.exe: test/CMakeFiles/CubeView.dir/CubeView.cxx.obj
bin/test/CubeView.exe: test/CMakeFiles/CubeView.dir/CubeViewUI.cxx.obj
bin/test/CubeView.exe: test/CMakeFiles/CubeView.dir/build.make
bin/test/CubeView.exe: lib/libfltk_gl.a
bin/test/CubeView.exe: lib/libfltk.a
bin/test/CubeView.exe: test/CMakeFiles/CubeView.dir/linkLibs.rsp
bin/test/CubeView.exe: test/CMakeFiles/CubeView.dir/objects1.rsp
bin/test/CubeView.exe: test/CMakeFiles/CubeView.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=D:\Project\CSC10008_ComputerNetworking\ControlledMachine\Client\Client\giaoDien\fltk\fltk-1.4.0-1\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX executable ..\bin\test\CubeView.exe"
	cd /d D:\Project\CSC10008_ComputerNetworking\ControlledMachine\Client\Client\giaoDien\fltk\fltk-1.4.0-1\build\test && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\CubeView.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
test/CMakeFiles/CubeView.dir/build: bin/test/CubeView.exe
.PHONY : test/CMakeFiles/CubeView.dir/build

test/CMakeFiles/CubeView.dir/clean:
	cd /d D:\Project\CSC10008_ComputerNetworking\ControlledMachine\Client\Client\giaoDien\fltk\fltk-1.4.0-1\build\test && $(CMAKE_COMMAND) -P CMakeFiles\CubeView.dir\cmake_clean.cmake
.PHONY : test/CMakeFiles/CubeView.dir/clean

test/CMakeFiles/CubeView.dir/depend: test/CubeViewUI.cxx
test/CMakeFiles/CubeView.dir/depend: test/CubeViewUI.h
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\Project\CSC10008_ComputerNetworking\ControlledMachine\Client\Client\giaoDien\fltk\fltk-1.4.0-1 D:\Project\CSC10008_ComputerNetworking\ControlledMachine\Client\Client\giaoDien\fltk\fltk-1.4.0-1\test D:\Project\CSC10008_ComputerNetworking\ControlledMachine\Client\Client\giaoDien\fltk\fltk-1.4.0-1\build D:\Project\CSC10008_ComputerNetworking\ControlledMachine\Client\Client\giaoDien\fltk\fltk-1.4.0-1\build\test D:\Project\CSC10008_ComputerNetworking\ControlledMachine\Client\Client\giaoDien\fltk\fltk-1.4.0-1\build\test\CMakeFiles\CubeView.dir\DependInfo.cmake "--color=$(COLOR)"
.PHONY : test/CMakeFiles/CubeView.dir/depend

