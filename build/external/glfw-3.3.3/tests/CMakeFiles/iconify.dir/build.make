# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.20

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
CMAKE_SOURCE_DIR = C:\Users\Gui\Documents\GitHub\CG

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\Gui\Documents\GitHub\CG\build

# Include any dependencies generated for this target.
include external/glfw-3.3.3/tests/CMakeFiles/iconify.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include external/glfw-3.3.3/tests/CMakeFiles/iconify.dir/compiler_depend.make

# Include the progress variables for this target.
include external/glfw-3.3.3/tests/CMakeFiles/iconify.dir/progress.make

# Include the compile flags for this target's objects.
include external/glfw-3.3.3/tests/CMakeFiles/iconify.dir/flags.make

external/glfw-3.3.3/tests/CMakeFiles/iconify.dir/iconify.c.obj: external/glfw-3.3.3/tests/CMakeFiles/iconify.dir/flags.make
external/glfw-3.3.3/tests/CMakeFiles/iconify.dir/iconify.c.obj: external/glfw-3.3.3/tests/CMakeFiles/iconify.dir/includes_C.rsp
external/glfw-3.3.3/tests/CMakeFiles/iconify.dir/iconify.c.obj: ../external/glfw-3.3.3/tests/iconify.c
external/glfw-3.3.3/tests/CMakeFiles/iconify.dir/iconify.c.obj: external/glfw-3.3.3/tests/CMakeFiles/iconify.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\Gui\Documents\GitHub\CG\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object external/glfw-3.3.3/tests/CMakeFiles/iconify.dir/iconify.c.obj"
	cd /d C:\Users\Gui\Documents\GitHub\CG\build\external\glfw-3.3.3\tests && C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT external/glfw-3.3.3/tests/CMakeFiles/iconify.dir/iconify.c.obj -MF CMakeFiles\iconify.dir\iconify.c.obj.d -o CMakeFiles\iconify.dir\iconify.c.obj -c C:\Users\Gui\Documents\GitHub\CG\external\glfw-3.3.3\tests\iconify.c

external/glfw-3.3.3/tests/CMakeFiles/iconify.dir/iconify.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/iconify.dir/iconify.c.i"
	cd /d C:\Users\Gui\Documents\GitHub\CG\build\external\glfw-3.3.3\tests && C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\Gui\Documents\GitHub\CG\external\glfw-3.3.3\tests\iconify.c > CMakeFiles\iconify.dir\iconify.c.i

external/glfw-3.3.3/tests/CMakeFiles/iconify.dir/iconify.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/iconify.dir/iconify.c.s"
	cd /d C:\Users\Gui\Documents\GitHub\CG\build\external\glfw-3.3.3\tests && C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\Gui\Documents\GitHub\CG\external\glfw-3.3.3\tests\iconify.c -o CMakeFiles\iconify.dir\iconify.c.s

external/glfw-3.3.3/tests/CMakeFiles/iconify.dir/__/deps/getopt.c.obj: external/glfw-3.3.3/tests/CMakeFiles/iconify.dir/flags.make
external/glfw-3.3.3/tests/CMakeFiles/iconify.dir/__/deps/getopt.c.obj: external/glfw-3.3.3/tests/CMakeFiles/iconify.dir/includes_C.rsp
external/glfw-3.3.3/tests/CMakeFiles/iconify.dir/__/deps/getopt.c.obj: ../external/glfw-3.3.3/deps/getopt.c
external/glfw-3.3.3/tests/CMakeFiles/iconify.dir/__/deps/getopt.c.obj: external/glfw-3.3.3/tests/CMakeFiles/iconify.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\Gui\Documents\GitHub\CG\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object external/glfw-3.3.3/tests/CMakeFiles/iconify.dir/__/deps/getopt.c.obj"
	cd /d C:\Users\Gui\Documents\GitHub\CG\build\external\glfw-3.3.3\tests && C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT external/glfw-3.3.3/tests/CMakeFiles/iconify.dir/__/deps/getopt.c.obj -MF CMakeFiles\iconify.dir\__\deps\getopt.c.obj.d -o CMakeFiles\iconify.dir\__\deps\getopt.c.obj -c C:\Users\Gui\Documents\GitHub\CG\external\glfw-3.3.3\deps\getopt.c

external/glfw-3.3.3/tests/CMakeFiles/iconify.dir/__/deps/getopt.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/iconify.dir/__/deps/getopt.c.i"
	cd /d C:\Users\Gui\Documents\GitHub\CG\build\external\glfw-3.3.3\tests && C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\Gui\Documents\GitHub\CG\external\glfw-3.3.3\deps\getopt.c > CMakeFiles\iconify.dir\__\deps\getopt.c.i

external/glfw-3.3.3/tests/CMakeFiles/iconify.dir/__/deps/getopt.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/iconify.dir/__/deps/getopt.c.s"
	cd /d C:\Users\Gui\Documents\GitHub\CG\build\external\glfw-3.3.3\tests && C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\Gui\Documents\GitHub\CG\external\glfw-3.3.3\deps\getopt.c -o CMakeFiles\iconify.dir\__\deps\getopt.c.s

