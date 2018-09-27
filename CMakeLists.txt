cmake_minimum_required(VERSION 3.9)
project(LibCKhyber C)

set(CMAKE_C_STANDARD 11)

set(CMAKE_C_ERROR_FLAGS "-Wall -Werror -Wextra -O3")
set(CMAKE_C_NO_ERROR_FLAGS "-Wno-error=unused-function -Wno-error=unused-parameter")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${CMAKE_C_ERROR_FLAGS} ${CMAKE_C_NO_ERROR_FLAGS}")

set(SOURCE_FILES
#        src/error/stackTrace.h
#        src/error/stackTrace.c
        src2/string/String.h
        src2/string/String.c
        src2/util/utils.h
        src2/util/utils.c
#        src/error/addr2Line/addr2line.c
#        src/error/addr2Line/sysdep.h
#        src/error/addr2Line/bucomm.h
#        src/error/addr2Line/bucomm.c
#        src/error/addr2Line.c
#        src/error/addr2Line.h
        src2/signal/sigAction.c
        src2/signal/sigAction.h
        src2/bfd/BinaryFileDescriptor.c
        src2/bfd/BinaryFileDescriptor.h
#        src/error/stackTraceAddr2Line.c
#        src/error/stackTraceAddr2Line.h
        src2/util/setField.h
        src2/buffer/buffer.h
        src2/buffer/buffer.c
        src2/string/Strings.c
        src2/string/Strings.h
        src2/stackTrace/StackTrace.c
        src2/stackTrace/StackTrace.h
        src2/stackTrace/StackFrame.c
        src2/stackTrace/StackFrame.h
        src2/stackTraceSignalHandler/StackTraceSignalHandler.c
        src2/stackTraceSignalHandler/StackTraceSignalHandler.h
        src2/addr2Line/Addr2Line.c
        src2/addr2Line/Addr2Line.h
        src2/signal/Signal.c
        src2/signal/Signal.h
        src2/programName/programName.c
        src2/programName/programName.h
        test/testStackTrace.c
        test/testStackTrace.h
        src2/string/StringStructs.h
        test/testStringFormat.c
        test/testStringFormat.h
        test/test.c
        test/test.h
#        src/error/addr2Line.c
#        src/error/addr2Line/addr2line.c
        ../binutils-gdb/bfd/elf-bfd.h
        src2/stackTrace/stack_size_t.h
        src2/hash/fnv1a.c
        src2/hash/fnv1a.h
        src2/util/numbers.h
        src2/collections/HashMap.c
        src2/collections/HashMap.h
        src2/collections/HashMap/HashMap_String_Addr2Line.c
        src2/collections/HashMap/HashMap_String_Addr2Line.h
        )

add_executable(LibCKhyber ${SOURCE_FILES})

target_link_libraries(LibCKhyber m bfd)