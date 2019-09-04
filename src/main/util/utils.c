//
// Created by Khyber on 11/9/2017.
//

#include "src/main/util/utils.h"

#include <stdlib.h>
#include <math.h>
#include <time.h>

const char *HOME = NULL;

void init_home() {
    HOME = getenv("HOME");
}

void doubleSleep(double seconds) {
    struct timespec timespec = {
            .tv_sec = (time_t) seconds,
            .tv_nsec = (long) ((seconds - floor(seconds)) * 1e9)
    };
    nanosleep(&timespec, NULL);
}

double secondsElapsed(const clock_t start, const clock_t end) {
    return (end - start) / (double) CLOCKS_PER_SEC;
}

void freeConst(const void *ptr) {
    free((void *) ptr);
}