# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.17

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

# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = C:\temp\clion\bin\cmake\win\bin\cmake.exe

# The command to remove a file.
RM = C:\temp\clion\bin\cmake\win\bin\cmake.exe -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\dev\C\ctracer

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\dev\C\ctracer\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/main.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/main.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/main.dir/flags.make

CMakeFiles/main.dir/src/camera.c.obj: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/src/camera.c.obj: ../src/camera.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\dev\C\ctracer\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/main.dir/src/camera.c.obj"
	C:\dev\compilers\mingw-w64\x86_64-8.1.0-posix-seh-rt_v6-rev0\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\main.dir\src\camera.c.obj   -c C:\dev\C\ctracer\src\camera.c

CMakeFiles/main.dir/src/camera.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/main.dir/src/camera.c.i"
	C:\dev\compilers\mingw-w64\x86_64-8.1.0-posix-seh-rt_v6-rev0\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\dev\C\ctracer\src\camera.c > CMakeFiles\main.dir\src\camera.c.i

CMakeFiles/main.dir/src/camera.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/main.dir/src/camera.c.s"
	C:\dev\compilers\mingw-w64\x86_64-8.1.0-posix-seh-rt_v6-rev0\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\dev\C\ctracer\src\camera.c -o CMakeFiles\main.dir\src\camera.c.s

CMakeFiles/main.dir/src/common.c.obj: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/src/common.c.obj: ../src/common.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\dev\C\ctracer\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/main.dir/src/common.c.obj"
	C:\dev\compilers\mingw-w64\x86_64-8.1.0-posix-seh-rt_v6-rev0\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\main.dir\src\common.c.obj   -c C:\dev\C\ctracer\src\common.c

CMakeFiles/main.dir/src/common.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/main.dir/src/common.c.i"
	C:\dev\compilers\mingw-w64\x86_64-8.1.0-posix-seh-rt_v6-rev0\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\dev\C\ctracer\src\common.c > CMakeFiles\main.dir\src\common.c.i

CMakeFiles/main.dir/src/common.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/main.dir/src/common.c.s"
	C:\dev\compilers\mingw-w64\x86_64-8.1.0-posix-seh-rt_v6-rev0\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\dev\C\ctracer\src\common.c -o CMakeFiles\main.dir\src\common.c.s

CMakeFiles/main.dir/src/hitable_list.c.obj: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/src/hitable_list.c.obj: ../src/hitable_list.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\dev\C\ctracer\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/main.dir/src/hitable_list.c.obj"
	C:\dev\compilers\mingw-w64\x86_64-8.1.0-posix-seh-rt_v6-rev0\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\main.dir\src\hitable_list.c.obj   -c C:\dev\C\ctracer\src\hitable_list.c

CMakeFiles/main.dir/src/hitable_list.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/main.dir/src/hitable_list.c.i"
	C:\dev\compilers\mingw-w64\x86_64-8.1.0-posix-seh-rt_v6-rev0\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\dev\C\ctracer\src\hitable_list.c > CMakeFiles\main.dir\src\hitable_list.c.i

CMakeFiles/main.dir/src/hitable_list.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/main.dir/src/hitable_list.c.s"
	C:\dev\compilers\mingw-w64\x86_64-8.1.0-posix-seh-rt_v6-rev0\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\dev\C\ctracer\src\hitable_list.c -o CMakeFiles\main.dir\src\hitable_list.c.s

CMakeFiles/main.dir/src/main.c.obj: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/src/main.c.obj: ../src/main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\dev\C\ctracer\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/main.dir/src/main.c.obj"
	C:\dev\compilers\mingw-w64\x86_64-8.1.0-posix-seh-rt_v6-rev0\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\main.dir\src\main.c.obj   -c C:\dev\C\ctracer\src\main.c

CMakeFiles/main.dir/src/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/main.dir/src/main.c.i"
	C:\dev\compilers\mingw-w64\x86_64-8.1.0-posix-seh-rt_v6-rev0\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\dev\C\ctracer\src\main.c > CMakeFiles\main.dir\src\main.c.i

CMakeFiles/main.dir/src/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/main.dir/src/main.c.s"
	C:\dev\compilers\mingw-w64\x86_64-8.1.0-posix-seh-rt_v6-rev0\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\dev\C\ctracer\src\main.c -o CMakeFiles\main.dir\src\main.c.s

CMakeFiles/main.dir/src/material.c.obj: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/src/material.c.obj: ../src/material.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\dev\C\ctracer\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object CMakeFiles/main.dir/src/material.c.obj"
	C:\dev\compilers\mingw-w64\x86_64-8.1.0-posix-seh-rt_v6-rev0\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\main.dir\src\material.c.obj   -c C:\dev\C\ctracer\src\material.c

CMakeFiles/main.dir/src/material.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/main.dir/src/material.c.i"
	C:\dev\compilers\mingw-w64\x86_64-8.1.0-posix-seh-rt_v6-rev0\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\dev\C\ctracer\src\material.c > CMakeFiles\main.dir\src\material.c.i

CMakeFiles/main.dir/src/material.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/main.dir/src/material.c.s"
	C:\dev\compilers\mingw-w64\x86_64-8.1.0-posix-seh-rt_v6-rev0\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\dev\C\ctracer\src\material.c -o CMakeFiles\main.dir\src\material.c.s

