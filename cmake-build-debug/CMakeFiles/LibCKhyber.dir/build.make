# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.11

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
CMAKE_SOURCE_DIR = /mnt/c/Users/Khyber/workspace/LibCKhyber

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/c/Users/Khyber/workspace/LibCKhyber/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/LibCKhyber.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/LibCKhyber.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/LibCKhyber.dir/flags.make

CMakeFiles/LibCKhyber.dir/src/main/string/String.c.o: CMakeFiles/LibCKhyber.dir/flags.make
CMakeFiles/LibCKhyber.dir/src/main/string/String.c.o: ../src/main/string/String.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/Khyber/workspace/LibCKhyber/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/LibCKhyber.dir/src/main/string/String.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/LibCKhyber.dir/src/main/string/String.c.o   -c /mnt/c/Users/Khyber/workspace/LibCKhyber/src/main/string/String.c

CMakeFiles/LibCKhyber.dir/src/main/string/String.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/LibCKhyber.dir/src/main/string/String.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /mnt/c/Users/Khyber/workspace/LibCKhyber/src/main/string/String.c > CMakeFiles/LibCKhyber.dir/src/main/string/String.c.i

CMakeFiles/LibCKhyber.dir/src/main/string/String.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/LibCKhyber.dir/src/main/string/String.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /mnt/c/Users/Khyber/workspace/LibCKhyber/src/main/string/String.c -o CMakeFiles/LibCKhyber.dir/src/main/string/String.c.s

CMakeFiles/LibCKhyber.dir/src/main/string/Strings.c.o: CMakeFiles/LibCKhyber.dir/flags.make
CMakeFiles/LibCKhyber.dir/src/main/string/Strings.c.o: ../src/main/string/Strings.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/Khyber/workspace/LibCKhyber/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/LibCKhyber.dir/src/main/string/Strings.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/LibCKhyber.dir/src/main/string/Strings.c.o   -c /mnt/c/Users/Khyber/workspace/LibCKhyber/src/main/string/Strings.c

CMakeFiles/LibCKhyber.dir/src/main/string/Strings.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/LibCKhyber.dir/src/main/string/Strings.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /mnt/c/Users/Khyber/workspace/LibCKhyber/src/main/string/Strings.c > CMakeFiles/LibCKhyber.dir/src/main/string/Strings.c.i

CMakeFiles/LibCKhyber.dir/src/main/string/Strings.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/LibCKhyber.dir/src/main/string/Strings.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /mnt/c/Users/Khyber/workspace/LibCKhyber/src/main/string/Strings.c -o CMakeFiles/LibCKhyber.dir/src/main/string/Strings.c.s

CMakeFiles/LibCKhyber.dir/src/main/util/utils.c.o: CMakeFiles/LibCKhyber.dir/flags.make
CMakeFiles/LibCKhyber.dir/src/main/util/utils.c.o: ../src/main/util/utils.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/Khyber/workspace/LibCKhyber/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/LibCKhyber.dir/src/main/util/utils.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/LibCKhyber.dir/src/main/util/utils.c.o   -c /mnt/c/Users/Khyber/workspace/LibCKhyber/src/main/util/utils.c

CMakeFiles/LibCKhyber.dir/src/main/util/utils.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/LibCKhyber.dir/src/main/util/utils.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /mnt/c/Users/Khyber/workspace/LibCKhyber/src/main/util/utils.c > CMakeFiles/LibCKhyber.dir/src/main/util/utils.c.i

CMakeFiles/LibCKhyber.dir/src/main/util/utils.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/LibCKhyber.dir/src/main/util/utils.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /mnt/c/Users/Khyber/workspace/LibCKhyber/src/main/util/utils.c -o CMakeFiles/LibCKhyber.dir/src/main/util/utils.c.s

CMakeFiles/LibCKhyber.dir/src/main/util/signal/sigAction.c.o: CMakeFiles/LibCKhyber.dir/flags.make
CMakeFiles/LibCKhyber.dir/src/main/util/signal/sigAction.c.o: ../src/main/util/signal/sigAction.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/Khyber/workspace/LibCKhyber/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/LibCKhyber.dir/src/main/util/signal/sigAction.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/LibCKhyber.dir/src/main/util/signal/sigAction.c.o   -c /mnt/c/Users/Khyber/workspace/LibCKhyber/src/main/util/signal/sigAction.c

