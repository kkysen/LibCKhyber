//
// Created by Khyber on 9/7/2018.
//

#ifndef STRINGS_H
#define STRINGS_H

#include "String.h"

typedef struct Strings {
    String *strings;
    size_t size;
} Strings;

Strings* Strings_new(String *strings, size_t size);

void Strings_clear(Strings *this);

#endif // STRINGS_H