CMakeFiles/main.dir/src/ray.c.obj: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/src/ray.c.obj: ../src/ray.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\dev\C\ctracer\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building C object CMakeFiles/main.dir/src/ray.c.obj"
	C:\dev\compilers\mingw-w64\x86_64-8.1.0-posix-seh-rt_v6-rev0\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\main.dir\src\ray.c.obj   -c C:\dev\C\ctracer\src\ray.c

CMakeFiles/main.dir/src/ray.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/main.dir/src/ray.c.i"
	C:\dev\compilers\mingw-w64\x86_64-8.1.0-posix-seh-rt_v6-rev0\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\dev\C\ctracer\src\ray.c > CMakeFiles\main.dir\src\ray.c.i

CMakeFiles/main.dir/src/ray.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/main.dir/src/ray.c.s"
	C:\dev\compilers\mingw-w64\x86_64-8.1.0-posix-seh-rt_v6-rev0\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\dev\C\ctracer\src\ray.c -o CMakeFiles\main.dir\src\ray.c.s

CMakeFiles/main.dir/src/sphere.c.obj: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/src/sphere.c.obj: ../src/sphere.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\dev\C\ctracer\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building C object CMakeFiles/main.dir/src/sphere.c.obj"
	C:\dev\compilers\mingw-w64\x86_64-8.1.0-posix-seh-rt_v6-rev0\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\main.dir\src\sphere.c.obj   -c C:\dev\C\ctracer\src\sphere.c

CMakeFiles/main.dir/src/sphere.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/main.dir/src/sphere.c.i"
	C:\dev\compilers\mingw-w64\x86_64-8.1.0-posix-seh-rt_v6-rev0\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\dev\C\ctracer\src\sphere.c > CMakeFiles\main.dir\src\sphere.c.i

CMakeFiles/main.dir/src/sphere.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/main.dir/src/sphere.c.s"
	C:\dev\compilers\mingw-w64\x86_64-8.1.0-posix-seh-rt_v6-rev0\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\dev\C\ctracer\src\sphere.c -o CMakeFiles\main.dir\src\sphere.c.s

CMakeFiles/main.dir/src/vec3.c.obj: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/src/vec3.c.obj: ../src/vec3.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\dev\C\ctracer\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building C object CMakeFiles/main.dir/src/vec3.c.obj"
	C:\dev\compilers\mingw-w64\x86_64-8.1.0-posix-seh-rt_v6-rev0\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\main.dir\src\vec3.c.obj   -c C:\dev\C\ctracer\src\vec3.c

CMakeFiles/main.dir/src/vec3.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/main.dir/src/vec3.c.i"
	C:\dev\compilers\mingw-w64\x86_64-8.1.0-posix-seh-rt_v6-rev0\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\dev\C\ctracer\src\vec3.c > CMakeFiles\main.dir\src\vec3.c.i

CMakeFiles/main.dir/src/vec3.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/main.dir/src/vec3.c.s"
	C:\dev\compilers\mingw-w64\x86_64-8.1.0-posix-seh-rt_v6-rev0\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\dev\C\ctracer\src\vec3.c -o CMakeFiles\main.dir\src\vec3.c.s

# Object files for target main
main_OBJECTS = \
"CMakeFiles/main.dir/src/camera.c.obj" \
"CMakeFiles/main.dir/src/common.c.obj" \
"CMakeFiles/main.dir/src/hitable_list.c.obj" \
"CMakeFiles/main.dir/src/main.c.obj" \
"CMakeFiles/main.dir/src/material.c.obj" \
"CMakeFiles/main.dir/src/ray.c.obj" \
"CMakeFiles/main.dir/src/sphere.c.obj" \
"CMakeFiles/main.dir/src/vec3.c.obj"

# External object files for target main
main_EXTERNAL_OBJECTS =

../main.exe: CMakeFiles/main.dir/src/camera.c.obj
../main.exe: CMakeFiles/main.dir/src/common.c.obj
../main.exe: CMakeFiles/main.dir/src/hitable_list.c.obj
../main.exe: CMakeFiles/main.dir/src/main.c.obj
../main.exe: CMakeFiles/main.dir/src/material.c.obj
../main.exe: CMakeFiles/main.dir/src/ray.c.obj
../main.exe: CMakeFiles/main.dir/src/sphere.c.obj
../main.exe: CMakeFiles/main.dir/src/vec3.c.obj
../main.exe: CMakeFiles/main.dir/build.make
../main.exe: CMakeFiles/main.dir/linklibs.rsp
../main.exe: CMakeFiles/main.dir/objects1.rsp
../main.exe: CMakeFiles/main.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\dev\C\ctracer\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Linking C executable ..\main.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\main.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/main.dir/build: ../main.exe

.PHONY : CMakeFiles/main.dir/build

CMakeFiles/main.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\main.dir\cmake_clean.cmake
.PHONY : CMakeFiles/main.dir/clean

CMakeFiles/main.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\dev\C\ctracer C:\dev\C\ctracer C:\dev\C\ctracer\cmake-build-debug C:\dev\C\ctracer\cmake-build-debug C:\dev\C\ctracer\cmake-build-debug\CMakeFiles\main.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/main.dir/depend

