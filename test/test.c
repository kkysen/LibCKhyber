//
// Created by Khyber on 9/17/2018.
//

#include "test.h"

#include <stdlib.h>

#include "../src2/util/utils.h"
#include "testStringFormat.h"
#include "testStackTrace.h"

typedef bool (*Test)();

static const Test tests[] = {testStringFormat, testStackTrace};

bool test() {
    bool all = true;
    for (size_t i = 0; i < arrayLen(tests); i++) {
        printf("Test %zu starting...\n", i);
        const bool passed = tests[i]();
        if (!passed) {
            all = false;
        }
        printf("Test %zu: %s\n", i, passed ? "true" : "false");
    }
    return all;
}

int main() {
    return test() ? EXIT_SUCCESS : EXIT_FAILURE;
}
