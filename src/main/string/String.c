//
// Created by Khyber on 12/1/2017.
//

#include "src/main/string/String.h"

#include <stdarg.h>

#include "src/main/string/Strings.h"
#include "src/main/util/utils.h"
#include "src/main/util/hash/fnv1a.h"
#include "src/main/util/cast.h"

#define String_strictResizeMultiplier 1

// TODO check std::string and java.lang.String for realloc strategy
float String_resizeMultiplier = String_strictResizeMultiplier;

void String_resetResizeMultiplier() {
    String_resizeMultiplier = String_strictResizeMultiplier;
}

String String_usingCharsN(char *const chars, const size_t size) {
    return (String) {
            .chars = chars,
            .size = size,
            .capacity = size,
            .hash = -1,
    };
}

String String_usingChars(char *const chars) {
    return String_usingCharsN(chars, strlen(chars));
}

static String *String_allocate() {
    String *const this = (String *) malloc(sizeof(String));
    this->size = 0;
    this->capacity = 0;
    this->chars = NULL;
    this->hash = -1;
    return this;
}

static String *String_allocateChars(String *const this, const size_t initialSize) {
    this->chars = malloc(initialSize + 1);
    this->capacity = initialSize;
    String_terminate(this);
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
    free(this->chars);
    this->chars = NULL;
    this->size = this->capacity = 0;
    this->hash = -1;
}

void String_free(const String *const this) {
    if (this) {
        String_clear((String *) this);
    }
    free((String *) this);
}

void String_terminate(const String *const this) {
    this->chars[this->size] = 0;
}

static void String_ensureCapacityMultiplied(String *const this, const size_t capacity, const float resizeMultiplier) {
    if (resizeMultiplier < 1) {
        return;
    }
    if (this->capacity < capacity) {
        const size_t newCapacity = (size_t) (capacity * resizeMultiplier);
        this->capacity = newCapacity;
        this->chars = realloc(this->chars, newCapacity + 1);
        String_terminate(this);
    }
}

void String_ensureCapacity(String *const this, const size_t capacity) {
    String_ensureCapacityMultiplied(this, capacity, String_resizeMultiplier);
}

static void String_ensureMoreCapacityMultiplied(String *const this, const size_t moreCapacity,
                                                const float resizeMultiplier) {
    String_ensureCapacityMultiplied(this, moreCapacity + this->size, resizeMultiplier);
}

void String_ensureMoreCapacity(String *const this, const size_t moreCapacity) {
    String_ensureMoreCapacityMultiplied(this, moreCapacity, String_resizeMultiplier);
}

void String_shrinkToSize(String *const this) {
    this->capacity = this->size;
    this->chars = realloc(this->chars, this->capacity + 1);
    String_terminate(this);
}

void String_shrinkToMoreCapacity(String *this, size_t moreCapacity) {
    const size_t newCapacity = this->size + moreCapacity;
    if (newCapacity > this->capacity) {
        String_ensureMoreCapacity(this, moreCapacity);
    } else {
        this->capacity = newCapacity;
        this->chars = realloc(this->chars, newCapacity + 1);
        String_terminate(this);
    }
}

static void String_appendBytesUnchecked(String *const this, const void *restrict const bytes, const size_t size) {
    if (size == 0) {
        return;
    }
    memcpy(this->chars + this->size, bytes, size);
    this->size += size;
    this->hash = -1;
    String_terminate(this);
}

void String_appendBytes(String *const this, const void *restrict const bytes, const size_t size) {
    String_ensureMoreCapacityMultiplied(this, size, String_resizeMultiplier);
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
    String_appendBytesUnchecked(copy, this->chars, this->size);
    copy->hash = this->hash;
    return copy;
}

String *String_concat(const String *const s1, const String *const s2) {
    const size_t size = s1->size + s2->size;
    String *const result = String_withCapacity(size);
    String_appendBytesUnchecked(result, s1->chars, s1->size);
    String_appendBytesUnchecked(result, s2->chars, s2->size);
    return result;
}

void String_format(String *const this, const char *const format, ...) {
    va_list args;
    va_start(args, format);
    va_list argsCopy;
    va_copy(argsCopy, args);
    const int iFormattedSize = vsnprintf(NULL, 0, format, argsCopy);
    if (iFormattedSize == 0) {
        return;
    }
    if (iFormattedSize < 0) {
        perror("vsnprintf");
    }
    const size_t formattedSize = (size_t) iFormattedSize;
    String_ensureMoreCapacity(this, formattedSize);
    
    const int iActualFormattedSize = vsnprintf(this->chars + this->size, formattedSize + 1, format, args);
    if (iActualFormattedSize == 0) {
        return;
    }
    this->hash = -1;
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
        memcpy(nextToken, separator->chars, separator->size);
        nextToken += separator->size;
    }
    return Strings_new(tokens, numTokens);
}

String *String_subString(const String *this, size_t begin, size_t end) {
    return String_ofCharsN(this->chars + begin, end - begin);
}

