//
// Created by Khyber on 9/6/2018.
//

#ifndef VIRTUAL_ADDR_2_LINE_H
#define VIRTUAL_ADDR_2_LINE_H

#include <stdbool.h>
#include <stdlib.h>

#include "../string/String.h"

typedef struct StackTrace {
    const Strings lines;
    const bool ok;
} StackTrace;

StackTrace StackTrace_invalid() {
    return {.ok = false, .lines = {.strings = NULL, .size = 0}};
}

typedef struct Addresses {
    const void* const* const addresses;
    const size_t numAddresses;
} Addresses;

bool runAddr2Line(Addresses addresses, String* out);

#endif // VIRTUAL_ADDR_2_LINE_H