CMakeFiles/LibCKhyber.dir/src/main/util/signal/sigAction.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/LibCKhyber.dir/src/main/util/signal/sigAction.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /mnt/c/Users/Khyber/workspace/LibCKhyber/src/main/util/signal/sigAction.c > CMakeFiles/LibCKhyber.dir/src/main/util/signal/sigAction.c.i

CMakeFiles/LibCKhyber.dir/src/main/util/signal/sigAction.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/LibCKhyber.dir/src/main/util/signal/sigAction.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /mnt/c/Users/Khyber/workspace/LibCKhyber/src/main/util/signal/sigAction.c -o CMakeFiles/LibCKhyber.dir/src/main/util/signal/sigAction.c.s

CMakeFiles/LibCKhyber.dir/src/main/util/buffer/buffer.c.o: CMakeFiles/LibCKhyber.dir/flags.make
CMakeFiles/LibCKhyber.dir/src/main/util/buffer/buffer.c.o: ../src/main/util/buffer/buffer.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/Khyber/workspace/LibCKhyber/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object CMakeFiles/LibCKhyber.dir/src/main/util/buffer/buffer.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/LibCKhyber.dir/src/main/util/buffer/buffer.c.o   -c /mnt/c/Users/Khyber/workspace/LibCKhyber/src/main/util/buffer/buffer.c

CMakeFiles/LibCKhyber.dir/src/main/util/buffer/buffer.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/LibCKhyber.dir/src/main/util/buffer/buffer.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /mnt/c/Users/Khyber/workspace/LibCKhyber/src/main/util/buffer/buffer.c > CMakeFiles/LibCKhyber.dir/src/main/util/buffer/buffer.c.i

CMakeFiles/LibCKhyber.dir/src/main/util/buffer/buffer.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/LibCKhyber.dir/src/main/util/buffer/buffer.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /mnt/c/Users/Khyber/workspace/LibCKhyber/src/main/util/buffer/buffer.c -o CMakeFiles/LibCKhyber.dir/src/main/util/buffer/buffer.c.s

CMakeFiles/LibCKhyber.dir/src/main/util/signal/Signal.c.o: CMakeFiles/LibCKhyber.dir/flags.make
CMakeFiles/LibCKhyber.dir/src/main/util/signal/Signal.c.o: ../src/main/util/signal/Signal.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/Khyber/workspace/LibCKhyber/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building C object CMakeFiles/LibCKhyber.dir/src/main/util/signal/Signal.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/LibCKhyber.dir/src/main/util/signal/Signal.c.o   -c /mnt/c/Users/Khyber/workspace/LibCKhyber/src/main/util/signal/Signal.c

CMakeFiles/LibCKhyber.dir/src/main/util/signal/Signal.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/LibCKhyber.dir/src/main/util/signal/Signal.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /mnt/c/Users/Khyber/workspace/LibCKhyber/src/main/util/signal/Signal.c > CMakeFiles/LibCKhyber.dir/src/main/util/signal/Signal.c.i

CMakeFiles/LibCKhyber.dir/src/main/util/signal/Signal.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/LibCKhyber.dir/src/main/util/signal/Signal.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /mnt/c/Users/Khyber/workspace/LibCKhyber/src/main/util/signal/Signal.c -o CMakeFiles/LibCKhyber.dir/src/main/util/signal/Signal.c.s

CMakeFiles/LibCKhyber.dir/src/main/util/programName/programName.c.o: CMakeFiles/LibCKhyber.dir/flags.make
CMakeFiles/LibCKhyber.dir/src/main/util/programName/programName.c.o: ../src/main/util/programName/programName.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/Khyber/workspace/LibCKhyber/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building C object CMakeFiles/LibCKhyber.dir/src/main/util/programName/programName.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/LibCKhyber.dir/src/main/util/programName/programName.c.o   -c /mnt/c/Users/Khyber/workspace/LibCKhyber/src/main/util/programName/programName.c

CMakeFiles/LibCKhyber.dir/src/main/util/programName/programName.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/LibCKhyber.dir/src/main/util/programName/programName.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /mnt/c/Users/Khyber/workspace/LibCKhyber/src/main/util/programName/programName.c > CMakeFiles/LibCKhyber.dir/src/main/util/programName/programName.c.i

CMakeFiles/LibCKhyber.dir/src/main/util/programName/programName.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/LibCKhyber.dir/src/main/util/programName/programName.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /mnt/c/Users/Khyber/workspace/LibCKhyber/src/main/util/programName/programName.c -o CMakeFiles/LibCKhyber.dir/src/main/util/programName/programName.c.s

