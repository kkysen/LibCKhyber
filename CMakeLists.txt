cmake_minimum_required(VERSION 3.9)
project(LibCKhyber C)

set(CMAKE_C_STANDARD 11)

# support lto (link time optimization)
SET(CMAKE_AR "gcc-ar")
SET(CMAKE_RANLIB "gcc-ranlib")


set(CMAKE_C_OPTIMIZATION_FLAGS "-O3 -flto")
set(CMAKE_C_ERROR_FLAGS "-Wall -Werror -Wextra")
set(CMAKE_C_NO_ERROR_FLAGS "-Wno-error=unused-function -Wno-error=unused-parameter")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${CMAKE_C_ERROR_FLAGS} ${CMAKE_C_NO_ERROR_FLAGS} ${CMAKE_C_OPTIMIZATION_FLAGS}")

set(LIB_BFD_FILES
        lib/binutils-bfd/bfd/elf-bfd.h
        lib/binutils-bfd/include/elf/common.h
        lib/binutils-bfd/include/elf/external.h
        lib/binutils-bfd/include/elf/internal.h
        lib/binutils-bfd/include/bfdlink.h
        )

set(STRING_FILES
        src/string/String.h
        src/string/String.c
        src/string/Strings.c
        src/string/Strings.h
        src/string/StringStructs.h
        )

set(UTIL_FILES
        src/util/utils.h
        src/util/utils.c
        src/util/signal/sigAction.c
        src/util/signal/sigAction.h
        src/util/setField.h
        src/util/buffer/buffer.h
        src/util/buffer/buffer.c
        src/util/signal/Signal.c
        src/util/signal/Signal.h
        src/util/programName/programName.c
        src/util/programName/programName.h
        src/util/hash/fnv1a.c
        src/util/hash/fnv1a.h
        src/util/numbers.h
        )

set(COLLECTIONS_FILES
        src/collections/HashMap/HashMap_String_Addr2Line.c
        src/collections/HashMap/HashMap_String_Addr2Line.h
        )

set(STACK_TRACE_FILES
        src/stackTrace/bfd/BinaryFileDescriptor.c
        src/stackTrace/bfd/BinaryFileDescriptor.h
        src/stackTrace/stackTrace/StackTrace.c
        src/stackTrace/stackTrace/StackTrace.h
        src/stackTrace/stackTrace/StackFrame.c
        src/stackTrace/stackTrace/StackFrame.h
        src/stackTrace/stackTraceSignalHandler/StackTraceSignalHandler.c
        src/stackTrace/stackTraceSignalHandler/StackTraceSignalHandler.h
        src/stackTrace/addr2Line/Addr2Line.c
        src/stackTrace/addr2Line/Addr2Line.h
        src/stackTrace/stackTrace/stack_size_t.h
        )

set(TEST_FILES
        test/testStackTrace.c
        test/testStackTrace.h
        test/testStringFormat.c
        test/testStringFormat.h
        test/test.c
        test/test.h
        )

set(SOURCE_FILES
        ${LIB_BFD_FILES}
        ${STRING_FILES}
        ${UTIL_FILES}
        ${COLLECTIONS_FILES}
        ${STACK_TRACE_FILES}
        ${TEST_FILES}
        )

add_library(Khyber STATIC ${SOURCE_FILES})

add_executable(LibCKhyber ${SOURCE_FILES})

target_link_libraries(LibCKhyber m bfd)
target_link_libraries(Khyber m bfd)