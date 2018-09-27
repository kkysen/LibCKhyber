

/**
  * Adapted from java.util.HashMap in OpenJDK.
  */

#ifndef HashMap_String_Addr2Line_H
#define HashMap_String_Addr2Line_H

#include <stdlib.h>
#include <stdbool.h>
#include "../../string/String.h"
#include "../../addr2Line/Addr2Line.h"

struct HashMapNode_String_Addr2Line;

typedef struct HashMapNode_String_Addr2Line HashMapNode_String_Addr2Line;

struct HashMapNode_String_Addr2Line {
    String * key;
    Addr2Line * value;
    u64 hash;
    HashMapNode_String_Addr2Line *next;
};

typedef struct HashMap_String_Addr2Line {
    HashMapNode_String_Addr2Line *table;
    size_t size;
    size_t capacity;
    size_t resizeThreshold;
    float loadFactor;
} HashMap_String_Addr2Line;



void HashMap_String_Addr2Line_initWithCapacityAndLoadFactor(HashMap_String_Addr2Line *this, size_t initialCapacity, float loadFactor);

void HashMap_String_Addr2Line_initWithCapacity(HashMap_String_Addr2Line *this, size_t initialCapacity);

void HashMap_String_Addr2Line_initWithLoadFactor(HashMap_String_Addr2Line *this, float loadFactor);

void HashMap_String_Addr2Line_init(HashMap_String_Addr2Line *this);

void HashMap_String_Addr2Line_clear(HashMap_String_Addr2Line *this);



HashMap_String_Addr2Line *HashMap_String_Addr2Line_newWithCapacityAndLoadFactor(size_t initialCapacity, float loadFactor);

HashMap_String_Addr2Line *HashMap_String_Addr2Line_newWithCapacity(size_t initialCapacity);

HashMap_String_Addr2Line *HashMap_String_Addr2Line_newWithLoadFactor(float loadFactor);

HashMap_String_Addr2Line *HashMap_String_Addr2Line_new();

void HashMap_String_Addr2Line_free(HashMap_String_Addr2Line *this);



Addr2Line * HashMap_String_Addr2Line_get(const HashMap_String_Addr2Line *this, const String * key);

Addr2Line * HashMap_String_Addr2Line_getOrDefault(const HashMap_String_Addr2Line *this, const String * key, const Addr2Line * defaultValue);



bool HashMap_String_Addr2Line_hasKey(const HashMap_String_Addr2Line *this, const String * key);

bool HashMap_String_Addr2Line_has(const HashMap_String_Addr2Line *this, const String * key, const Addr2Line * value);

bool HashMap_String_Addr2Line_hasValue(  const HashMap_String_Addr2Line *this, const Addr2Line * value);



Addr2Line * HashMap_String_Addr2Line_put(HashMap_String_Addr2Line *this, const String * key, const Addr2Line * value);

Addr2Line * HashMap_String_Addr2Line_putIfPresent(HashMap_String_Addr2Line *this, const String * key, const Addr2Line * value);

Addr2Line * HashMap_String_Addr2Line_putIfAbsent(HashMap_String_Addr2Line *this, const String * key, const Addr2Line * value);



Addr2Line * HashMap_String_Addr2Line_removeKey(HashMap_String_Addr2Line *this, const String * key);

bool HashMap_String_Addr2Line_remove(HashMap_String_Addr2Line *this, const String * key, const Addr2Line * value);

bool HashMap_String_Addr2Line_removeValue(HashMap_String_Addr2Line *this, const Addr2Line * value);



Addr2Line * HashMap_String_Addr2Line_replace(HashMap_String_Addr2Line *this, const String * key, const Addr2Line * value);

Addr2Line * HashMap_String_Addr2Line_replaceIfEquals(HashMap_String_Addr2Line *this, const String * key, const Addr2Line * oldValue, const Addr2Line * newValue);



void HashMap_String_Addr2Line_putAll(HashMap_String_Addr2Line *this, const HashMap_String_Addr2Line *map);

HashMap_String_Addr2Line *HashMap_String_Addr2Line_copy(const HashMap_String_Addr2Line *this);



bool HashMap_String_Addr2Line_equals(const HashMap_String_Addr2Line *map1, const HashMap_String_Addr2Line *map2);


#endif // HashMap_String_Addr2Line_H

    