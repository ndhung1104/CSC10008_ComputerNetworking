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
include test/CMakeFiles/forms.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include test/CMakeFiles/forms.dir/compiler_depend.make

# Include the progress variables for this target.
include test/CMakeFiles/forms.dir/progress.make

# Include the compile flags for this target's objects.
include test/CMakeFiles/forms.dir/flags.make

test/CMakeFiles/forms.dir/codegen:
.PHONY : test/CMakeFiles/forms.dir/codegen

test/CMakeFiles/forms.dir/forms.cxx.obj: test/CMakeFiles/forms.dir/flags.make
test/CMakeFiles/forms.dir/forms.cxx.obj: test/CMakeFiles/forms.dir/includes_CXX.rsp
test/CMakeFiles/forms.dir/forms.cxx.obj: D:/Project/CSC10008_ComputerNetworking/ControlledMachine/Client/Client/giaoDien/fltk/fltk-1.4.0-1/test/forms.cxx
test/CMakeFiles/forms.dir/forms.cxx.obj: test/CMakeFiles/forms.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=D:\Project\CSC10008_ComputerNetworking\ControlledMachine\Client\Client\giaoDien\fltk\fltk-1.4.0-1\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object test/CMakeFiles/forms.dir/forms.cxx.obj"
	cd /d D:\Project\CSC10008_ComputerNetworking\ControlledMachine\Client\Client\giaoDien\fltk\fltk-1.4.0-1\build\test && C:\msys64\ucrt64\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT test/CMakeFiles/forms.dir/forms.cxx.obj -MF CMakeFiles\forms.dir\forms.cxx.obj.d -o CMakeFiles\forms.dir\forms.cxx.obj -c D:\Project\CSC10008_ComputerNetworking\ControlledMachine\Client\Client\giaoDien\fltk\fltk-1.4.0-1\test\forms.cxx

test/CMakeFiles/forms.dir/forms.cxx.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/forms.dir/forms.cxx.i"
	cd /d D:\Project\CSC10008_ComputerNetworking\ControlledMachine\Client\Client\giaoDien\fltk\fltk-1.4.0-1\build\test && C:\msys64\ucrt64\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\Project\CSC10008_ComputerNetworking\ControlledMachine\Client\Client\giaoDien\fltk\fltk-1.4.0-1\test\forms.cxx > CMakeFiles\forms.dir\forms.cxx.i

test/CMakeFiles/forms.dir/forms.cxx.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/forms.dir/forms.cxx.s"
	cd /d D:\Project\CSC10008_ComputerNetworking\ControlledMachine\Client\Client\giaoDien\fltk\fltk-1.4.0-1\build\test && C:\msys64\ucrt64\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\Project\CSC10008_ComputerNetworking\ControlledMachine\Client\Client\giaoDien\fltk\fltk-1.4.0-1\test\forms.cxx -o CMakeFiles\forms.dir\forms.cxx.s

# Object files for target forms
forms_OBJECTS = \
"CMakeFiles/forms.dir/forms.cxx.obj"

# External object files for target forms
forms_EXTERNAL_OBJECTS =

bin/test/forms.exe: test/CMakeFiles/forms.dir/forms.cxx.obj
bin/test/forms.exe: test/CMakeFiles/forms.dir/build.make
bin/test/forms.exe: lib/libfltk_forms.a
bin/test/forms.exe: lib/libfltk.a
bin/test/forms.exe: test/CMakeFiles/forms.dir/linkLibs.rsp
bin/test/forms.exe: test/CMakeFiles/forms.dir/objects1.rsp
bin/test/forms.exe: test/CMakeFiles/forms.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=D:\Project\CSC10008_ComputerNetworking\ControlledMachine\Client\Client\giaoDien\fltk\fltk-1.4.0-1\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ..\bin\test\forms.exe"
	cd /d D:\Project\CSC10008_ComputerNetworking\ControlledMachine\Client\Client\giaoDien\fltk\fltk-1.4.0-1\build\test && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\forms.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
test/CMakeFiles/forms.dir/build: bin/test/forms.exe
.PHONY : test/CMakeFiles/forms.dir/build

test/CMakeFiles/forms.dir/clean:
	cd /d D:\Project\CSC10008_ComputerNetworking\ControlledMachine\Client\Client\giaoDien\fltk\fltk-1.4.0-1\build\test && $(CMAKE_COMMAND) -P CMakeFiles\forms.dir\cmake_clean.cmake
.PHONY : test/CMakeFiles/forms.dir/clean

test/CMakeFiles/forms.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\Project\CSC10008_ComputerNetworking\ControlledMachine\Client\Client\giaoDien\fltk\fltk-1.4.0-1 D:\Project\CSC10008_ComputerNetworking\ControlledMachine\Client\Client\giaoDien\fltk\fltk-1.4.0-1\test D:\Project\CSC10008_ComputerNetworking\ControlledMachine\Client\Client\giaoDien\fltk\fltk-1.4.0-1\build D:\Project\CSC10008_ComputerNetworking\ControlledMachine\Client\Client\giaoDien\fltk\fltk-1.4.0-1\build\test D:\Project\CSC10008_ComputerNetworking\ControlledMachine\Client\Client\giaoDien\fltk\fltk-1.4.0-1\build\test\CMakeFiles\forms.dir\DependInfo.cmake "--color=$(COLOR)"
.PHONY : test/CMakeFiles/forms.dir/depend
