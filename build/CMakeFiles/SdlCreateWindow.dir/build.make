# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.27

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
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.27.5/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.27.5/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/macos/Desktop/SDL-Assignment/sdl-game-dev/p1-sdl-create-app

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/macos/Desktop/SDL-Assignment/sdl-game-dev/p1-sdl-create-app/build

# Include any dependencies generated for this target.
include CMakeFiles/SdlCreateWindow.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/SdlCreateWindow.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/SdlCreateWindow.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/SdlCreateWindow.dir/flags.make

CMakeFiles/SdlCreateWindow.dir/src/main.cpp.o: CMakeFiles/SdlCreateWindow.dir/flags.make
CMakeFiles/SdlCreateWindow.dir/src/main.cpp.o: /Users/macos/Desktop/SDL-Assignment/sdl-game-dev/p1-sdl-create-app/src/main.cpp
CMakeFiles/SdlCreateWindow.dir/src/main.cpp.o: CMakeFiles/SdlCreateWindow.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/macos/Desktop/SDL-Assignment/sdl-game-dev/p1-sdl-create-app/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/SdlCreateWindow.dir/src/main.cpp.o"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/SdlCreateWindow.dir/src/main.cpp.o -MF CMakeFiles/SdlCreateWindow.dir/src/main.cpp.o.d -o CMakeFiles/SdlCreateWindow.dir/src/main.cpp.o -c /Users/macos/Desktop/SDL-Assignment/sdl-game-dev/p1-sdl-create-app/src/main.cpp

CMakeFiles/SdlCreateWindow.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/SdlCreateWindow.dir/src/main.cpp.i"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/macos/Desktop/SDL-Assignment/sdl-game-dev/p1-sdl-create-app/src/main.cpp > CMakeFiles/SdlCreateWindow.dir/src/main.cpp.i

CMakeFiles/SdlCreateWindow.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/SdlCreateWindow.dir/src/main.cpp.s"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/macos/Desktop/SDL-Assignment/sdl-game-dev/p1-sdl-create-app/src/main.cpp -o CMakeFiles/SdlCreateWindow.dir/src/main.cpp.s

CMakeFiles/SdlCreateWindow.dir/src/ball.cpp.o: CMakeFiles/SdlCreateWindow.dir/flags.make
CMakeFiles/SdlCreateWindow.dir/src/ball.cpp.o: /Users/macos/Desktop/SDL-Assignment/sdl-game-dev/p1-sdl-create-app/src/ball.cpp
CMakeFiles/SdlCreateWindow.dir/src/ball.cpp.o: CMakeFiles/SdlCreateWindow.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/macos/Desktop/SDL-Assignment/sdl-game-dev/p1-sdl-create-app/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/SdlCreateWindow.dir/src/ball.cpp.o"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/SdlCreateWindow.dir/src/ball.cpp.o -MF CMakeFiles/SdlCreateWindow.dir/src/ball.cpp.o.d -o CMakeFiles/SdlCreateWindow.dir/src/ball.cpp.o -c /Users/macos/Desktop/SDL-Assignment/sdl-game-dev/p1-sdl-create-app/src/ball.cpp

CMakeFiles/SdlCreateWindow.dir/src/ball.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/SdlCreateWindow.dir/src/ball.cpp.i"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/macos/Desktop/SDL-Assignment/sdl-game-dev/p1-sdl-create-app/src/ball.cpp > CMakeFiles/SdlCreateWindow.dir/src/ball.cpp.i

CMakeFiles/SdlCreateWindow.dir/src/ball.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/SdlCreateWindow.dir/src/ball.cpp.s"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/macos/Desktop/SDL-Assignment/sdl-game-dev/p1-sdl-create-app/src/ball.cpp -o CMakeFiles/SdlCreateWindow.dir/src/ball.cpp.s

CMakeFiles/SdlCreateWindow.dir/src/commonFn.cpp.o: CMakeFiles/SdlCreateWindow.dir/flags.make
CMakeFiles/SdlCreateWindow.dir/src/commonFn.cpp.o: /Users/macos/Desktop/SDL-Assignment/sdl-game-dev/p1-sdl-create-app/src/commonFn.cpp
CMakeFiles/SdlCreateWindow.dir/src/commonFn.cpp.o: CMakeFiles/SdlCreateWindow.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/macos/Desktop/SDL-Assignment/sdl-game-dev/p1-sdl-create-app/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/SdlCreateWindow.dir/src/commonFn.cpp.o"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/SdlCreateWindow.dir/src/commonFn.cpp.o -MF CMakeFiles/SdlCreateWindow.dir/src/commonFn.cpp.o.d -o CMakeFiles/SdlCreateWindow.dir/src/commonFn.cpp.o -c /Users/macos/Desktop/SDL-Assignment/sdl-game-dev/p1-sdl-create-app/src/commonFn.cpp

