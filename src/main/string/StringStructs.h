//
// Created by Khyber on 9/17/2018.
//

#ifndef STRING_STRUCTS_H
#define STRING_STRUCTS_H

#include <stdlib.h>

#include "src/main/util/numbers.h"

typedef struct String {
    char *chars;
    size_t size;
    size_t capacity;
    i64 hash;
} String;

typedef struct Strings {
    String *strings;
    size_t size;
} Strings;

#endif // STRING_STRUCTS_H
