# CMAKE generated file: DO NOT EDIT!
# Generated by "MSYS Makefiles" Generator, CMake Version 3.14

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
CMAKE_COMMAND = "/C/Program Files/CMake/bin/cmake.exe"

# The command to remove a file.
RM = "/C/Program Files/CMake/bin/cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /C/Users/luma/work/gtest-hoge

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /C/Users/luma/work/gtest-hoge/build

# Include any dependencies generated for this target.
include CMakeFiles/a.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/a.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/a.dir/flags.make

CMakeFiles/a.dir/a.cpp.obj: CMakeFiles/a.dir/flags.make
CMakeFiles/a.dir/a.cpp.obj: ../a.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/C/Users/luma/work/gtest-hoge/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/a.dir/a.cpp.obj"
	/C/git-sdk-64/mingw64/bin/g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/a.dir/a.cpp.obj -c /C/Users/luma/work/gtest-hoge/a.cpp

CMakeFiles/a.dir/a.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/a.dir/a.cpp.i"
	/C/git-sdk-64/mingw64/bin/g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /C/Users/luma/work/gtest-hoge/a.cpp > CMakeFiles/a.dir/a.cpp.i

CMakeFiles/a.dir/a.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/a.dir/a.cpp.s"
	/C/git-sdk-64/mingw64/bin/g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /C/Users/luma/work/gtest-hoge/a.cpp -o CMakeFiles/a.dir/a.cpp.s

# Object files for target a
a_OBJECTS = \
"CMakeFiles/a.dir/a.cpp.obj"

# External object files for target a
a_EXTERNAL_OBJECTS =

a.exe: CMakeFiles/a.dir/a.cpp.obj
a.exe: CMakeFiles/a.dir/build.make
a.exe: C:/git-sdk-64/mingw64/lib/libgtest_main.dll.a
a.exe: C:/git-sdk-64/mingw64/lib/libgtest.dll.a
a.exe: CMakeFiles/a.dir/linklibs.rsp
a.exe: CMakeFiles/a.dir/objects1.rsp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/C/Users/luma/work/gtest-hoge/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable a.exe"
	"/C/Program Files/CMake/bin/cmake.exe" -E remove -f CMakeFiles/a.dir/objects.a
	/C/git-sdk-64/mingw64/bin/ar.exe cr CMakeFiles/a.dir/objects.a @CMakeFiles/a.dir/objects1.rsp
	/C/git-sdk-64/mingw64/bin/g++.exe    -Wl,--whole-archive CMakeFiles/a.dir/objects.a -Wl,--no-whole-archive  -o a.exe -Wl,--out-implib,liba.dll.a -Wl,--major-image-version,0,--minor-image-version,0 @CMakeFiles/a.dir/linklibs.rsp

# Rule to build all files generated by this target.
CMakeFiles/a.dir/build: a.exe

.PHONY : CMakeFiles/a.dir/build

CMakeFiles/a.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/a.dir/cmake_clean.cmake
.PHONY : CMakeFiles/a.dir/clean

CMakeFiles/a.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MSYS Makefiles" /C/Users/luma/work/gtest-hoge /C/Users/luma/work/gtest-hoge /C/Users/luma/work/gtest-hoge/build /C/Users/luma/work/gtest-hoge/build /C/Users/luma/work/gtest-hoge/build/CMakeFiles/a.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/a.dir/depend

