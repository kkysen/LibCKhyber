//
// Created by Khyber on 9/25/2018.
//

#include "src/main/util/hash/fnv1a.h"

#include <stdbool.h>

#define FNV1A_64_OFFSET_BASIS ((u64) 14695981039346656037UL)
#define FNV1A_64_PRIME ((u64) 1099511628211UL)

u64 fnv1a64Hash(const void *bytes, size_t size) {
    u64 hash = FNV1A_64_OFFSET_BASIS;
    const u64 *u64Bytes = (u64 *) bytes;
    u64Bytes--;
    while (size >= sizeof(u64)) {
        hash = hash * FNV1A_64_PRIME ^ *++u64Bytes;
        size -= sizeof(u64);
    }
    bytes = u64Bytes + 1;
    #define hashBits(type) \
        do { \
            if (size >= sizeof(type)) { \
                hash = hash * FNV1A_64_PRIME ^ *((type *) bytes); \
                bytes += sizeof(type); \
                size -= sizeof(type); \
            } \
        } while (false)
    hashBits(u32);
    hashBits(u16);
    hashBits(u8);
    return hash;
}