CMakeFiles/SdlCreateWindow.dir/src/commonFn.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/SdlCreateWindow.dir/src/commonFn.cpp.i"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/macos/Desktop/SDL-Assignment/sdl-game-dev/p1-sdl-create-app/src/commonFn.cpp > CMakeFiles/SdlCreateWindow.dir/src/commonFn.cpp.i

CMakeFiles/SdlCreateWindow.dir/src/commonFn.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/SdlCreateWindow.dir/src/commonFn.cpp.s"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/macos/Desktop/SDL-Assignment/sdl-game-dev/p1-sdl-create-app/src/commonFn.cpp -o CMakeFiles/SdlCreateWindow.dir/src/commonFn.cpp.s

CMakeFiles/SdlCreateWindow.dir/src/game.cpp.o: CMakeFiles/SdlCreateWindow.dir/flags.make
CMakeFiles/SdlCreateWindow.dir/src/game.cpp.o: /Users/macos/Desktop/SDL-Assignment/sdl-game-dev/p1-sdl-create-app/src/game.cpp
CMakeFiles/SdlCreateWindow.dir/src/game.cpp.o: CMakeFiles/SdlCreateWindow.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/macos/Desktop/SDL-Assignment/sdl-game-dev/p1-sdl-create-app/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/SdlCreateWindow.dir/src/game.cpp.o"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/SdlCreateWindow.dir/src/game.cpp.o -MF CMakeFiles/SdlCreateWindow.dir/src/game.cpp.o.d -o CMakeFiles/SdlCreateWindow.dir/src/game.cpp.o -c /Users/macos/Desktop/SDL-Assignment/sdl-game-dev/p1-sdl-create-app/src/game.cpp

CMakeFiles/SdlCreateWindow.dir/src/game.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/SdlCreateWindow.dir/src/game.cpp.i"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/macos/Desktop/SDL-Assignment/sdl-game-dev/p1-sdl-create-app/src/game.cpp > CMakeFiles/SdlCreateWindow.dir/src/game.cpp.i

CMakeFiles/SdlCreateWindow.dir/src/game.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/SdlCreateWindow.dir/src/game.cpp.s"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/macos/Desktop/SDL-Assignment/sdl-game-dev/p1-sdl-create-app/src/game.cpp -o CMakeFiles/SdlCreateWindow.dir/src/game.cpp.s

# Object files for target SdlCreateWindow
SdlCreateWindow_OBJECTS = \
"CMakeFiles/SdlCreateWindow.dir/src/main.cpp.o" \
"CMakeFiles/SdlCreateWindow.dir/src/ball.cpp.o" \
"CMakeFiles/SdlCreateWindow.dir/src/commonFn.cpp.o" \
"CMakeFiles/SdlCreateWindow.dir/src/game.cpp.o"

# External object files for target SdlCreateWindow
SdlCreateWindow_EXTERNAL_OBJECTS =

SdlCreateWindow: CMakeFiles/SdlCreateWindow.dir/src/main.cpp.o
SdlCreateWindow: CMakeFiles/SdlCreateWindow.dir/src/ball.cpp.o
SdlCreateWindow: CMakeFiles/SdlCreateWindow.dir/src/commonFn.cpp.o
SdlCreateWindow: CMakeFiles/SdlCreateWindow.dir/src/game.cpp.o
SdlCreateWindow: CMakeFiles/SdlCreateWindow.dir/build.make
SdlCreateWindow: //usr/local/Cellar/sdl2/2.28.3/lib/libSDL2.dylib
SdlCreateWindow: /usr/local/Cellar/sdl2_image/2.6.3_2/lib/libSDL2_image.dylib
SdlCreateWindow: CMakeFiles/SdlCreateWindow.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/Users/macos/Desktop/SDL-Assignment/sdl-game-dev/p1-sdl-create-app/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX executable SdlCreateWindow"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/SdlCreateWindow.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/SdlCreateWindow.dir/build: SdlCreateWindow
.PHONY : CMakeFiles/SdlCreateWindow.dir/build

CMakeFiles/SdlCreateWindow.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/SdlCreateWindow.dir/cmake_clean.cmake
.PHONY : CMakeFiles/SdlCreateWindow.dir/clean

CMakeFiles/SdlCreateWindow.dir/depend:
	cd /Users/macos/Desktop/SDL-Assignment/sdl-game-dev/p1-sdl-create-app/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/macos/Desktop/SDL-Assignment/sdl-game-dev/p1-sdl-create-app /Users/macos/Desktop/SDL-Assignment/sdl-game-dev/p1-sdl-create-app /Users/macos/Desktop/SDL-Assignment/sdl-game-dev/p1-sdl-create-app/build /Users/macos/Desktop/SDL-Assignment/sdl-game-dev/p1-sdl-create-app/build /Users/macos/Desktop/SDL-Assignment/sdl-game-dev/p1-sdl-create-app/build/CMakeFiles/SdlCreateWindow.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/SdlCreateWindow.dir/depend