ssize_t String_findChar(const String *this, char c) {
    return String_findCharFrom(this, 0, c);
}

ssize_t String_findCharFrom(const String *this, size_t offset, char c) {
    if (offset >= this->size) {
        return -1;
    }
    const char *location = strchr(this->chars + offset, c);
    if (!location) {
        return -1;
    }
    return location - this->chars;
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

static u64 computeHash(const String *const this) {
    return fnv1a64Hash(this->chars, this->size);
}

u64 String_hash(const String *const this) {
    if (this->hash != -1) {
        return (u64) this->hash;
    }
    const u64 hash = computeHash(this) & (1UL << (sizeof(u64) - 1)); // clear leading bit
    ((String *) this)->hash = hash;
    return hash;
}

bool String_equals(const String *const s1, const String *const s2) {
    if (s1 == s2) {
        return true;
    }
    if (!s1 || !s2) {
        return false;
    }
    if (s1->size != s2->size) {
        return false;
    }
    if (s1->hash != -1 && s2->hash != -1 && s1->hash != s2->hash) {
        return false;
    }
    return String_compare(s1, s2) == 0;
}

int String_compare(const String *const s1, const String *const s2) {
    ssize_t sizeDiff = s1->size - s2->size;
    const int cmp = memcmp(s1->chars, s2->chars, min(s1->size, s2->size));
    if (sizeDiff == 0 || cmp != 0) {
        return cmp;
    }
    return sizeDiff < 0 ? -1 : 1;
}

void String_appendBuffer(String *const this, Buffer *const buffer) {
    String_appendBytes(this, Buffer_constData(buffer), Buffer_remaining(buffer));
}

void String_sliceToBuffer(const String *const this, Buffer *const buffer, const size_t begin, const size_t end) {
    const size_t size = min(end - begin, Buffer_remaining(buffer));
    memcpy(Buffer_data(buffer), this->chars, size);
    buffer->index += size;
}

void String_toBuffer(const String *const this, Buffer *const buffer) {
    String_sliceToBuffer(this, buffer, 0, this->size);
}

ssize_t String_findLongSubString(const String *const this, const String *const subString) {
    if (subString->size > this->size) {
        return -1;
    }
    const size_t size = this->size - (subString->size - 1);
    for (size_t i = 0; i < size; i++) {
        if (memcmp(this->chars + i, subString->chars, subString->size) == 0) {
            return i;
        }
    }
    return -1;
}

ssize_t String_find(const String *this, const String *subString) {
    const u8 *const bytes = (u8 *) this->chars;
    
    // use a bitfield to truncate target,
    // not in hot loop so bitfield optimization performance not an issue
    // ssize_t used instead of size_t in edge loop b/c 0u < 0u triggers a warning
    
    #define searchForTarget(_target, type, shift) \
        const type target = _target; \
        const size_t edgeSize = this->size - (sizeof(target) - 1u); \
        for (size_t i = 0; i < edgeSize; i++) { \
            const type candidate = as(type, bytes + i) << ((shift) * 8u) >> ((shift) * 8u); \
            if (candidate == target) { \
                return i; \
            } \
        } \
        const type edge = as(type, bytes + edgeSize); \
        for (ssize_t i = 1; i <= (shift); i++) { \
            const type candidate = edge << (i * 8u) >> (i * 8u); \
            if (candidate == target) { \
                return edgeSize + i; \
            } \
        } \
        return -1 \

    #define searchAligned(type) { \
        searchForTarget(as(type, subString->chars), type, 0u); \
    }
    
    #define searchUnAligned(type, shift) { \
        struct { \
            type target: (sizeof(type) - (shift)) * 8u; \
        } targetStruct; \
        memcpy(&targetStruct, subString->chars, sizeof(targetStruct)); \
        searchForTarget(targetStruct.target, type, shift); \
    }
    
    switch (subString->size) {
        case 0:
            return -1;
        case 1: searchAligned(u8)
        case 2: searchAligned(u16)
        case 3: searchUnAligned(u32, 1u)
        case 4: searchAligned(u32)
        case 5: searchUnAligned(u64, 3u)
        case 6: searchUnAligned(u64, 2u)
        case 7: searchUnAligned(u64, 1u)
        case 8: searchAligned(u64)
            // no support for 128, 256 integers vector optimization yet
        default:
            return String_findLongSubString(this, subString);
    }
    
    #undef searchUnAligned
    #undef searchAligned
    #undef searchForTarget
}

bool String_contains(const String *const this, const String *const subString) {
    return String_find(this, subString) != -1;
}

bool String_toFd(const String *this, int fd) {
    return write(fd, this->chars, this->size) == (ssize_t) this->size;
}

bool String_toFile(const String *this, FILE *out) {
    return fwrite(this->chars, 1, this->size, out) == this->size;
}

bool String_print(const String *this) {
    return String_toFile(this, stdout);
}