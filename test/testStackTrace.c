//
// Created by Khyber on 9/17/2018.
//

#include "testStackTrace.h"

#include "../src2/stackTrace/StackTrace.h"

bool testStackTrace() {
    printf("Hello\n");
//    return true;
    StackTrace_printNow(stdout);
    return true;
}