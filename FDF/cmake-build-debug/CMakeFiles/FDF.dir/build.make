# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.14

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = "/Users/mcamila/Desktop/3 ,.app/Contents/bin/cmake/mac/bin/cmake"

# The command to remove a file.
RM = "/Users/mcamila/Desktop/3 ,.app/Contents/bin/cmake/mac/bin/cmake" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/mcamila/MyProjects/42/42/FDF

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/mcamila/MyProjects/42/42/FDF/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/FDF.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/FDF.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/FDF.dir/flags.make

CMakeFiles/FDF.dir/draw_line.c.o: CMakeFiles/FDF.dir/flags.make
CMakeFiles/FDF.dir/draw_line.c.o: ../draw_line.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/mcamila/MyProjects/42/42/FDF/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/FDF.dir/draw_line.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/FDF.dir/draw_line.c.o   -c /Users/mcamila/MyProjects/42/42/FDF/draw_line.c

CMakeFiles/FDF.dir/draw_line.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/FDF.dir/draw_line.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/mcamila/MyProjects/42/42/FDF/draw_line.c > CMakeFiles/FDF.dir/draw_line.c.i

CMakeFiles/FDF.dir/draw_line.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/FDF.dir/draw_line.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/mcamila/MyProjects/42/42/FDF/draw_line.c -o CMakeFiles/FDF.dir/draw_line.c.s

CMakeFiles/FDF.dir/functions.c.o: CMakeFiles/FDF.dir/flags.make
CMakeFiles/FDF.dir/functions.c.o: ../functions.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/mcamila/MyProjects/42/42/FDF/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/FDF.dir/functions.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/FDF.dir/functions.c.o   -c /Users/mcamila/MyProjects/42/42/FDF/functions.c

CMakeFiles/FDF.dir/functions.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/FDF.dir/functions.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/mcamila/MyProjects/42/42/FDF/functions.c > CMakeFiles/FDF.dir/functions.c.i

CMakeFiles/FDF.dir/functions.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/FDF.dir/functions.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/mcamila/MyProjects/42/42/FDF/functions.c -o CMakeFiles/FDF.dir/functions.c.s

CMakeFiles/FDF.dir/main.c.o: CMakeFiles/FDF.dir/flags.make
CMakeFiles/FDF.dir/main.c.o: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/mcamila/MyProjects/42/42/FDF/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/FDF.dir/main.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/FDF.dir/main.c.o   -c /Users/mcamila/MyProjects/42/42/FDF/main.c

CMakeFiles/FDF.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/FDF.dir/main.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/mcamila/MyProjects/42/42/FDF/main.c > CMakeFiles/FDF.dir/main.c.i

CMakeFiles/FDF.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/FDF.dir/main.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/mcamila/MyProjects/42/42/FDF/main.c -o CMakeFiles/FDF.dir/main.c.s

CMakeFiles/FDF.dir/render.c.o: CMakeFiles/FDF.dir/flags.make
CMakeFiles/FDF.dir/render.c.o: ../render.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/mcamila/MyProjects/42/42/FDF/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/FDF.dir/render.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/FDF.dir/render.c.o   -c /Users/mcamila/MyProjects/42/42/FDF/render.c

CMakeFiles/FDF.dir/render.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/FDF.dir/render.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/mcamila/MyProjects/42/42/FDF/render.c > CMakeFiles/FDF.dir/render.c.i

CMakeFiles/FDF.dir/render.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/FDF.dir/render.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/mcamila/MyProjects/42/42/FDF/render.c -o CMakeFiles/FDF.dir/render.c.s

CMakeFiles/FDF.dir/matrix.c.o: CMakeFiles/FDF.dir/flags.make
CMakeFiles/FDF.dir/matrix.c.o: ../matrix.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/mcamila/MyProjects/42/42/FDF/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object CMakeFiles/FDF.dir/matrix.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/FDF.dir/matrix.c.o   -c /Users/mcamila/MyProjects/42/42/FDF/matrix.c

CMakeFiles/FDF.dir/matrix.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/FDF.dir/matrix.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/mcamila/MyProjects/42/42/FDF/matrix.c > CMakeFiles/FDF.dir/matrix.c.i

CMakeFiles/FDF.dir/matrix.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/FDF.dir/matrix.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/mcamila/MyProjects/42/42/FDF/matrix.c -o CMakeFiles/FDF.dir/matrix.c.s

CMakeFiles/FDF.dir/map_parser.c.o: CMakeFiles/FDF.dir/flags.make
CMakeFiles/FDF.dir/map_parser.c.o: ../map_parser.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/mcamila/MyProjects/42/42/FDF/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building C object CMakeFiles/FDF.dir/map_parser.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/FDF.dir/map_parser.c.o   -c /Users/mcamila/MyProjects/42/42/FDF/map_parser.c

CMakeFiles/FDF.dir/map_parser.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/FDF.dir/map_parser.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/mcamila/MyProjects/42/42/FDF/map_parser.c > CMakeFiles/FDF.dir/map_parser.c.i

CMakeFiles/FDF.dir/map_parser.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/FDF.dir/map_parser.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/mcamila/MyProjects/42/42/FDF/map_parser.c -o CMakeFiles/FDF.dir/map_parser.c.s

# Object files for target FDF
FDF_OBJECTS = \
"CMakeFiles/FDF.dir/draw_line.c.o" \
"CMakeFiles/FDF.dir/functions.c.o" \
"CMakeFiles/FDF.dir/main.c.o" \
"CMakeFiles/FDF.dir/render.c.o" \
"CMakeFiles/FDF.dir/matrix.c.o" \
"CMakeFiles/FDF.dir/map_parser.c.o"

# External object files for target FDF
FDF_EXTERNAL_OBJECTS =

FDF: CMakeFiles/FDF.dir/draw_line.c.o
FDF: CMakeFiles/FDF.dir/functions.c.o
FDF: CMakeFiles/FDF.dir/main.c.o
FDF: CMakeFiles/FDF.dir/render.c.o
FDF: CMakeFiles/FDF.dir/matrix.c.o
FDF: CMakeFiles/FDF.dir/map_parser.c.o
FDF: CMakeFiles/FDF.dir/build.make
FDF: libmlx.a
FDF: liblibft.a
FDF: CMakeFiles/FDF.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/mcamila/MyProjects/42/42/FDF/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Linking C executable FDF"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/FDF.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/FDF.dir/build: FDF

.PHONY : CMakeFiles/FDF.dir/build

CMakeFiles/FDF.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/FDF.dir/cmake_clean.cmake
.PHONY : CMakeFiles/FDF.dir/clean

CMakeFiles/FDF.dir/depend:
	cd /Users/mcamila/MyProjects/42/42/FDF/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/mcamila/MyProjects/42/42/FDF /Users/mcamila/MyProjects/42/42/FDF /Users/mcamila/MyProjects/42/42/FDF/cmake-build-debug /Users/mcamila/MyProjects/42/42/FDF/cmake-build-debug /Users/mcamila/MyProjects/42/42/FDF/cmake-build-debug/CMakeFiles/FDF.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/FDF.dir/depend

