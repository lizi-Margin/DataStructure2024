# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.29

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
CMAKE_SOURCE_DIR = C:\Users\33149\Desktop\DS2024\pack

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\33149\Desktop\DS2024\pack\build

# Include any dependencies generated for this target.
include bin/CMakeFiles/subpack.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include bin/CMakeFiles/subpack.dir/compiler_depend.make

# Include the progress variables for this target.
include bin/CMakeFiles/subpack.dir/progress.make

# Include the compile flags for this target's objects.
include bin/CMakeFiles/subpack.dir/flags.make

bin/CMakeFiles/subpack.dir/List.cpp.obj: bin/CMakeFiles/subpack.dir/flags.make
bin/CMakeFiles/subpack.dir/List.cpp.obj: C:/Users/33149/Desktop/DS2024/pack/util/List.cpp
bin/CMakeFiles/subpack.dir/List.cpp.obj: bin/CMakeFiles/subpack.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Users\33149\Desktop\DS2024\pack\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object bin/CMakeFiles/subpack.dir/List.cpp.obj"
	cd /d C:\Users\33149\Desktop\DS2024\pack\build\bin && C:\Users\33149\scoop\apps\mingw-winlibs-llvm\current\bin\clang++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT bin/CMakeFiles/subpack.dir/List.cpp.obj -MF CMakeFiles\subpack.dir\List.cpp.obj.d -o CMakeFiles\subpack.dir\List.cpp.obj -c C:\Users\33149\Desktop\DS2024\pack\util\List.cpp

bin/CMakeFiles/subpack.dir/List.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/subpack.dir/List.cpp.i"
	cd /d C:\Users\33149\Desktop\DS2024\pack\build\bin && C:\Users\33149\scoop\apps\mingw-winlibs-llvm\current\bin\clang++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\33149\Desktop\DS2024\pack\util\List.cpp > CMakeFiles\subpack.dir\List.cpp.i

bin/CMakeFiles/subpack.dir/List.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/subpack.dir/List.cpp.s"
	cd /d C:\Users\33149\Desktop\DS2024\pack\build\bin && C:\Users\33149\scoop\apps\mingw-winlibs-llvm\current\bin\clang++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\33149\Desktop\DS2024\pack\util\List.cpp -o CMakeFiles\subpack.dir\List.cpp.s

bin/CMakeFiles/subpack.dir/Comments.cpp.obj: bin/CMakeFiles/subpack.dir/flags.make
bin/CMakeFiles/subpack.dir/Comments.cpp.obj: C:/Users/33149/Desktop/DS2024/pack/util/Comments.cpp
bin/CMakeFiles/subpack.dir/Comments.cpp.obj: bin/CMakeFiles/subpack.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Users\33149\Desktop\DS2024\pack\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object bin/CMakeFiles/subpack.dir/Comments.cpp.obj"
	cd /d C:\Users\33149\Desktop\DS2024\pack\build\bin && C:\Users\33149\scoop\apps\mingw-winlibs-llvm\current\bin\clang++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT bin/CMakeFiles/subpack.dir/Comments.cpp.obj -MF CMakeFiles\subpack.dir\Comments.cpp.obj.d -o CMakeFiles\subpack.dir\Comments.cpp.obj -c C:\Users\33149\Desktop\DS2024\pack\util\Comments.cpp

bin/CMakeFiles/subpack.dir/Comments.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/subpack.dir/Comments.cpp.i"
	cd /d C:\Users\33149\Desktop\DS2024\pack\build\bin && C:\Users\33149\scoop\apps\mingw-winlibs-llvm\current\bin\clang++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\33149\Desktop\DS2024\pack\util\Comments.cpp > CMakeFiles\subpack.dir\Comments.cpp.i

bin/CMakeFiles/subpack.dir/Comments.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/subpack.dir/Comments.cpp.s"
	cd /d C:\Users\33149\Desktop\DS2024\pack\build\bin && C:\Users\33149\scoop\apps\mingw-winlibs-llvm\current\bin\clang++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\33149\Desktop\DS2024\pack\util\Comments.cpp -o CMakeFiles\subpack.dir\Comments.cpp.s

# Object files for target subpack
subpack_OBJECTS = \
"CMakeFiles/subpack.dir/List.cpp.obj" \
"CMakeFiles/subpack.dir/Comments.cpp.obj"

# External object files for target subpack
subpack_EXTERNAL_OBJECTS =

bin/subpack.exe: bin/CMakeFiles/subpack.dir/List.cpp.obj
bin/subpack.exe: bin/CMakeFiles/subpack.dir/Comments.cpp.obj
bin/subpack.exe: bin/CMakeFiles/subpack.dir/build.make
bin/subpack.exe: bin/CMakeFiles/subpack.dir/linkLibs.rsp
bin/subpack.exe: bin/CMakeFiles/subpack.dir/objects1.rsp
bin/subpack.exe: bin/CMakeFiles/subpack.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=C:\Users\33149\Desktop\DS2024\pack\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable subpack.exe"
	cd /d C:\Users\33149\Desktop\DS2024\pack\build\bin && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\subpack.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
bin/CMakeFiles/subpack.dir/build: bin/subpack.exe
.PHONY : bin/CMakeFiles/subpack.dir/build

bin/CMakeFiles/subpack.dir/clean:
	cd /d C:\Users\33149\Desktop\DS2024\pack\build\bin && $(CMAKE_COMMAND) -P CMakeFiles\subpack.dir\cmake_clean.cmake
.PHONY : bin/CMakeFiles/subpack.dir/clean

bin/CMakeFiles/subpack.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\33149\Desktop\DS2024\pack C:\Users\33149\Desktop\DS2024\pack\util C:\Users\33149\Desktop\DS2024\pack\build C:\Users\33149\Desktop\DS2024\pack\build\bin C:\Users\33149\Desktop\DS2024\pack\build\bin\CMakeFiles\subpack.dir\DependInfo.cmake "--color=$(COLOR)"
.PHONY : bin/CMakeFiles/subpack.dir/depend
