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

# Utility rule file for html.

# Include any custom commands dependencies for this target.
include documentation/CMakeFiles/html.dir/compiler_depend.make

# Include the progress variables for this target.
include documentation/CMakeFiles/html.dir/progress.make

documentation/CMakeFiles/html: documentation/Doxyfile
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --blue --bold --progress-dir=D:\Project\CSC10008_ComputerNetworking\ControlledMachine\Client\Client\giaoDien\fltk\fltk-1.4.0-1\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Generating HTML documentation"
	cd /d D:\Project\CSC10008_ComputerNetworking\ControlledMachine\Client\Client\giaoDien\fltk\fltk-1.4.0-1\build\documentation && "C:\Program Files\doxygen\bin\doxygen.exe" Doxyfile

documentation/Doxyfile:
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --blue --bold --progress-dir=D:\Project\CSC10008_ComputerNetworking\ControlledMachine\Client\Client\giaoDien\fltk\fltk-1.4.0-1\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Converting Doxyfile to doxygen version 1.12.0"
	cd /d D:\Project\CSC10008_ComputerNetworking\ControlledMachine\Client\Client\giaoDien\fltk\fltk-1.4.0-1\build\documentation && D:\Project\CSC10008_ComputerNetworking\ControlledMachine\Client\Client\giaoDien\fltk\fltk-1.4.0-1\documentation\convert_doxyfile "C:/Program Files/doxygen/bin/doxygen.exe" Doxyfile.in Doxyfile D:/Project/CSC10008_ComputerNetworking/ControlledMachine/Client/Client/giaoDien/fltk/fltk-1.4.0-1/build/documentation/Doxyfile_error.log

documentation/CMakeFiles/html.dir/codegen:
.PHONY : documentation/CMakeFiles/html.dir/codegen

html: documentation/CMakeFiles/html
html: documentation/Doxyfile
html: documentation/CMakeFiles/html.dir/build.make
.PHONY : html

# Rule to build all files generated by this target.
documentation/CMakeFiles/html.dir/build: html
.PHONY : documentation/CMakeFiles/html.dir/build

documentation/CMakeFiles/html.dir/clean:
	cd /d D:\Project\CSC10008_ComputerNetworking\ControlledMachine\Client\Client\giaoDien\fltk\fltk-1.4.0-1\build\documentation && $(CMAKE_COMMAND) -P CMakeFiles\html.dir\cmake_clean.cmake
.PHONY : documentation/CMakeFiles/html.dir/clean

documentation/CMakeFiles/html.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\Project\CSC10008_ComputerNetworking\ControlledMachine\Client\Client\giaoDien\fltk\fltk-1.4.0-1 D:\Project\CSC10008_ComputerNetworking\ControlledMachine\Client\Client\giaoDien\fltk\fltk-1.4.0-1\documentation D:\Project\CSC10008_ComputerNetworking\ControlledMachine\Client\Client\giaoDien\fltk\fltk-1.4.0-1\build D:\Project\CSC10008_ComputerNetworking\ControlledMachine\Client\Client\giaoDien\fltk\fltk-1.4.0-1\build\documentation D:\Project\CSC10008_ComputerNetworking\ControlledMachine\Client\Client\giaoDien\fltk\fltk-1.4.0-1\build\documentation\CMakeFiles\html.dir\DependInfo.cmake "--color=$(COLOR)"
.PHONY : documentation/CMakeFiles/html.dir/depend
