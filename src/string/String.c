//
// Created by Khyber on 12/1/2017.
//

#include "String.h"

#include <string.h>
#include <stdarg.h>

#define String_terminate() this->chars[this->size] = 0

String* String_allocate(const size_t initialSize) {
    String* const this = (String*) malloc(sizeof(String));
    this->size = initialSize;
    this->capacity = initialSize;
    this->ptr = NULL;
    return this;
}

String *String_allocateChars(String* const this, const size_t initialSize) {
    this->ptr = malloc(initialSize + 1);
    String_terminate();
    return this;
}

String String_onStackOfSize(const size_t initialSize) {
    String this = {
            .size = initialSize,
            .capacity = initialSize,
    };
    String_allocateChars(&this, initialSize);
    return this;
}

String* String_ofSize(const size_t initialSize) {
    return String_allocateChars(String_allocate(initialSize), initialSize);
}

String* String_empty() {
    static const size_t DEFAULT_SIZE = 16;
    return String_ofSize(DEFAULT_SIZE);
}

String* String_ofBytes(const void* const bytes, const size_t size) {
    String* const this = String_ofSize(size);
    String_appendBytes(this, bytes, size);
    return this;
}

String* String_ofCharsN(const char* const chars, const size_t size) {
    String* const this = String_ofSize(size);
    String_appendCharsN(this, chars, size);
    return this;
}

String* String_ofChars(const char* const chars) {
    String* const this = String_ofSize(0);
    String_appendChars(this, chars);
    return this;
}

void String_free(String* const this) {
    String_clear(this);
    free(this);
}

void String_ensureCapacity(String* const this, const size_t capacity) {
    if (this->capacity < capacity) {
        this->capacity = capacity;
        this->ptr = realloc(this->ptr, capacity + 1);
        String_terminate();
    }
}

void String_ensureMoreCapacity(String* const this, const size_t moreCapacity) {
    String_ensureCapacity(this, moreCapacity + this->size);
}

void String_shrinkToSize(String* const this) {
    this->capacity = this->size;
    this->ptr = realloc(this->ptr, this->capacity + 1);
    String_terminate();
}

void String_shrinkToMoreCapacity(String *this, size_t moreCapacity) {
    const size_t newCapacity = this->size + moreCapacity;
    if (newCapacity > this->capacity) {
        String_ensureMoreCapacity(this, moreCapacity);
    } else {
        this->capacity = newCapacity;
        this->ptr = realloc(this->ptr, newCapacity + 1);
        String_terminate();
    }
}

void String_appendBytes(String* const this, const void restrict* const bytes, const size_t size) {
    const size_t remaining = this->capacity - this->size;
    if (remaining < size) {
        this->capacity = this->size + size;
        this->ptr = realloc(this->ptr, this->capacity + 1);
    }
    memcpy(this->ptr + this->size, bytes, size);
    this->size += size;
    String_terminate();
}

void String_appendCharsN(String* const this, const char* const chars, const size_t size) {
    String_appendBytes(this, chars, size * sizeof(char));
}

void String_appendChars(String* const this, const char* const chars) {
    String_appendCharsN(this, chars, strlen(chars));
}

void String_append(String *const this, const String string) {
    String_appendCharsN(this, string.chars, string.size);
}

size_t String_appendStream(String* const this, FILE* const file) {
    char buffer[4096] = {0};
    size_t totalNumBytes = 0;
    size_t numBytes;
    while ((numBytes = fread(buffer, 1, sizeof(buffer) - 1, file)) > 0) {
        totalNumBytes += numBytes;
        String_appendBytes(this, buffer, numBytes);
    }
    return totalNumBytes;
}

void String_clear(String* const this) {
    free(this->ptr);
    this->ptr = NULL;
    this->size = this->capacity = 0;
}

String *String_reReference(const String this) {
    String* const reference = String_ofSize(this.size);
    reference->chars = this.chars;
    return reference;
}

String* String_copy(const String this) {
    String* const copy = String_ofSize(this.size);
    memcpy(copy->chars, this.chars, this.size);
    return copy;
}

String* String_concat(const String s1, const String s2) {
    String* const result = String_ofSize(s1.size + s2.size);
    memcpy(result->chars, s1.chars, s1.size);
    memcpy(result->chars + s1.size, s2.chars, s2.size);
    return result;
}

void String_format(String* const this, const char* const format, ...) {
    va_list args;
    va_start(args, format);
    const int formattedLength = snprintf(NULL, 0, format, args);
    if (formattedLength < 0) {
        perror("snprinf");
    }
    const size_t formattedSize = (size_t) formattedLength;
    String_ensureMoreCapacity(this, formattedSize);
    snprintf(this->chars + this->size + 1, formattedSize, format, args);
    va_end(args);
}

static size_t splitInPlaceAndCountTokens(char *const chars, const char *const separator) {
    // TODO use strsep or strtok
}

Strings* String_split(const String this, const String separator) {
    const size_t numTokens = splitInPlaceAndCountTokens(this.chars, separator.chars);
    String *const tokens = malloc(sizeof(String *) * numTokens);
    char *nextToken = this.chars;
    for (size_t i = 0;; ++i) {
        const size_t tokenLength = strlen(nextToken);
        const String *const token = String_ofCharsN(nextToken, tokenLength);
        memcpy(tokens + i, token, sizeof(String));
        if (i == numTokens - 1) {
            break;
        }
        // fill in removed separator (from splitInPlaceAndCountTokens)
        nextToken += tokenLength;
        memcpy(nextToken, separator.ptr, separator.size);
        nextToken += separator.size;
    }
    return Strings_new(tokens, numTokens);
}