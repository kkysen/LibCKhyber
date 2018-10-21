//
// Created by Khyber on 12/1/2017.
//

#ifndef STRING_H
#define STRING_H

#include <sys/types.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

#include "src/main/string/StringStructs.h"
#include "src/main/util/numbers.h"
#include "src/main/serialize/buffer/Buffer.h"

extern float String_resizeMultiplier;

void String_resetResizeMultiplier();

String String_usingCharsN(char *chars, size_t size);

String String_usingChars(char *chars);

#define String_usingLiteral(literalString) String_usingCharsN(literalString, sizeof(literalString) - 1)

/**
 * Create a new String with an \param initialSize.
 *
 * @param [in] initialSize the initial size and capacity of the String
 * @return the String
 */
String *String_withCapacity(size_t initialSize);

String String_onStackOfSize(size_t initialSize);

String *String_empty();

String *String_default();

String *String_ofBytes(const void *bytes, size_t size);

String *String_ofCharsN(const char *chars, size_t size);

String *String_ofChars(const char *chars);

#define String_of(literalString) String_ofCharsN(literalString, sizeof(literalString) - 1)

/**
 * Clear this String,
 * freeing its chars and setting its size and capacity to 0.
 *
 * @param [in, out] this this String
 */
void String_clear(String *this);

/**
 * Free this String, clearing this String and freeing its pointer.
 * @param [in, out] this
 */
void String_free(const String *this);

void String_terminate(const String *this);

/**
 * Ensure this String has a capacity of at least \param capacity.
 *
 * @param [in, out] this this String
 * @param [in] capacity the minimum capacity
 */
void String_ensureCapacity(String *this, size_t capacity);

/**
 * Ensure this String has a capacity of at least
 * the current size + \param moreCapacity.
 *
 * @param [in, out] this this String
 * @param [in] moreCapacity the minimum capacity to add to the current size
 */
void String_ensureMoreCapacity(String *this, size_t moreCapacity);

/**
 * Shrink the capacity of this String to the current size.
 *
 * @param [in, out] this this String
 */
void String_shrinkToSize(String *this);

void String_shrinkToMoreCapacity(String *this, size_t moreCapacity);

/**
 * Append \param size \param bytes to this String.
 *
 * @param [in, out] this this String
 * @param [in] bytes the bytes to append
 * @param [in] size the size of the \param bytes
 */
void String_appendBytes(String *this, const void *restrict bytes, size_t size);

/**
 * Append a string \param chars of length \param size to this String.
 *
 * @param [in, out] this this String
 * @param [in] chars the string to append
 * @param [in] size the size of string \param chars
 */
void String_appendCharsN(String *this, const char *chars, size_t size);

/**
 * Append a null-terminated string \param chars to this String.
 *
 * @param [in, out] this this String
 * @param [in] chars the null-terminated string to append
 */
void String_appendChars(String *this, const char *chars);

#define String_appendLiteral(this, literalString) String_appendCharsN(this, literalString, sizeof(literalString) - 1)

#define String_appendNewLine(this) String_appendLiteral(out, "\n")

void String_append(String *this, const String *string);

/**
 * Append the contents of a \param file stream to this String.
 *
 * @param [in, out] this this String
 * @param [in] file the file to append
 * @return the number of bytes read from the stream
 */
size_t String_appendStream(String *this, FILE *file);

String *String_reReference(const String *this);

String *String_copy(const String *this);

String *String_concat(const String *s1, const String *s2);

void String_format(String *this, const char *format, ...);

Strings *String_split(const String *this, const String *separator);

String *String_subString(const String *this, size_t begin, size_t end);

ssize_t String_findChar(const String *this, char c);

ssize_t String_findCharFrom(const String *this, size_t offset, char c);

ssize_t String_rfind(const String *this, char c);

const char *String_nullableChars(const String *this);

// might modify this->hash, but will act as a const object
u64 String_hash(const String *this);

bool String_equals(const String *s1, const String *s2);

int String_compare(const String *s1, const String *s2);

void String_appendBuffer(String *this, Buffer *buffer);

void String_sliceToBuffer(const String *this, Buffer *buffer, size_t begin, size_t end);

void String_toBuffer(const String *this, Buffer *buffer);

ssize_t String_find(const String *this, const String *subString);

bool String_contains(const String *this, const String *subString);

bool String_toFd(const String *this, int fd);

bool String_toFile(const String *this, FILE *out);

bool String_print(const String *this);

#endif // STRING_H