external/glfw-3.3.3/tests/CMakeFiles/iconify.dir/__/deps/glad_gl.c.obj: external/glfw-3.3.3/tests/CMakeFiles/iconify.dir/flags.make
external/glfw-3.3.3/tests/CMakeFiles/iconify.dir/__/deps/glad_gl.c.obj: external/glfw-3.3.3/tests/CMakeFiles/iconify.dir/includes_C.rsp
external/glfw-3.3.3/tests/CMakeFiles/iconify.dir/__/deps/glad_gl.c.obj: ../external/glfw-3.3.3/deps/glad_gl.c
external/glfw-3.3.3/tests/CMakeFiles/iconify.dir/__/deps/glad_gl.c.obj: external/glfw-3.3.3/tests/CMakeFiles/iconify.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\Gui\Documents\GitHub\CG\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object external/glfw-3.3.3/tests/CMakeFiles/iconify.dir/__/deps/glad_gl.c.obj"
	cd /d C:\Users\Gui\Documents\GitHub\CG\build\external\glfw-3.3.3\tests && C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT external/glfw-3.3.3/tests/CMakeFiles/iconify.dir/__/deps/glad_gl.c.obj -MF CMakeFiles\iconify.dir\__\deps\glad_gl.c.obj.d -o CMakeFiles\iconify.dir\__\deps\glad_gl.c.obj -c C:\Users\Gui\Documents\GitHub\CG\external\glfw-3.3.3\deps\glad_gl.c

external/glfw-3.3.3/tests/CMakeFiles/iconify.dir/__/deps/glad_gl.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/iconify.dir/__/deps/glad_gl.c.i"
	cd /d C:\Users\Gui\Documents\GitHub\CG\build\external\glfw-3.3.3\tests && C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\Gui\Documents\GitHub\CG\external\glfw-3.3.3\deps\glad_gl.c > CMakeFiles\iconify.dir\__\deps\glad_gl.c.i

external/glfw-3.3.3/tests/CMakeFiles/iconify.dir/__/deps/glad_gl.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/iconify.dir/__/deps/glad_gl.c.s"
	cd /d C:\Users\Gui\Documents\GitHub\CG\build\external\glfw-3.3.3\tests && C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\Gui\Documents\GitHub\CG\external\glfw-3.3.3\deps\glad_gl.c -o CMakeFiles\iconify.dir\__\deps\glad_gl.c.s

# Object files for target iconify
iconify_OBJECTS = \
"CMakeFiles/iconify.dir/iconify.c.obj" \
"CMakeFiles/iconify.dir/__/deps/getopt.c.obj" \
"CMakeFiles/iconify.dir/__/deps/glad_gl.c.obj"

# External object files for target iconify
iconify_EXTERNAL_OBJECTS =

external/glfw-3.3.3/tests/iconify.exe: external/glfw-3.3.3/tests/CMakeFiles/iconify.dir/iconify.c.obj
external/glfw-3.3.3/tests/iconify.exe: external/glfw-3.3.3/tests/CMakeFiles/iconify.dir/__/deps/getopt.c.obj
external/glfw-3.3.3/tests/iconify.exe: external/glfw-3.3.3/tests/CMakeFiles/iconify.dir/__/deps/glad_gl.c.obj
external/glfw-3.3.3/tests/iconify.exe: external/glfw-3.3.3/tests/CMakeFiles/iconify.dir/build.make
external/glfw-3.3.3/tests/iconify.exe: external/glfw-3.3.3/src/libglfw3.a
external/glfw-3.3.3/tests/iconify.exe: external/glfw-3.3.3/tests/CMakeFiles/iconify.dir/linklibs.rsp
external/glfw-3.3.3/tests/iconify.exe: external/glfw-3.3.3/tests/CMakeFiles/iconify.dir/objects1.rsp
external/glfw-3.3.3/tests/iconify.exe: external/glfw-3.3.3/tests/CMakeFiles/iconify.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\Gui\Documents\GitHub\CG\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking C executable iconify.exe"
	cd /d C:\Users\Gui\Documents\GitHub\CG\build\external\glfw-3.3.3\tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\iconify.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
external/glfw-3.3.3/tests/CMakeFiles/iconify.dir/build: external/glfw-3.3.3/tests/iconify.exe
.PHONY : external/glfw-3.3.3/tests/CMakeFiles/iconify.dir/build

external/glfw-3.3.3/tests/CMakeFiles/iconify.dir/clean:
	cd /d C:\Users\Gui\Documents\GitHub\CG\build\external\glfw-3.3.3\tests && $(CMAKE_COMMAND) -P CMakeFiles\iconify.dir\cmake_clean.cmake
.PHONY : external/glfw-3.3.3/tests/CMakeFiles/iconify.dir/clean

external/glfw-3.3.3/tests/CMakeFiles/iconify.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\Gui\Documents\GitHub\CG C:\Users\Gui\Documents\GitHub\CG\external\glfw-3.3.3\tests C:\Users\Gui\Documents\GitHub\CG\build C:\Users\Gui\Documents\GitHub\CG\build\external\glfw-3.3.3\tests C:\Users\Gui\Documents\GitHub\CG\build\external\glfw-3.3.3\tests\CMakeFiles\iconify.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : external/glfw-3.3.3/tests/CMakeFiles/iconify.dir/depend

