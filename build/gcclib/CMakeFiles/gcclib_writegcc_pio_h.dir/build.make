# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.28

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

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /opt/homebrew/Cellar/cmake/3.28.3/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/Cellar/cmake/3.28.3/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/Users/andyvotava/src/GCC library"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/Users/andyvotava/src/GCC library/build"

# Utility rule file for gcclib_writegcc_pio_h.

# Include any custom commands dependencies for this target.
include gcclib/CMakeFiles/gcclib_writegcc_pio_h.dir/compiler_depend.make

# Include the progress variables for this target.
include gcclib/CMakeFiles/gcclib_writegcc_pio_h.dir/progress.make

gcclib/CMakeFiles/gcclib_writegcc_pio_h: gcclib/writegcc.pio.h

gcclib/writegcc.pio.h: /Users/andyvotava/src/GCC\ library/gcclib/pio/writegcc.pio
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --blue --bold --progress-dir="/Users/andyvotava/src/GCC library/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Generating writegcc.pio.h"
	cd "/Users/andyvotava/src/GCC library/build/gcclib" && ../pioasm/pioasm -o c-sdk "/Users/andyvotava/src/GCC library/gcclib/pio/writegcc.pio" "/Users/andyvotava/src/GCC library/build/gcclib/writegcc.pio.h"

gcclib_writegcc_pio_h: gcclib/CMakeFiles/gcclib_writegcc_pio_h
gcclib_writegcc_pio_h: gcclib/writegcc.pio.h
gcclib_writegcc_pio_h: gcclib/CMakeFiles/gcclib_writegcc_pio_h.dir/build.make
.PHONY : gcclib_writegcc_pio_h

# Rule to build all files generated by this target.
gcclib/CMakeFiles/gcclib_writegcc_pio_h.dir/build: gcclib_writegcc_pio_h
.PHONY : gcclib/CMakeFiles/gcclib_writegcc_pio_h.dir/build

gcclib/CMakeFiles/gcclib_writegcc_pio_h.dir/clean:
	cd "/Users/andyvotava/src/GCC library/build/gcclib" && $(CMAKE_COMMAND) -P CMakeFiles/gcclib_writegcc_pio_h.dir/cmake_clean.cmake
.PHONY : gcclib/CMakeFiles/gcclib_writegcc_pio_h.dir/clean

gcclib/CMakeFiles/gcclib_writegcc_pio_h.dir/depend:
	cd "/Users/andyvotava/src/GCC library/build" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/Users/andyvotava/src/GCC library" "/Users/andyvotava/src/GCC library/gcclib" "/Users/andyvotava/src/GCC library/build" "/Users/andyvotava/src/GCC library/build/gcclib" "/Users/andyvotava/src/GCC library/build/gcclib/CMakeFiles/gcclib_writegcc_pio_h.dir/DependInfo.cmake" "--color=$(COLOR)"
.PHONY : gcclib/CMakeFiles/gcclib_writegcc_pio_h.dir/depend

