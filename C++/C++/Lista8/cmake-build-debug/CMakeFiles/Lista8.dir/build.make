# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.25

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
CMAKE_COMMAND = /snap/clion/235/bin/cmake/linux/x64/bin/cmake

# The command to remove a file.
RM = /snap/clion/235/bin/cmake/linux/x64/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/home/viktoria/Documents/Drugi semestr/Cpp/Lista8"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/home/viktoria/Documents/Drugi semestr/Cpp/Lista8/cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/Lista8.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/Lista8.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/Lista8.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Lista8.dir/flags.make

CMakeFiles/Lista8.dir/main.cpp.o: CMakeFiles/Lista8.dir/flags.make
CMakeFiles/Lista8.dir/main.cpp.o: /home/viktoria/Documents/Drugi\ semestr/Cpp/Lista8/main.cpp
CMakeFiles/Lista8.dir/main.cpp.o: CMakeFiles/Lista8.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/viktoria/Documents/Drugi semestr/Cpp/Lista8/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Lista8.dir/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Lista8.dir/main.cpp.o -MF CMakeFiles/Lista8.dir/main.cpp.o.d -o CMakeFiles/Lista8.dir/main.cpp.o -c "/home/viktoria/Documents/Drugi semestr/Cpp/Lista8/main.cpp"

CMakeFiles/Lista8.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Lista8.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/viktoria/Documents/Drugi semestr/Cpp/Lista8/main.cpp" > CMakeFiles/Lista8.dir/main.cpp.i

CMakeFiles/Lista8.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Lista8.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/viktoria/Documents/Drugi semestr/Cpp/Lista8/main.cpp" -o CMakeFiles/Lista8.dir/main.cpp.s

CMakeFiles/Lista8.dir/RationalNum.cpp.o: CMakeFiles/Lista8.dir/flags.make
CMakeFiles/Lista8.dir/RationalNum.cpp.o: /home/viktoria/Documents/Drugi\ semestr/Cpp/Lista8/RationalNum.cpp
CMakeFiles/Lista8.dir/RationalNum.cpp.o: CMakeFiles/Lista8.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/viktoria/Documents/Drugi semestr/Cpp/Lista8/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/Lista8.dir/RationalNum.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Lista8.dir/RationalNum.cpp.o -MF CMakeFiles/Lista8.dir/RationalNum.cpp.o.d -o CMakeFiles/Lista8.dir/RationalNum.cpp.o -c "/home/viktoria/Documents/Drugi semestr/Cpp/Lista8/RationalNum.cpp"

CMakeFiles/Lista8.dir/RationalNum.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Lista8.dir/RationalNum.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/viktoria/Documents/Drugi semestr/Cpp/Lista8/RationalNum.cpp" > CMakeFiles/Lista8.dir/RationalNum.cpp.i

CMakeFiles/Lista8.dir/RationalNum.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Lista8.dir/RationalNum.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/viktoria/Documents/Drugi semestr/Cpp/Lista8/RationalNum.cpp" -o CMakeFiles/Lista8.dir/RationalNum.cpp.s

# Object files for target Lista8
Lista8_OBJECTS = \
"CMakeFiles/Lista8.dir/main.cpp.o" \
"CMakeFiles/Lista8.dir/RationalNum.cpp.o"

# External object files for target Lista8
Lista8_EXTERNAL_OBJECTS =

Lista8: CMakeFiles/Lista8.dir/main.cpp.o
Lista8: CMakeFiles/Lista8.dir/RationalNum.cpp.o
Lista8: CMakeFiles/Lista8.dir/build.make
Lista8: CMakeFiles/Lista8.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/home/viktoria/Documents/Drugi semestr/Cpp/Lista8/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable Lista8"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Lista8.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Lista8.dir/build: Lista8
.PHONY : CMakeFiles/Lista8.dir/build

CMakeFiles/Lista8.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Lista8.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Lista8.dir/clean

CMakeFiles/Lista8.dir/depend:
	cd "/home/viktoria/Documents/Drugi semestr/Cpp/Lista8/cmake-build-debug" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/viktoria/Documents/Drugi semestr/Cpp/Lista8" "/home/viktoria/Documents/Drugi semestr/Cpp/Lista8" "/home/viktoria/Documents/Drugi semestr/Cpp/Lista8/cmake-build-debug" "/home/viktoria/Documents/Drugi semestr/Cpp/Lista8/cmake-build-debug" "/home/viktoria/Documents/Drugi semestr/Cpp/Lista8/cmake-build-debug/CMakeFiles/Lista8.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/Lista8.dir/depend