CMakeFiles/LibCKhyber.dir/src/main/util/hash/fnv1a.c.o: CMakeFiles/LibCKhyber.dir/flags.make
CMakeFiles/LibCKhyber.dir/src/main/util/hash/fnv1a.c.o: ../src/main/util/hash/fnv1a.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/Khyber/workspace/LibCKhyber/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building C object CMakeFiles/LibCKhyber.dir/src/main/util/hash/fnv1a.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/LibCKhyber.dir/src/main/util/hash/fnv1a.c.o   -c /mnt/c/Users/Khyber/workspace/LibCKhyber/src/main/util/hash/fnv1a.c

CMakeFiles/LibCKhyber.dir/src/main/util/hash/fnv1a.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/LibCKhyber.dir/src/main/util/hash/fnv1a.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /mnt/c/Users/Khyber/workspace/LibCKhyber/src/main/util/hash/fnv1a.c > CMakeFiles/LibCKhyber.dir/src/main/util/hash/fnv1a.c.i

CMakeFiles/LibCKhyber.dir/src/main/util/hash/fnv1a.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/LibCKhyber.dir/src/main/util/hash/fnv1a.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /mnt/c/Users/Khyber/workspace/LibCKhyber/src/main/util/hash/fnv1a.c -o CMakeFiles/LibCKhyber.dir/src/main/util/hash/fnv1a.c.s

CMakeFiles/LibCKhyber.dir/src/main/collections/HashMap/HashMap_String_Addr2Line.c.o: CMakeFiles/LibCKhyber.dir/flags.make
CMakeFiles/LibCKhyber.dir/src/main/collections/HashMap/HashMap_String_Addr2Line.c.o: ../src/main/collections/HashMap/HashMap_String_Addr2Line.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/Khyber/workspace/LibCKhyber/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building C object CMakeFiles/LibCKhyber.dir/src/main/collections/HashMap/HashMap_String_Addr2Line.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/LibCKhyber.dir/src/main/collections/HashMap/HashMap_String_Addr2Line.c.o   -c /mnt/c/Users/Khyber/workspace/LibCKhyber/src/main/collections/HashMap/HashMap_String_Addr2Line.c

CMakeFiles/LibCKhyber.dir/src/main/collections/HashMap/HashMap_String_Addr2Line.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/LibCKhyber.dir/src/main/collections/HashMap/HashMap_String_Addr2Line.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /mnt/c/Users/Khyber/workspace/LibCKhyber/src/main/collections/HashMap/HashMap_String_Addr2Line.c > CMakeFiles/LibCKhyber.dir/src/main/collections/HashMap/HashMap_String_Addr2Line.c.i

CMakeFiles/LibCKhyber.dir/src/main/collections/HashMap/HashMap_String_Addr2Line.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/LibCKhyber.dir/src/main/collections/HashMap/HashMap_String_Addr2Line.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /mnt/c/Users/Khyber/workspace/LibCKhyber/src/main/collections/HashMap/HashMap_String_Addr2Line.c -o CMakeFiles/LibCKhyber.dir/src/main/collections/HashMap/HashMap_String_Addr2Line.c.s

CMakeFiles/LibCKhyber.dir/src/main/stackTrace/bfd/BinaryFileDescriptor.c.o: CMakeFiles/LibCKhyber.dir/flags.make
CMakeFiles/LibCKhyber.dir/src/main/stackTrace/bfd/BinaryFileDescriptor.c.o: ../src/main/stackTrace/bfd/BinaryFileDescriptor.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/Khyber/workspace/LibCKhyber/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building C object CMakeFiles/LibCKhyber.dir/src/main/stackTrace/bfd/BinaryFileDescriptor.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/LibCKhyber.dir/src/main/stackTrace/bfd/BinaryFileDescriptor.c.o   -c /mnt/c/Users/Khyber/workspace/LibCKhyber/src/main/stackTrace/bfd/BinaryFileDescriptor.c

CMakeFiles/LibCKhyber.dir/src/main/stackTrace/bfd/BinaryFileDescriptor.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/LibCKhyber.dir/src/main/stackTrace/bfd/BinaryFileDescriptor.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /mnt/c/Users/Khyber/workspace/LibCKhyber/src/main/stackTrace/bfd/BinaryFileDescriptor.c > CMakeFiles/LibCKhyber.dir/src/main/stackTrace/bfd/BinaryFileDescriptor.c.i

