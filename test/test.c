//
// Created by Khyber on 9/17/2018.
//

#include "test.h"

#include <stdlib.h>
#include <values.h>

#include "../src/util/utils.h"
#include "testStringFormat.h"
#include "testStackTrace.h"

typedef bool (*Test)();

static const Test tests[] = {testStackTrace, testStackTraceSignalHandler};

bool test() {
    const int64_t x = -((int64_t) INT_MAX) - 1000;
    const int32_t y = (int32_t) x;
    printf("%d\n", y);
    bool all = true;
    for (size_t i = 0; i < arrayLen(tests); i++) {
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
