//
// Created by Khyber on 1/24/2018.
//

#ifndef BUFFER_H
#define BUFFER_H

#include <unistd.h>
#include <stdbool.h>

#include "../../util/setField.h"

typedef struct Buffer {
    void *data;
    size_t index;
    size_t limit;
    size_t capacity;
} Buffer;

/**
 * Puts a value into this buffer and advances the buffer's index.
 *
 * @param buffer the buffer the \param val is being added to
 * @param val the value being added to the \param buffer
 */
#define Buffer_put(buffer, val) \
    memcpy((buffer)->data + (buffer)->index, &(val), sizeof(val)); \
    (buffer)->index += sizeof(val)

#define arraySize(array, length) ((length) * sizeof(*(array)))

/**
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
#define Buffer_putArray(buffer, array, length) \
    do { \
        const size_t size = arraySize(array, length); \
        Buffer_put(buffer, size); \
        memcpy((buffer)->data + (buffer)->index, array, size); \
        (buffer)->index += size; \
    } while (false)

/**
 * Gets a value of type \param var from a \param buffer
 * and places it in a \param var.
 * Also advances the \param buffer's index.
 *
 * @param buffer the buffer to get the value from
 * @param var the variable to place the value in
 */
#define Buffer_get(buffer, var) \
    memcpy((void *) &(var), (buffer)->data + (buffer)->index, sizeof(var)); \
    (buffer)->index += sizeof(var)

/**
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
#define Buffer_getArray(buffer, array, length_var) \
    do { \
        size_t length; \
        Buffer_get(buffer, length); \
        typeof(array) alloced_array = realloc(array, length); \
        memcpy(alloced_array, (buffer)->data + (buffer)->index, arraySize(array, length)); \
        (buffer)->index += arraySize(array, length); \
        memcpy((void *) &(array), &alloced_array, sizeof(array)); \
        typeof(length_var) casted_length = (typeof(length_var)) (length / sizeof(*(array))); \
        memcpy((void *) &(length_var), &casted_length, sizeof(casted_length)); \
    } while (false)

bool Buffer_isValid(const Buffer *buffer);

bool Buffer_hasRemaining(const Buffer *buffer);

size_t Buffer_remaining(const Buffer *buffer);

void *Buffer_remainingData(const Buffer *buffer);



#endif // BUFFER_H