CMakeFiles/LibCKhyber.dir/src/main/stackTrace/bfd/BinaryFileDescriptor.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/LibCKhyber.dir/src/main/stackTrace/bfd/BinaryFileDescriptor.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /mnt/c/Users/Khyber/workspace/LibCKhyber/src/main/stackTrace/bfd/BinaryFileDescriptor.c -o CMakeFiles/LibCKhyber.dir/src/main/stackTrace/bfd/BinaryFileDescriptor.c.s

CMakeFiles/LibCKhyber.dir/src/main/stackTrace/stackTrace/StackTrace.c.o: CMakeFiles/LibCKhyber.dir/flags.make
CMakeFiles/LibCKhyber.dir/src/main/stackTrace/stackTrace/StackTrace.c.o: ../src/main/stackTrace/stackTrace/StackTrace.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/Khyber/workspace/LibCKhyber/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building C object CMakeFiles/LibCKhyber.dir/src/main/stackTrace/stackTrace/StackTrace.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/LibCKhyber.dir/src/main/stackTrace/stackTrace/StackTrace.c.o   -c /mnt/c/Users/Khyber/workspace/LibCKhyber/src/main/stackTrace/stackTrace/StackTrace.c

CMakeFiles/LibCKhyber.dir/src/main/stackTrace/stackTrace/StackTrace.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/LibCKhyber.dir/src/main/stackTrace/stackTrace/StackTrace.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /mnt/c/Users/Khyber/workspace/LibCKhyber/src/main/stackTrace/stackTrace/StackTrace.c > CMakeFiles/LibCKhyber.dir/src/main/stackTrace/stackTrace/StackTrace.c.i

CMakeFiles/LibCKhyber.dir/src/main/stackTrace/stackTrace/StackTrace.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/LibCKhyber.dir/src/main/stackTrace/stackTrace/StackTrace.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /mnt/c/Users/Khyber/workspace/LibCKhyber/src/main/stackTrace/stackTrace/StackTrace.c -o CMakeFiles/LibCKhyber.dir/src/main/stackTrace/stackTrace/StackTrace.c.s

CMakeFiles/LibCKhyber.dir/src/main/stackTrace/stackTrace/StackFrame.c.o: CMakeFiles/LibCKhyber.dir/flags.make
CMakeFiles/LibCKhyber.dir/src/main/stackTrace/stackTrace/StackFrame.c.o: ../src/main/stackTrace/stackTrace/StackFrame.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/Khyber/workspace/LibCKhyber/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Building C object CMakeFiles/LibCKhyber.dir/src/main/stackTrace/stackTrace/StackFrame.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/LibCKhyber.dir/src/main/stackTrace/stackTrace/StackFrame.c.o   -c /mnt/c/Users/Khyber/workspace/LibCKhyber/src/main/stackTrace/stackTrace/StackFrame.c

CMakeFiles/LibCKhyber.dir/src/main/stackTrace/stackTrace/StackFrame.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/LibCKhyber.dir/src/main/stackTrace/stackTrace/StackFrame.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /mnt/c/Users/Khyber/workspace/LibCKhyber/src/main/stackTrace/stackTrace/StackFrame.c > CMakeFiles/LibCKhyber.dir/src/main/stackTrace/stackTrace/StackFrame.c.i

CMakeFiles/LibCKhyber.dir/src/main/stackTrace/stackTrace/StackFrame.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/LibCKhyber.dir/src/main/stackTrace/stackTrace/StackFrame.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /mnt/c/Users/Khyber/workspace/LibCKhyber/src/main/stackTrace/stackTrace/StackFrame.c -o CMakeFiles/LibCKhyber.dir/src/main/stackTrace/stackTrace/StackFrame.c.s

CMakeFiles/LibCKhyber.dir/src/main/stackTrace/stackTraceSignalHandler/StackTraceSignalHandler.c.o: CMakeFiles/LibCKhyber.dir/flags.make
CMakeFiles/LibCKhyber.dir/src/main/stackTrace/stackTraceSignalHandler/StackTraceSignalHandler.c.o: ../src/main/stackTrace/stackTraceSignalHandler/StackTraceSignalHandler.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/Khyber/workspace/LibCKhyber/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_13) "Building C object CMakeFiles/LibCKhyber.dir/src/main/stackTrace/stackTraceSignalHandler/StackTraceSignalHandler.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/LibCKhyber.dir/src/main/stackTrace/stackTraceSignalHandler/StackTraceSignalHandler.c.o   -c /mnt/c/Users/Khyber/workspace/LibCKhyber/src/main/stackTrace/stackTraceSignalHandler/StackTraceSignalHandler.c

