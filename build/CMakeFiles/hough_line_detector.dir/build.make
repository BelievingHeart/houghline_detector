# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.13

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
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/afterburner/CLionProjects/houghline_detector

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/afterburner/CLionProjects/houghline_detector/build

# Include any dependencies generated for this target.
include CMakeFiles/hough_line_detector.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/hough_line_detector.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/hough_line_detector.dir/flags.make

CMakeFiles/hough_line_detector.dir/main.cpp.o: CMakeFiles/hough_line_detector.dir/flags.make
CMakeFiles/hough_line_detector.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/afterburner/CLionProjects/houghline_detector/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/hough_line_detector.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/hough_line_detector.dir/main.cpp.o -c /home/afterburner/CLionProjects/houghline_detector/main.cpp

CMakeFiles/hough_line_detector.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/hough_line_detector.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/afterburner/CLionProjects/houghline_detector/main.cpp > CMakeFiles/hough_line_detector.dir/main.cpp.i

CMakeFiles/hough_line_detector.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/hough_line_detector.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/afterburner/CLionProjects/houghline_detector/main.cpp -o CMakeFiles/hough_line_detector.dir/main.cpp.s

# Object files for target hough_line_detector
hough_line_detector_OBJECTS = \
"CMakeFiles/hough_line_detector.dir/main.cpp.o"

# External object files for target hough_line_detector
hough_line_detector_EXTERNAL_OBJECTS =

hough_line_detector: CMakeFiles/hough_line_detector.dir/main.cpp.o
hough_line_detector: CMakeFiles/hough_line_detector.dir/build.make
hough_line_detector: /usr/local/lib/libopencv_highgui.so.4.0.0
hough_line_detector: /usr/local/lib/libopencv_videoio.so.4.0.0
hough_line_detector: /usr/local/lib/libopencv_imgcodecs.so.4.0.0
hough_line_detector: /usr/local/lib/libopencv_imgproc.so.4.0.0
hough_line_detector: /usr/local/lib/libopencv_core.so.4.0.0
hough_line_detector: CMakeFiles/hough_line_detector.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/afterburner/CLionProjects/houghline_detector/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable hough_line_detector"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/hough_line_detector.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/hough_line_detector.dir/build: hough_line_detector

.PHONY : CMakeFiles/hough_line_detector.dir/build

CMakeFiles/hough_line_detector.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/hough_line_detector.dir/cmake_clean.cmake
.PHONY : CMakeFiles/hough_line_detector.dir/clean

CMakeFiles/hough_line_detector.dir/depend:
	cd /home/afterburner/CLionProjects/houghline_detector/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/afterburner/CLionProjects/houghline_detector /home/afterburner/CLionProjects/houghline_detector /home/afterburner/CLionProjects/houghline_detector/build /home/afterburner/CLionProjects/houghline_detector/build /home/afterburner/CLionProjects/houghline_detector/build/CMakeFiles/hough_line_detector.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/hough_line_detector.dir/depend

