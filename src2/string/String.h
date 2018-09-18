//
// Created by Khyber on 12/1/2017.
//

#ifndef STRING_BUILDER_H
#define STRING_BUILDER_H

#include <stdio.h>

#include "StringStructs.h"

/**
 * Create a new String with an \param initialSize.
 *
 * @param [in] initialSize the initial size and capacity of the String
 * @return the String
 */
String* String_ofSize(size_t initialSize);

String String_onStackOfSize(size_t initialSize);

String* String_empty();

String* String_ofBytes(const void* bytes, size_t size);

String* String_ofCharsN(const char* chars, size_t size);

String* String_ofChars(const char* chars);

#define String_of(literalString) String_ofCharsN(literalString, sizeof(literalString) - 1)

/**
 * Free this String, clearing this String and freeing its pointer.
 * @param [in, out] this
 */
void String_free(String* this);

/**
 * Ensure this String has a capacity of at least \param capacity.
 *
 * @param [in, out] this this String
 * @param [in] capacity the minimum capacity
 */
void String_ensureCapacity(String* this, size_t capacity);

/**
 * Ensure this String has a capacity of at least
 * the current size + \param moreCapacity.
 *
 * @param [in, out] this this String
 * @param [in] moreCapacity the minimum capacity to add to the current size
 */
void String_ensureMoreCapacity(String* this, size_t moreCapacity);

/**
 * Shrink the capacity of this String to the current size.
 *
 * @param [in, out] this this String
 */
void String_shrinkToSize(String* this);

void String_shrinkToMoreCapacity(String* this, size_t moreCapacity);

/**
 * Append \param size \param bytes to this String.
 *
 * @param [in, out] this this String
 * @param [in] bytes the bytes to append
 * @param [in] size the size of the \param bytes
 */
void String_appendBytes(String* this, const void* restrict bytes, size_t size);

/**
 * Append a string \param chars of length \param size to this String.
 *
 * @param [in, out] this this String
 * @param [in] chars the string to append
 * @param [in] size the size of string \param chars
 */
void String_appendCharsN(String* this, const char* chars, size_t size);

/**
 * Append a null-terminated string \param chars to this String.
 *
 * @param [in, out] this this String
 * @param [in] chars the null-terminated string to append
 */
void String_appendChars(String* this, const char* chars);

#define String_appendLiteral(this, literalString) String_appendCharsN(this, literalString, sizeof(literalString) - 1)

void String_append(String* this, const String *string);

/**
 * Append the contents of a \param file stream to this String.
 *
 * @param [in, out] this this String
 * @param [in] file the file to append
 * @return the number of bytes read from the stream
 */
size_t String_appendStream(String* this, FILE* file);

/**
 * Clear this String,
 * freeing its chars and setting its size and capacity to 0.
 *
 * @param [in, out] this this String
 */
void String_clear(String* this);

String* String_reReference(const String* this);

String* String_copy(const String* this);

String* String_concat(const String* s1, const String* s2);

void String_format(String* this, const char* format, ...);

Strings* String_split(const String* this, const String* separator);

#endif // STRING_BUILDER_H
