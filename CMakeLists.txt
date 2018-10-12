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
        src/lib/binutils-bfd/bfd/elf-bfd.h
        src/lib/binutils-bfd/include/elf/common.h
        src/lib/binutils-bfd/include/elf/external.h
        src/lib/binutils-bfd/include/elf/internal.h
        src/lib/binutils-bfd/include/bfdlink.h
        )

set(STRING_FILES
        src/main/string/String.h
        src/main/string/String.c
        src/main/string/Strings.c
        src/main/string/Strings.h
        src/main/string/StringStructs.h
        )

set(UTIL_FILES
        src/main/util/utils.h
        src/main/util/utils.c
        src/main/util/signal/sigAction.c
        src/main/util/signal/sigAction.h
        src/main/util/setField.h
        src/main/util/buffer/buffer.h
        src/main/util/buffer/buffer.c
        src/main/util/signal/Signal.c
        src/main/util/signal/Signal.h
        src/main/util/programName/programName.c
        src/main/util/programName/programName.h
        src/main/util/hash/fnv1a.c
        src/main/util/hash/fnv1a.h
        src/main/util/numbers.h
        )

set(COLLECTIONS_FILES
        src/main/collections/HashMap/HashMap_String_Addr2Line.c
        src/main/collections/HashMap/HashMap_String_Addr2Line.h
        )

set(STACK_TRACE_FILES
        src/main/stackTrace/bfd/BinaryFileDescriptor.c
        src/main/stackTrace/bfd/BinaryFileDescriptor.h
        src/main/stackTrace/stackTrace/StackTrace.c
        src/main/stackTrace/stackTrace/StackTrace.h
        src/main/stackTrace/stackTrace/StackFrame.c
        src/main/stackTrace/stackTrace/StackFrame.h
        src/main/stackTrace/stackTraceSignalHandler/StackTraceSignalHandler.c
        src/main/stackTrace/stackTraceSignalHandler/StackTraceSignalHandler.h
        src/main/stackTrace/addr2Line/Addr2Line.c
        src/main/stackTrace/addr2Line/Addr2Line.h
        src/main/stackTrace/stackTrace/stack_size_t.h
        )

set(TEST_FILES
        src/test/testStackTrace.c
        src/test/testStackTrace.h
        src/test/testStringFormat.c
        src/test/testStringFormat.h
        src/test/test.c
        src/test/test.h
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