//
// Created by Khyber on 1/24/2018.
//

#include "src/main/serialize/buffer/Buffer.h"

#include "src/main/util/utils.h"

bool Buffer_isValid(const Buffer *const this) {
    return this->data && this->index < this->limit && this->limit <= this->capacity;
}

bool Buffer_hasRemaining(const Buffer *const this) {
    return this->index < this->limit;
}

size_t Buffer_remaining(const Buffer *const this) {
    return this->limit - this->index;
}

const void *Buffer_constData(const Buffer *const this) {
    return this->data + this->index;
}

void *Buffer_data(Buffer *const this) {
    return this->data + this->index;
}

void Buffer_putMemory(Buffer *const this, const void *const data, const size_t size) {
    memcpy(Buffer_data(this), data, size);
    this->index += size;
}

void Buffer_getMemory(Buffer *const this, void *const data, const size_t size) {
    memcpy(data, Buffer_constData(this), size);
    this->index += size;
}

bool Buffer_write(Buffer *const this, const int fd) {
    if (!Buffer_isValid(this)) {
        perror("Buffer_isValid");
        return false;
    }
    
    size_t size = Buffer_remaining(this);
    if (size == 0) {
        return true; // no data to send
    }
    
    const void *const data = Buffer_constData(this);
    size_t i = 0;
    while (size > 0) {
        const ssize_t bytesWritten = write(fd, data + i, size);
        if (bytesWritten == -1) {
            perror("write");
            this->index += i;
            return false;
        }
        size -= bytesWritten;
        i += bytesWritten;
    }
    this->index += i;
    
    return true;
}

bool Buffer_read(Buffer *const this, const int fd) {
    if (!Buffer_isValid(this)) {
        perror("Buffer_isValid");
        return false;
    }
    
    size_t size = Buffer_remaining(this);
    if (size == 0) {
        return true; // no data to recv
    }
    
    void *const data = Buffer_data(this);
    size_t i = 0;
    while (size > 0) {
        const ssize_t bytesRead = read(fd, data + i, size);
        if (bytesRead == -1) {
            perror("read");
            this->index += i;
            return false;
        }
        size -= bytesRead;
        i += bytesRead;
    }
    this->index += i;
    
    return true;
}