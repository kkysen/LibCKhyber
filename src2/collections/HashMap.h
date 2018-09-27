//
// Created by Khyber on 9/25/2018.
//

#ifndef HASH_MAP_H
#define HASH_MAP_H

#include "../string/String.h"

typedef String * K;
typedef String * V;

struct HashMapNode;
typedef struct HashMapNode HashMapNode;

typedef struct HashMap {
    HashMapNode *table;
    size_t size;
    size_t resizeThreshold;
    float loadFactor;
} HashMap;

struct HashMapNode {
    K key;
    V value;
    u64 hash;
    HashMapNode *next;
} HashMapNode;

void HashMap_init(HashMap *this);

HashMap *HashMap_new();

void HashMap_clear(HashMap *this);

void HashMap_free(HashMap *this);

void HashMap_get(const HashMap *this, const K key, int const a) {

}

#endif // HASH_MAP_H
