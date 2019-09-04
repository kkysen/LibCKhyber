//
// Created by Khyber on 9/17/2018.
//

#include "src/test/test.h"

#include <stdlib.h>

#include "src/main/util/utils.h"
#include "src/test/testStringFormat.h"
#include "src/test/testStackTrace.h"
#include "src/test/testStringContains.h"
#include "src/test/testException.h"
#include "src/main/stackTrace/stackTraceSignalHandler/StackTraceSignalHandler.h"

typedef bool (*Test)();

static const Test tests[] = {testStringFormat, testStringContains, testStackTrace, testException,
                             testStackTraceSignalHandler};

bool test() {
    bool all = true;
    for (size_t i = 0; i < arrayLen(tests); i++) {
        printf("__________________________________________________\n");
        printf("Test %zu starting...\n", i);
        const bool passed = tests[i]();
        if (!passed) {
            all = false;
        }
        printf("Test %zu: %s\n", i, passed ? "true" : "false");
        fflush(stdout);
        fflush(stderr);
    }
    return all;
}

int main() {
    setStackTraceSignalHandler();
    return test() ? EXIT_SUCCESS : EXIT_FAILURE;
}
