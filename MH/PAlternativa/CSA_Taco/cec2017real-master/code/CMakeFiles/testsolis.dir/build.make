# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /mnt/d/JorgeGangosoKlock/Universidad/Asignaturas/MH/PAlternativa/CSA_Taco/cec2017real-master/code

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/d/JorgeGangosoKlock/Universidad/Asignaturas/MH/PAlternativa/CSA_Taco/cec2017real-master/code

# Include any dependencies generated for this target.
include CMakeFiles/testsolis.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/testsolis.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/testsolis.dir/flags.make

CMakeFiles/testsolis.dir/testsolis.o: CMakeFiles/testsolis.dir/flags.make
CMakeFiles/testsolis.dir/testsolis.o: testsolis.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/d/JorgeGangosoKlock/Universidad/Asignaturas/MH/PAlternativa/CSA_Taco/cec2017real-master/code/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/testsolis.dir/testsolis.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/testsolis.dir/testsolis.o -c /mnt/d/JorgeGangosoKlock/Universidad/Asignaturas/MH/PAlternativa/CSA_Taco/cec2017real-master/code/testsolis.cc

CMakeFiles/testsolis.dir/testsolis.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/testsolis.dir/testsolis.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/d/JorgeGangosoKlock/Universidad/Asignaturas/MH/PAlternativa/CSA_Taco/cec2017real-master/code/testsolis.cc > CMakeFiles/testsolis.dir/testsolis.i

CMakeFiles/testsolis.dir/testsolis.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/testsolis.dir/testsolis.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/d/JorgeGangosoKlock/Universidad/Asignaturas/MH/PAlternativa/CSA_Taco/cec2017real-master/code/testsolis.cc -o CMakeFiles/testsolis.dir/testsolis.s

CMakeFiles/testsolis.dir/testsolis.o.requires:

.PHONY : CMakeFiles/testsolis.dir/testsolis.o.requires

CMakeFiles/testsolis.dir/testsolis.o.provides: CMakeFiles/testsolis.dir/testsolis.o.requires
	$(MAKE) -f CMakeFiles/testsolis.dir/build.make CMakeFiles/testsolis.dir/testsolis.o.provides.build
.PHONY : CMakeFiles/testsolis.dir/testsolis.o.provides

CMakeFiles/testsolis.dir/testsolis.o.provides.build: CMakeFiles/testsolis.dir/testsolis.o


# Object files for target testsolis
testsolis_OBJECTS = \
"CMakeFiles/testsolis.dir/testsolis.o"

# External object files for target testsolis
testsolis_EXTERNAL_OBJECTS =

testsolis: CMakeFiles/testsolis.dir/testsolis.o
testsolis: CMakeFiles/testsolis.dir/build.make
testsolis: libcec17_test_func.so
testsolis: CMakeFiles/testsolis.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/d/JorgeGangosoKlock/Universidad/Asignaturas/MH/PAlternativa/CSA_Taco/cec2017real-master/code/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable testsolis"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/testsolis.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/testsolis.dir/build: testsolis

.PHONY : CMakeFiles/testsolis.dir/build

CMakeFiles/testsolis.dir/requires: CMakeFiles/testsolis.dir/testsolis.o.requires

.PHONY : CMakeFiles/testsolis.dir/requires

CMakeFiles/testsolis.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/testsolis.dir/cmake_clean.cmake
.PHONY : CMakeFiles/testsolis.dir/clean

CMakeFiles/testsolis.dir/depend:
	cd /mnt/d/JorgeGangosoKlock/Universidad/Asignaturas/MH/PAlternativa/CSA_Taco/cec2017real-master/code && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/d/JorgeGangosoKlock/Universidad/Asignaturas/MH/PAlternativa/CSA_Taco/cec2017real-master/code /mnt/d/JorgeGangosoKlock/Universidad/Asignaturas/MH/PAlternativa/CSA_Taco/cec2017real-master/code /mnt/d/JorgeGangosoKlock/Universidad/Asignaturas/MH/PAlternativa/CSA_Taco/cec2017real-master/code /mnt/d/JorgeGangosoKlock/Universidad/Asignaturas/MH/PAlternativa/CSA_Taco/cec2017real-master/code /mnt/d/JorgeGangosoKlock/Universidad/Asignaturas/MH/PAlternativa/CSA_Taco/cec2017real-master/code/CMakeFiles/testsolis.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/testsolis.dir/depend
