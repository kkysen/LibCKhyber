//
// Created by Khyber on 9/17/2018.
//

#include "src/test/testStackTrace.h"

#include <bfd.h>

#include "src/main/stackTrace/stackTrace/StackTrace.h"
#include "src/main/stackTrace/stackTraceSignalHandler/StackTraceSignalHandler.h"
#include "src/main/util/programName/programName.h"

static void toInline() {
    StackTrace_printNow(stdout);
}

bool testStackTrace() {
    toInline();
    return true;
}

static void causeSegFault(int level ATTRIBUTE_UNUSED) {
    int *p = NULL;
    printf("%d\n", *p);
}

static void causeDivByZero(int level) {
    printf("%d\n", (uint32_t) (uint64_t) &level / level);
}

static void causeError(uint32_t level, void (*_causeError)(int level)) {
    if (level == 0) {
        _causeError(level);
        return;
    }
    causeError(level - 1, _causeError);
}

bool testStackTraceSignalHandler() {
    setStackTraceSignalHandler();
    const uint32_t level = 10;
    causeError(level, causeSegFault);
    causeError(level, causeDivByZero);
    return false;
}