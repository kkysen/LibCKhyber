//
// Created by Khyber on 9/17/2018.
//

#include "test.h"

#include <stdlib.h>

#include "../main/util/utils.h"
#include "testStringFormat.h"
#include "testStackTrace.h"

typedef bool (*Test)();

static const Test tests[] = {testStringFormat, testStackTrace, testStackTraceSignalHandler};

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
    return test() ? EXIT_SUCCESS : EXIT_FAILURE;
}