CMakeFiles/LibCKhyber.dir/src/main/stackTrace/stackTraceSignalHandler/StackTraceSignalHandler.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/LibCKhyber.dir/src/main/stackTrace/stackTraceSignalHandler/StackTraceSignalHandler.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /mnt/c/Users/Khyber/workspace/LibCKhyber/src/main/stackTrace/stackTraceSignalHandler/StackTraceSignalHandler.c > CMakeFiles/LibCKhyber.dir/src/main/stackTrace/stackTraceSignalHandler/StackTraceSignalHandler.c.i

CMakeFiles/LibCKhyber.dir/src/main/stackTrace/stackTraceSignalHandler/StackTraceSignalHandler.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/LibCKhyber.dir/src/main/stackTrace/stackTraceSignalHandler/StackTraceSignalHandler.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /mnt/c/Users/Khyber/workspace/LibCKhyber/src/main/stackTrace/stackTraceSignalHandler/StackTraceSignalHandler.c -o CMakeFiles/LibCKhyber.dir/src/main/stackTrace/stackTraceSignalHandler/StackTraceSignalHandler.c.s

CMakeFiles/LibCKhyber.dir/src/main/stackTrace/addr2Line/Addr2Line.c.o: CMakeFiles/LibCKhyber.dir/flags.make
CMakeFiles/LibCKhyber.dir/src/main/stackTrace/addr2Line/Addr2Line.c.o: ../src/main/stackTrace/addr2Line/Addr2Line.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/Khyber/workspace/LibCKhyber/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_14) "Building C object CMakeFiles/LibCKhyber.dir/src/main/stackTrace/addr2Line/Addr2Line.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/LibCKhyber.dir/src/main/stackTrace/addr2Line/Addr2Line.c.o   -c /mnt/c/Users/Khyber/workspace/LibCKhyber/src/main/stackTrace/addr2Line/Addr2Line.c

CMakeFiles/LibCKhyber.dir/src/main/stackTrace/addr2Line/Addr2Line.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/LibCKhyber.dir/src/main/stackTrace/addr2Line/Addr2Line.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /mnt/c/Users/Khyber/workspace/LibCKhyber/src/main/stackTrace/addr2Line/Addr2Line.c > CMakeFiles/LibCKhyber.dir/src/main/stackTrace/addr2Line/Addr2Line.c.i

CMakeFiles/LibCKhyber.dir/src/main/stackTrace/addr2Line/Addr2Line.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/LibCKhyber.dir/src/main/stackTrace/addr2Line/Addr2Line.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /mnt/c/Users/Khyber/workspace/LibCKhyber/src/main/stackTrace/addr2Line/Addr2Line.c -o CMakeFiles/LibCKhyber.dir/src/main/stackTrace/addr2Line/Addr2Line.c.s

CMakeFiles/LibCKhyber.dir/src/main/math/Vector.c.o: CMakeFiles/LibCKhyber.dir/flags.make
CMakeFiles/LibCKhyber.dir/src/main/math/Vector.c.o: ../src/main/math/Vector.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/Khyber/workspace/LibCKhyber/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_15) "Building C object CMakeFiles/LibCKhyber.dir/src/main/math/Vector.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/LibCKhyber.dir/src/main/math/Vector.c.o   -c /mnt/c/Users/Khyber/workspace/LibCKhyber/src/main/math/Vector.c

CMakeFiles/LibCKhyber.dir/src/main/math/Vector.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/LibCKhyber.dir/src/main/math/Vector.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /mnt/c/Users/Khyber/workspace/LibCKhyber/src/main/math/Vector.c > CMakeFiles/LibCKhyber.dir/src/main/math/Vector.c.i

CMakeFiles/LibCKhyber.dir/src/main/math/Vector.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/LibCKhyber.dir/src/main/math/Vector.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /mnt/c/Users/Khyber/workspace/LibCKhyber/src/main/math/Vector.c -o CMakeFiles/LibCKhyber.dir/src/main/math/Vector.c.s

