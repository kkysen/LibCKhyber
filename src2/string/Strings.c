//
// Created by Khyber on 9/7/2018.
//

#include "Strings.h"

#include "String.h"

Strings* Strings_new(String *const strings, const size_t size) {
    Strings *const this = malloc(sizeof(Strings));
    this->strings = strings;
    this->size = size;
    return this;
}

void Strings_clear(Strings *const this) {
    for (size_t i = 0; i < this->size; ++i) {
        String_free(this->strings + i);
    }
    free(this->strings);
    this->strings = NULL;
    this->size = 0;
}