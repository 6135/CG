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
include p1/CMakeFiles/p1.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include p1/CMakeFiles/p1.dir/compiler_depend.make

# Include the progress variables for this target.
include p1/CMakeFiles/p1.dir/progress.make

# Include the compile flags for this target's objects.
include p1/CMakeFiles/p1.dir/flags.make

p1/CMakeFiles/p1.dir/p1.cpp.obj: p1/CMakeFiles/p1.dir/flags.make
p1/CMakeFiles/p1.dir/p1.cpp.obj: p1/CMakeFiles/p1.dir/includes_CXX.rsp
p1/CMakeFiles/p1.dir/p1.cpp.obj: ../p1/p1.cpp
p1/CMakeFiles/p1.dir/p1.cpp.obj: p1/CMakeFiles/p1.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\Gui\Documents\GitHub\CG\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object p1/CMakeFiles/p1.dir/p1.cpp.obj"
	cd /d C:\Users\Gui\Documents\GitHub\CG\build\p1 && C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT p1/CMakeFiles/p1.dir/p1.cpp.obj -MF CMakeFiles\p1.dir\p1.cpp.obj.d -o CMakeFiles\p1.dir\p1.cpp.obj -c C:\Users\Gui\Documents\GitHub\CG\p1\p1.cpp

p1/CMakeFiles/p1.dir/p1.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/p1.dir/p1.cpp.i"
	cd /d C:\Users\Gui\Documents\GitHub\CG\build\p1 && C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\Gui\Documents\GitHub\CG\p1\p1.cpp > CMakeFiles\p1.dir\p1.cpp.i

p1/CMakeFiles/p1.dir/p1.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/p1.dir/p1.cpp.s"
	cd /d C:\Users\Gui\Documents\GitHub\CG\build\p1 && C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\Gui\Documents\GitHub\CG\p1\p1.cpp -o CMakeFiles\p1.dir\p1.cpp.s

# Object files for target p1
p1_OBJECTS = \
"CMakeFiles/p1.dir/p1.cpp.obj"

# External object files for target p1
p1_EXTERNAL_OBJECTS =

p1/p1.exe: p1/CMakeFiles/p1.dir/p1.cpp.obj
p1/p1.exe: p1/CMakeFiles/p1.dir/build.make
p1/p1.exe: external/glfw-3.3.3/src/libglfw3.a
p1/p1.exe: external/glad/libglad.a
p1/p1.exe: p1/CMakeFiles/p1.dir/linklibs.rsp
p1/p1.exe: p1/CMakeFiles/p1.dir/objects1.rsp
p1/p1.exe: p1/CMakeFiles/p1.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\Gui\Documents\GitHub\CG\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable p1.exe"
	cd /d C:\Users\Gui\Documents\GitHub\CG\build\p1 && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\p1.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
p1/CMakeFiles/p1.dir/build: p1/p1.exe
.PHONY : p1/CMakeFiles/p1.dir/build

p1/CMakeFiles/p1.dir/clean:
	cd /d C:\Users\Gui\Documents\GitHub\CG\build\p1 && $(CMAKE_COMMAND) -P CMakeFiles\p1.dir\cmake_clean.cmake
.PHONY : p1/CMakeFiles/p1.dir/clean

p1/CMakeFiles/p1.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\Gui\Documents\GitHub\CG C:\Users\Gui\Documents\GitHub\CG\p1 C:\Users\Gui\Documents\GitHub\CG\build C:\Users\Gui\Documents\GitHub\CG\build\p1 C:\Users\Gui\Documents\GitHub\CG\build\p1\CMakeFiles\p1.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : p1/CMakeFiles/p1.dir/depend
