//
// Created by Khyber on 9/17/2018.
//

#include <bfd.h>
#include "testStackTrace.h"

#include "../src2/stackTrace/StackTrace.h"
#include "../src2/stackTraceSignalHandler/StackTraceSignalHandler.h"
#include "../src2/programName/programName.h"

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
    const uint32_t level = 100;
    causeError(level, causeSegFault);
    causeError(level, causeDivByZero);
    return false;
}