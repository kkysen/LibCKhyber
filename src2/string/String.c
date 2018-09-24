//
// Created by Khyber on 12/1/2017.
//

#include "String.h"

#include <string.h>
#include <stdarg.h>
#include <ansidecl.h>

#include "Strings.h"

#define String_terminate() this->chars[this->size] = 0

static String *String_allocate() {
    String *const this = (String *) malloc(sizeof(String));
    this->size = 0;
    this->capacity = 0;
    this->ptr = NULL;
    return this;
}

static String *String_allocateChars(String *const this, const size_t initialSize) {
    this->ptr = malloc(initialSize + 1);
    this->capacity = initialSize;
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

String *String_withCapacity(const size_t initialSize) {
    return String_allocateChars(String_allocate(), initialSize);
}

String *String_empty() {
    return String_withCapacity(0);
}

String *String_default() {
    static const size_t DEFAULT_SIZE = 16;
    return String_withCapacity(DEFAULT_SIZE);
}

String *String_ofBytes(const void *const bytes, const size_t size) {
    String *const this = String_withCapacity(size);
    String_appendBytes(this, bytes, size);
    return this;
}

String *String_ofCharsN(const char *const chars, const size_t size) {
    String *const this = String_withCapacity(size);
    String_appendCharsN(this, chars, size);
    return this;
}

String *String_ofChars(const char *const chars) {
    String *const this = String_withCapacity(0);
    String_appendChars(this, chars);
    return this;
}

void String_clear(String *const this) {
    free(this->ptr);
    this->ptr = NULL;
    this->size = this->capacity = 0;
}

void String_free(String *const this) {
    if (this) {
        String_clear(this);
    }
    free(this);
}

void String_ensureCapacity(String *const this, const size_t capacity) {
    if (this->capacity < capacity) {
        this->capacity = capacity;
        this->ptr = realloc(this->ptr, capacity + 1);
        String_terminate();
    }
}

void String_ensureMoreCapacity(String *const this, const size_t moreCapacity) {
    String_ensureCapacity(this, moreCapacity + this->size);
}

void String_shrinkToSize(String *const this) {
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

static void String_appendBytesUnchecked(String *const this, const void *restrict const bytes, const size_t size) {
    memcpy(this->ptr + this->size, bytes, size);
    this->size += size;
    String_terminate();
}

void String_appendBytes(String *const this, const void *restrict const bytes, const size_t size) {
    String_ensureMoreCapacity(this, size);
    String_appendBytesUnchecked(this, bytes, size);
}

void String_appendCharsN(String *const this, const char *const chars, const size_t size) {
    String_appendBytes(this, chars, size * sizeof(char));
}

void String_appendChars(String *const this, const char *const chars) {
    String_appendCharsN(this, chars, strlen(chars));
}

void String_append(String *const this, const String *const string) {
    String_appendCharsN(this, string->chars, string->size);
}

size_t String_appendStream(String *const this, FILE *const file) {
    char buffer[4096] = {0};
    size_t totalNumBytes = 0;
    size_t numBytes;
    while ((numBytes = fread(buffer, 1, sizeof(buffer) - 1, file)) > 0) {
        totalNumBytes += numBytes;
        String_appendBytes(this, buffer, numBytes);
    }
    return totalNumBytes;
}

String *String_reReference(const String *const this) {
    String *const reference = String_withCapacity(this->size);
    reference->size = this->size;
    reference->chars = this->chars;
    return reference;
}

String *String_copy(const String *const this) {
    String *const copy = String_withCapacity(this->size);
    String_appendBytesUnchecked(copy, this->ptr, this->size);
    return copy;
}

String *String_concat(const String *const s1, const String *const s2) {
    const size_t size = s1->size + s2->size;
    String *const result = String_withCapacity(size);
    String_appendBytesUnchecked(result, s1->ptr, s1->size);
    String_appendBytesUnchecked(result, s2->ptr, s2->size);
    return result;
}

void String_format(String *const this, const char *const format, ...) {
    va_list args;
    va_start(args, format);
    va_list argsCopy;
    va_copy(argsCopy, args);
    const int iFormattedSize = vsnprintf(NULL, 0, format, argsCopy);
    if (iFormattedSize < 0) {
        perror("vsnprinf");
    }
    const size_t formattedSize = (size_t) iFormattedSize;
    String_ensureMoreCapacity(this, formattedSize);
    const int iActualFormattedSize = vsnprintf(this->chars + this->size, formattedSize + 1, format, args);
    if (iActualFormattedSize < 0) {
        perror("vsnprintf");
    }
    const size_t actualFormattedSize = (size_t) iActualFormattedSize;
    if (actualFormattedSize != formattedSize) {
        perror("vsnprintf: actualFormattedSize != formattedSize");
    }
    this->size += actualFormattedSize; // TODO add checks
    va_end(args);
}

static size_t splitInPlaceAndCountTokens(char *const chars, const char *const separator) {
    perror("NOT IMPLEMENTED");
    exit(EXIT_FAILURE);
    // TODO use strsep or strtok
}

Strings *String_split(const String *const this, const String *const separator) {
    const size_t numTokens = splitInPlaceAndCountTokens(this->chars, separator->chars);
    String *const tokens = malloc(sizeof(String *) * numTokens);
    char *nextToken = this->chars;
    for (size_t i = 0;; ++i) {
        const size_t tokenLength = strlen(nextToken);
        const String *const token = String_ofCharsN(nextToken, tokenLength);
        memcpy(tokens + i, token, sizeof(String));
        if (i == numTokens - 1) {
            break;
        }
        // fill in removed separator (from splitInPlaceAndCountTokens)
        nextToken += tokenLength;
        memcpy(nextToken, separator->ptr, separator->size);
        nextToken += separator->size;
    }
    return Strings_new(tokens, numTokens);
}

String *String_subString(const String *this, size_t begin, size_t end) {
    return String_ofCharsN(this->chars + begin, end - begin);
}

ssize_t String_rfind(const String *const this, const char c) {
    const char *s = this->chars + this->size;
    while (*--s != c) {
        if (s == this->chars) {
            return -1;
        }
    }
    return s - this->chars;
}

const char *String_nullableChars(const String *const this) {
    return this ? this->chars : NULL;
}