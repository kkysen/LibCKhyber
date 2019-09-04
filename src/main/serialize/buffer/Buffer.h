//
// Created by Khyber on 1/24/2018.
//

#ifndef BUFFER_H
#define BUFFER_H

#include <unistd.h>
#include <stdbool.h>
#include <stdio.h>

#include "src/main/util/setField.h"

typedef struct Buffer {
    void *data;
    size_t index;
    size_t limit;
    size_t capacity;
} Buffer;

bool Buffer_isValid(const Buffer *this);

bool Buffer_hasRemaining(const Buffer *this);

size_t Buffer_remaining(const Buffer *this);

const void *Buffer_constData(const Buffer *this);

void *Buffer_data(Buffer *this);

void Buffer_putMemory(Buffer *this, const void *data, size_t size);

void Buffer_getMemory(Buffer *this, void *data, size_t size);

#define arraySize(array, length) ((length) * sizeof(*(array)))

/**
 * Puts a value into this buffer and advances the buffer's index.
 *
 * @param buffer the buffer the \param val is being added to
 * @param val the value being added to the \param buffer
 */
#define Buffer_put(this, val) Buffer_putMemory(this, &(val), sizeof(val)

/**
 * TODO fix or delete
 *
 * Puts a typed array of length \param length into this buffer
 * and advances the buffer's index.
 *
 * Note: All lengths are serialized as size_t,
 * no matter what its original type is.
 *
 * @param buffer the buffer the \param array is being added to
 * @param array the typed array being added to the \param buffer
 * @param length the length of the array in terms of its type
 */
#define Buffer_putArray(this, array, length) \
    do { \
        const size_t size = arraySize(array, length); \
        Buffer_put(this, size); \
        memcpy(Buffer_data(this), array, size); \
        (this)->index += size; \
    } while (false)

/**
 * Gets a value of type \param var from a \param buffer
 * and places it in a \param var.
 * Also advances the \param buffer's index.
 *
 * @param buffer the buffer to get the value from
 * @param var the variable to place the value in
 */
#define Buffer_get(this, var) Buffer_getMemory(this, (void *) &(var), sizeof(var))

/**
 * TODO fix or delete
 *
 * Gets an array serialized in a \param buffer
 * and places it (reallocing) into an \param array
 * and sets \param length_var to the array's length.
 * Also advances the \param buffer's index.
 *
 * Note: All lengths are serialized as size_t,
 * no matter what its original type is.
 *
 * @param buffer the buffer to get the array from
 * @param array a pointer to an array that will be realloc'ed to store the array data from the buffer
 * @param length_var an integer variable that will store the length of the array w.r.t to its type
 */
#define Buffer_getArray(this, array, lengthVar) \
    do { \
        size_t length; \
        Buffer_get(this, length); \
        typeof(array) alloced_array = realloc(array, length); \
        memcpy(alloced_array, Buffer_constData(this), arraySize(array, length)); \
        (this)->index += arraySize(array, length); \
        memcpy((void *) &(array), &alloced_array, sizeof(array)); \
        typeof(lengthVar) casted_length = (typeof(lengthVar)) (length / sizeof(*(array))); \
        memcpy((void *) &(lengthVar), &casted_length, sizeof(casted_length)); \
    } while (false)

bool Buffer_write(Buffer *this, int fd);

bool Buffer_read(Buffer *this, int fd);

bool Buffer_writeFile(Buffer *this, FILE *file);

bool Buffer_readFile(Buffer *this, FILE *file);



#endif // BUFFER_H
