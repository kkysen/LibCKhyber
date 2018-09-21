//
// Created by Khyber on 9/17/2018.
//

#include "testStackTrace.h"

#include "../src2/stackTrace/StackTrace.h"
#include "../src2/stackTraceSignalHandler/StackTraceSignalHandler.h"

bool testStackTrace() {
    printf("Hello\n");
//    return true;
    StackTrace_printNow(stdout);
    return true;
}

static void causeSegFault(uint32_t level) {
    if (level == 0) {
        const int* p = NULL;
        printf("%d\n", (uint32_t) (uint64_t) &level / level);
        printf("%d\n", *p);
        return;
    }
    causeSegFault(level - 1);
}

bool testStackTraceSignalHandler() {
    setStackTraceSignalHandler();
    causeSegFault(10);
    return false;
}