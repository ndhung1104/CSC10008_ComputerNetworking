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
include test/CMakeFiles/pixmap.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include test/CMakeFiles/pixmap.dir/compiler_depend.make

# Include the progress variables for this target.
include test/CMakeFiles/pixmap.dir/progress.make

# Include the compile flags for this target's objects.
include test/CMakeFiles/pixmap.dir/flags.make

test/CMakeFiles/pixmap.dir/codegen:
.PHONY : test/CMakeFiles/pixmap.dir/codegen

test/CMakeFiles/pixmap.dir/pixmap.cxx.obj: test/CMakeFiles/pixmap.dir/flags.make
test/CMakeFiles/pixmap.dir/pixmap.cxx.obj: test/CMakeFiles/pixmap.dir/includes_CXX.rsp
test/CMakeFiles/pixmap.dir/pixmap.cxx.obj: D:/Project/CSC10008_ComputerNetworking/ControlledMachine/Client/Client/giaoDien/fltk/fltk-1.4.0-1/test/pixmap.cxx
test/CMakeFiles/pixmap.dir/pixmap.cxx.obj: test/CMakeFiles/pixmap.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=D:\Project\CSC10008_ComputerNetworking\ControlledMachine\Client\Client\giaoDien\fltk\fltk-1.4.0-1\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object test/CMakeFiles/pixmap.dir/pixmap.cxx.obj"
	cd /d D:\Project\CSC10008_ComputerNetworking\ControlledMachine\Client\Client\giaoDien\fltk\fltk-1.4.0-1\build\test && C:\msys64\ucrt64\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT test/CMakeFiles/pixmap.dir/pixmap.cxx.obj -MF CMakeFiles\pixmap.dir\pixmap.cxx.obj.d -o CMakeFiles\pixmap.dir\pixmap.cxx.obj -c D:\Project\CSC10008_ComputerNetworking\ControlledMachine\Client\Client\giaoDien\fltk\fltk-1.4.0-1\test\pixmap.cxx

test/CMakeFiles/pixmap.dir/pixmap.cxx.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/pixmap.dir/pixmap.cxx.i"
	cd /d D:\Project\CSC10008_ComputerNetworking\ControlledMachine\Client\Client\giaoDien\fltk\fltk-1.4.0-1\build\test && C:\msys64\ucrt64\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\Project\CSC10008_ComputerNetworking\ControlledMachine\Client\Client\giaoDien\fltk\fltk-1.4.0-1\test\pixmap.cxx > CMakeFiles\pixmap.dir\pixmap.cxx.i

test/CMakeFiles/pixmap.dir/pixmap.cxx.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/pixmap.dir/pixmap.cxx.s"
	cd /d D:\Project\CSC10008_ComputerNetworking\ControlledMachine\Client\Client\giaoDien\fltk\fltk-1.4.0-1\build\test && C:\msys64\ucrt64\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\Project\CSC10008_ComputerNetworking\ControlledMachine\Client\Client\giaoDien\fltk\fltk-1.4.0-1\test\pixmap.cxx -o CMakeFiles\pixmap.dir\pixmap.cxx.s

# Object files for target pixmap
pixmap_OBJECTS = \
"CMakeFiles/pixmap.dir/pixmap.cxx.obj"

# External object files for target pixmap
pixmap_EXTERNAL_OBJECTS =

bin/test/pixmap.exe: test/CMakeFiles/pixmap.dir/pixmap.cxx.obj
bin/test/pixmap.exe: test/CMakeFiles/pixmap.dir/build.make
bin/test/pixmap.exe: lib/libfltk_images.a
bin/test/pixmap.exe: lib/libfltk.a
bin/test/pixmap.exe: lib/libfltk_png.a
bin/test/pixmap.exe: lib/libfltk_z.a
bin/test/pixmap.exe: lib/libfltk_jpeg.a
bin/test/pixmap.exe: test/CMakeFiles/pixmap.dir/linkLibs.rsp
bin/test/pixmap.exe: test/CMakeFiles/pixmap.dir/objects1.rsp
bin/test/pixmap.exe: test/CMakeFiles/pixmap.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=D:\Project\CSC10008_ComputerNetworking\ControlledMachine\Client\Client\giaoDien\fltk\fltk-1.4.0-1\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ..\bin\test\pixmap.exe"
	cd /d D:\Project\CSC10008_ComputerNetworking\ControlledMachine\Client\Client\giaoDien\fltk\fltk-1.4.0-1\build\test && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\pixmap.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
test/CMakeFiles/pixmap.dir/build: bin/test/pixmap.exe
.PHONY : test/CMakeFiles/pixmap.dir/build

test/CMakeFiles/pixmap.dir/clean:
	cd /d D:\Project\CSC10008_ComputerNetworking\ControlledMachine\Client\Client\giaoDien\fltk\fltk-1.4.0-1\build\test && $(CMAKE_COMMAND) -P CMakeFiles\pixmap.dir\cmake_clean.cmake
.PHONY : test/CMakeFiles/pixmap.dir/clean

test/CMakeFiles/pixmap.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\Project\CSC10008_ComputerNetworking\ControlledMachine\Client\Client\giaoDien\fltk\fltk-1.4.0-1 D:\Project\CSC10008_ComputerNetworking\ControlledMachine\Client\Client\giaoDien\fltk\fltk-1.4.0-1\test D:\Project\CSC10008_ComputerNetworking\ControlledMachine\Client\Client\giaoDien\fltk\fltk-1.4.0-1\build D:\Project\CSC10008_ComputerNetworking\ControlledMachine\Client\Client\giaoDien\fltk\fltk-1.4.0-1\build\test D:\Project\CSC10008_ComputerNetworking\ControlledMachine\Client\Client\giaoDien\fltk\fltk-1.4.0-1\build\test\CMakeFiles\pixmap.dir\DependInfo.cmake "--color=$(COLOR)"
.PHONY : test/CMakeFiles/pixmap.dir/depend