CMakeFiles/LibCKhyber.dir/src/test/testStackTrace.c.o: CMakeFiles/LibCKhyber.dir/flags.make
CMakeFiles/LibCKhyber.dir/src/test/testStackTrace.c.o: ../src/test/testStackTrace.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/Khyber/workspace/LibCKhyber/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_16) "Building C object CMakeFiles/LibCKhyber.dir/src/test/testStackTrace.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/LibCKhyber.dir/src/test/testStackTrace.c.o   -c /mnt/c/Users/Khyber/workspace/LibCKhyber/src/test/testStackTrace.c

CMakeFiles/LibCKhyber.dir/src/test/testStackTrace.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/LibCKhyber.dir/src/test/testStackTrace.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /mnt/c/Users/Khyber/workspace/LibCKhyber/src/test/testStackTrace.c > CMakeFiles/LibCKhyber.dir/src/test/testStackTrace.c.i

CMakeFiles/LibCKhyber.dir/src/test/testStackTrace.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/LibCKhyber.dir/src/test/testStackTrace.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /mnt/c/Users/Khyber/workspace/LibCKhyber/src/test/testStackTrace.c -o CMakeFiles/LibCKhyber.dir/src/test/testStackTrace.c.s

CMakeFiles/LibCKhyber.dir/src/test/testStringFormat.c.o: CMakeFiles/LibCKhyber.dir/flags.make
CMakeFiles/LibCKhyber.dir/src/test/testStringFormat.c.o: ../src/test/testStringFormat.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/Khyber/workspace/LibCKhyber/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_17) "Building C object CMakeFiles/LibCKhyber.dir/src/test/testStringFormat.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/LibCKhyber.dir/src/test/testStringFormat.c.o   -c /mnt/c/Users/Khyber/workspace/LibCKhyber/src/test/testStringFormat.c

CMakeFiles/LibCKhyber.dir/src/test/testStringFormat.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/LibCKhyber.dir/src/test/testStringFormat.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /mnt/c/Users/Khyber/workspace/LibCKhyber/src/test/testStringFormat.c > CMakeFiles/LibCKhyber.dir/src/test/testStringFormat.c.i

CMakeFiles/LibCKhyber.dir/src/test/testStringFormat.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/LibCKhyber.dir/src/test/testStringFormat.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /mnt/c/Users/Khyber/workspace/LibCKhyber/src/test/testStringFormat.c -o CMakeFiles/LibCKhyber.dir/src/test/testStringFormat.c.s

CMakeFiles/LibCKhyber.dir/src/test/test.c.o: CMakeFiles/LibCKhyber.dir/flags.make
CMakeFiles/LibCKhyber.dir/src/test/test.c.o: ../src/test/test.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/Khyber/workspace/LibCKhyber/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_18) "Building C object CMakeFiles/LibCKhyber.dir/src/test/test.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/LibCKhyber.dir/src/test/test.c.o   -c /mnt/c/Users/Khyber/workspace/LibCKhyber/src/test/test.c

CMakeFiles/LibCKhyber.dir/src/test/test.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/LibCKhyber.dir/src/test/test.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /mnt/c/Users/Khyber/workspace/LibCKhyber/src/test/test.c > CMakeFiles/LibCKhyber.dir/src/test/test.c.i

CMakeFiles/LibCKhyber.dir/src/test/test.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/LibCKhyber.dir/src/test/test.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /mnt/c/Users/Khyber/workspace/LibCKhyber/src/test/test.c -o CMakeFiles/LibCKhyber.dir/src/test/test.c.s

