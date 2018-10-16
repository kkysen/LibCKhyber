//
// Created by Khyber on 1/24/2018.
//

#include "src/main/serialize/buffer/Buffer.h"

bool Buffer_isValid(const Buffer *const buffer) {
    return buffer->data && buffer->index < buffer->limit && buffer->limit <= buffer->capacity;
}

bool Buffer_hasRemaining(const Buffer *const buffer) {
    return buffer->index < buffer->limit;
}

size_t Buffer_remaining(const Buffer *buffer) {
    return buffer->limit - buffer->index;
}

void *Buffer_remainingData(const Buffer *buffer) {
    return buffer->data + buffer->index;
}