# Object files for target LibCKhyber
LibCKhyber_OBJECTS = \
"CMakeFiles/LibCKhyber.dir/src/main/string/String.c.o" \
"CMakeFiles/LibCKhyber.dir/src/main/string/Strings.c.o" \
"CMakeFiles/LibCKhyber.dir/src/main/util/utils.c.o" \
"CMakeFiles/LibCKhyber.dir/src/main/util/signal/sigAction.c.o" \
"CMakeFiles/LibCKhyber.dir/src/main/util/buffer/buffer.c.o" \
"CMakeFiles/LibCKhyber.dir/src/main/util/signal/Signal.c.o" \
"CMakeFiles/LibCKhyber.dir/src/main/util/programName/programName.c.o" \
"CMakeFiles/LibCKhyber.dir/src/main/util/hash/fnv1a.c.o" \
"CMakeFiles/LibCKhyber.dir/src/main/collections/HashMap/HashMap_String_Addr2Line.c.o" \
"CMakeFiles/LibCKhyber.dir/src/main/stackTrace/bfd/BinaryFileDescriptor.c.o" \
"CMakeFiles/LibCKhyber.dir/src/main/stackTrace/stackTrace/StackTrace.c.o" \
"CMakeFiles/LibCKhyber.dir/src/main/stackTrace/stackTrace/StackFrame.c.o" \
"CMakeFiles/LibCKhyber.dir/src/main/stackTrace/stackTraceSignalHandler/StackTraceSignalHandler.c.o" \
"CMakeFiles/LibCKhyber.dir/src/main/stackTrace/addr2Line/Addr2Line.c.o" \
"CMakeFiles/LibCKhyber.dir/src/main/math/Vector.c.o" \
"CMakeFiles/LibCKhyber.dir/src/test/testStackTrace.c.o" \
"CMakeFiles/LibCKhyber.dir/src/test/testStringFormat.c.o" \
"CMakeFiles/LibCKhyber.dir/src/test/test.c.o"

# External object files for target LibCKhyber
LibCKhyber_EXTERNAL_OBJECTS =

LibCKhyber: CMakeFiles/LibCKhyber.dir/src/main/string/String.c.o
LibCKhyber: CMakeFiles/LibCKhyber.dir/src/main/string/Strings.c.o
LibCKhyber: CMakeFiles/LibCKhyber.dir/src/main/util/utils.c.o
LibCKhyber: CMakeFiles/LibCKhyber.dir/src/main/util/signal/sigAction.c.o
LibCKhyber: CMakeFiles/LibCKhyber.dir/src/main/util/buffer/buffer.c.o
LibCKhyber: CMakeFiles/LibCKhyber.dir/src/main/util/signal/Signal.c.o
LibCKhyber: CMakeFiles/LibCKhyber.dir/src/main/util/programName/programName.c.o
LibCKhyber: CMakeFiles/LibCKhyber.dir/src/main/util/hash/fnv1a.c.o
LibCKhyber: CMakeFiles/LibCKhyber.dir/src/main/collections/HashMap/HashMap_String_Addr2Line.c.o
LibCKhyber: CMakeFiles/LibCKhyber.dir/src/main/stackTrace/bfd/BinaryFileDescriptor.c.o
LibCKhyber: CMakeFiles/LibCKhyber.dir/src/main/stackTrace/stackTrace/StackTrace.c.o
LibCKhyber: CMakeFiles/LibCKhyber.dir/src/main/stackTrace/stackTrace/StackFrame.c.o
LibCKhyber: CMakeFiles/LibCKhyber.dir/src/main/stackTrace/stackTraceSignalHandler/StackTraceSignalHandler.c.o
LibCKhyber: CMakeFiles/LibCKhyber.dir/src/main/stackTrace/addr2Line/Addr2Line.c.o
LibCKhyber: CMakeFiles/LibCKhyber.dir/src/main/math/Vector.c.o
LibCKhyber: CMakeFiles/LibCKhyber.dir/src/test/testStackTrace.c.o
LibCKhyber: CMakeFiles/LibCKhyber.dir/src/test/testStringFormat.c.o
LibCKhyber: CMakeFiles/LibCKhyber.dir/src/test/test.c.o
LibCKhyber: CMakeFiles/LibCKhyber.dir/build.make
LibCKhyber: CMakeFiles/LibCKhyber.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/c/Users/Khyber/workspace/LibCKhyber/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_19) "Linking C executable LibCKhyber"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/LibCKhyber.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/LibCKhyber.dir/build: LibCKhyber

.PHONY : CMakeFiles/LibCKhyber.dir/build

CMakeFiles/LibCKhyber.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/LibCKhyber.dir/cmake_clean.cmake
.PHONY : CMakeFiles/LibCKhyber.dir/clean

CMakeFiles/LibCKhyber.dir/depend:
	cd /mnt/c/Users/Khyber/workspace/LibCKhyber/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/c/Users/Khyber/workspace/LibCKhyber /mnt/c/Users/Khyber/workspace/LibCKhyber /mnt/c/Users/Khyber/workspace/LibCKhyber/cmake-build-debug /mnt/c/Users/Khyber/workspace/LibCKhyber/cmake-build-debug /mnt/c/Users/Khyber/workspace/LibCKhyber/cmake-build-debug/CMakeFiles/LibCKhyber.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/LibCKhyber.dir/depend

