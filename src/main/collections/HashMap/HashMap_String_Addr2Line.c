

#include "src/main/collections/HashMap/HashMap_String_Addr2Line.h"

#include <string.h>

static const size_t HashMap_String_Addr2Line_defaultInitialCapacity = 1u << 4u;

static const float HashMap_String_Addr2Line_defaultLoadFactor = 0.75f;



static size_t HashMap_String_Addr2Line_capacityFor(size_t size);

static size_t HashMap_String_Addr2Line_index(size_t hash);



static void HashMap_String_Addr2Line_resize(HashMap_String_Addr2Line *this);

static Addr2Line * HashMap_String_Addr2Line_putNode(HashMap_String_Addr2Line *this, const HashMapNode_String_Addr2Line *node, bool onlyIfAbsent, bool evict);



static bool HashMap_String_Addr2Line_keyEquals(const String * key1, const String * key2);

static bool HashMap_String_Addr2Line_valueEquals(const Addr2Line * value1, const Addr2Line * value2);



static void HashMapNode_String_Addr2Line_clear(HashMapNode_String_Addr2Line *this);

static bool HashMapNode_String_Addr2Line_keyEquals(const HashMapNode_String_Addr2Line *node1, const HashMapNode_String_Addr2Line *node2);



static bool HashMap_String_Addr2Line_keyEquals(const String * const key1, const String * const key2) {
    return key1 == key2 || (String_equals(key1, key2));
}

static bool HashMap_String_Addr2Line_valueEquals(const Addr2Line * const value1, const Addr2Line * const value2) {
    return value1 == value2 || ((u64) value1->fd == (u64) value2->fd);
}



static void HashMapNode_String_Addr2Line_clear(HashMapNode_String_Addr2Line *const this) {
    // TODO fix and free String and Addr2Line
    if (this->next) {
        HashMapNode_String_Addr2Line_clear(this->next);
    }
}

static bool HashMapNode_String_Addr2Line_keyEquals(const HashMapNode_String_Addr2Line *const node1, const HashMapNode_String_Addr2Line *const node2) {
    return node1->hash == node2->hash && HashMap_String_Addr2Line_keyEquals(node1->key, node2->key);
}



static size_t HashMap_String_Addr2Line_capacityFor(const size_t size) {
    const u8 leadingBitIndex = sizeof(size) * 8 - __builtin_clz(size);
    const size_t capacity = 1u << leadingBitIndex;
    return capacity == size ? capacity : capacity << 1u; // when size is a power of 2
}

#define FIBONACCI_FACTOR 11400714819323198485LLU // = (1u << 64) / phi

static size_t HashMap_String_Addr2Line_index(size_t hash) {
    const u8 shiftAmount = 0; // TODO
    hash ^= hash >> shiftAmount;
    return (11400714819323198485LLU * hash) >> shiftAmount;
}

#undef FIBONACCI_FACTOR



static void HashMap_String_Addr2Line_resize(HashMap_String_Addr2Line *const this) {
    size_t oldCapacity = this->capacity;
//    size_t newCapacity = 0;
    if (oldCapacity > 0) {
//        newCapacity = oldCapacity << 1u;
        return;
    }
}



// node is meant to be stack allocated
static Addr2Line * HashMap_String_Addr2Line_putNode(HashMap_String_Addr2Line *const this, const HashMapNode_String_Addr2Line *const node, const bool onlyIfAbsent, const bool evict) {
    if (!this->table || this->capacity == 0) {
        HashMap_String_Addr2Line_resize(this);
    }
    const size_t i = (this->capacity - 1) & node->hash;
    HashMapNode_String_Addr2Line *const head = this->table + i;
    if (!head) {
        memcpy(head, node, sizeof(*node));
    } else {
        return NULL;
        HashMapNode_String_Addr2Line *e;
        if (HashMapNode_String_Addr2Line_keyEquals(node, head)) {
            e = head;
        } else {
            for (HashMapNode_String_Addr2Line *e = head->next; e; e = e->next) {
            
            }
            for (;;) {
                if (!(e = head->next)) {
                    head->next = malloc(sizeof(*node));
                    memcpy(head->next, node, sizeof(*node));
                    break;
                }
                if (HashMapNode_String_Addr2Line_keyEquals(node, e)) {
                    break;
                }
                // head = e;
            }
        }
    }
    
    if (++this->size > this->resizeThreshold) {
        HashMap_String_Addr2Line_resize(this);
    }
    return NULL;
}



void HashMap_String_Addr2Line_initWithCapacityAndLoadFactor(HashMap_String_Addr2Line *const this, const size_t initialCapacity, const float loadFactor) {
    this->size = 0;
    this->capacity = 0;
    this->loadFactor = loadFactor;
    this->resizeThreshold = HashMap_String_Addr2Line_capacityFor(initialCapacity);
    this->table = NULL;
}

void HashMap_String_Addr2Line_initWithCapacity(HashMap_String_Addr2Line *const this, const size_t initialCapacity) {
    HashMap_String_Addr2Line_initWithCapacityAndLoadFactor(this, initialCapacity, HashMap_String_Addr2Line_defaultLoadFactor);
}

void HashMap_String_Addr2Line_initWithLoadFactor(HashMap_String_Addr2Line *const this, const float loadFactor) {
    HashMap_String_Addr2Line_initWithCapacityAndLoadFactor(this, HashMap_String_Addr2Line_defaultInitialCapacity, loadFactor);
}

void HashMap_String_Addr2Line_init(HashMap_String_Addr2Line *const this) {
    HashMap_String_Addr2Line_initWithCapacity(this, HashMap_String_Addr2Line_defaultInitialCapacity);
}

void HashMap_String_Addr2Line_clear(HashMap_String_Addr2Line *const this) {
    for (size_t i = 0; i < this->capacity; i++) {
        HashMapNode_String_Addr2Line_clear(this->table + i);
    }
    
    free(this->table);
    this->table = NULL;
    this->size = 0;
    this->resizeThreshold = 0; // TODO check
    this->loadFactor = 0; // TODO check
}



HashMap_String_Addr2Line *HashMap_String_Addr2Line_newWithCapacityAndLoadFactor(const size_t initialCapacity, const float loadFactor) {
    HashMap_String_Addr2Line *const this = malloc(sizeof(*this));
    HashMap_String_Addr2Line_initWithCapacityAndLoadFactor(this, initialCapacity, loadFactor);
    return this;
}

HashMap_String_Addr2Line *HashMap_String_Addr2Line_newWithCapacity(const size_t initialCapacity) {
    return HashMap_String_Addr2Line_newWithCapacityAndLoadFactor(initialCapacity, HashMap_String_Addr2Line_defaultLoadFactor);
}

HashMap_String_Addr2Line *HashMap_String_Addr2Line_newWithLoadFactor(const float loadFactor) {
    return HashMap_String_Addr2Line_newWithCapacityAndLoadFactor(HashMap_String_Addr2Line_defaultInitialCapacity, loadFactor);
}

HashMap_String_Addr2Line *HashMap_String_Addr2Line_new() {
    return HashMap_String_Addr2Line_newWithCapacity(HashMap_String_Addr2Line_defaultInitialCapacity);
}

void HashMap_String_Addr2Line_free(HashMap_String_Addr2Line *const this) {
    if (this) {
        HashMap_String_Addr2Line_clear(this);
        free(this);
    }
}



Addr2Line * HashMap_String_Addr2Line_get(const HashMap_String_Addr2Line *const this, const String * const key) {
    return NULL;
}

Addr2Line * HashMap_String_Addr2Line_getOrDefault(const HashMap_String_Addr2Line *const this, const String * const key, const Addr2Line * const defaultValue) {
    return NULL;
}



bool HashMap_String_Addr2Line_hasKey(const HashMap_String_Addr2Line *const this, const String * const key) {
    return false;
}

bool HashMap_String_Addr2Line_has(const HashMap_String_Addr2Line *const this, const String * const key, const Addr2Line * const value) {
    return false;
}

bool HashMap_String_Addr2Line_hasValue(const HashMap_String_Addr2Line *const this, const Addr2Line * const value) {
    return false;
}



Addr2Line * HashMap_String_Addr2Line_put(HashMap_String_Addr2Line *const this, const String * const key, const Addr2Line * const value) {
    return NULL;
}

Addr2Line * HashMap_String_Addr2Line_putIfPresent(HashMap_String_Addr2Line *const this, const String * const key, const Addr2Line * const value) {
    return NULL;
}

Addr2Line * HashMap_String_Addr2Line_putIfAbsent(HashMap_String_Addr2Line *const this, const String * const key, const Addr2Line * const value) {
    return NULL;
}



Addr2Line * HashMap_String_Addr2Line_removeKey(HashMap_String_Addr2Line *const this, const String * const key) {
    return NULL;
}

bool HashMap_String_Addr2Line_remove(HashMap_String_Addr2Line *const this, const String * const key, const Addr2Line * const value) {
    return false;
}

bool HashMap_String_Addr2Line_removeValue(HashMap_String_Addr2Line *const this, const Addr2Line * const value) {
    return false;
}



Addr2Line * HashMap_String_Addr2Line_replace(HashMap_String_Addr2Line *const this, const String * const key, const Addr2Line * const value) {
    return NULL;
}

Addr2Line * HashMap_String_Addr2Line_replaceIfEquals(HashMap_String_Addr2Line *const this, const String * const key, const Addr2Line * const oldValue, const Addr2Line * const newValue) {
    return NULL;
}



void HashMap_String_Addr2Line_putAll(HashMap_String_Addr2Line *const this, const HashMap_String_Addr2Line *const map) {
    for (size_t i = 0; i < map->capacity; i++) {
        for (const HashMapNode_String_Addr2Line *node = map->table + i; node; node = node->next) {
            HashMap_String_Addr2Line_putNode(this, node, false, true);
        }
    }
}

HashMap_String_Addr2Line *HashMap_String_Addr2Line_copy(const HashMap_String_Addr2Line *const this) {
    HashMap_String_Addr2Line *copy = HashMap_String_Addr2Line_newWithCapacityAndLoadFactor(this->capacity, this->loadFactor);
    HashMap_String_Addr2Line_putAll(copy, this);
    return copy;
}



bool HashMap_String_Addr2Line_equals(const HashMap_String_Addr2Line *const map1, const HashMap_String_Addr2Line *const map2) {
    for (size_t i = 0; i < map1->capacity; i++) {
        for (const HashMapNode_String_Addr2Line *node = map1->table + i; node; node = node->next) {
            if (!HashMap_String_Addr2Line_has(map2, node->key, node->value)) {
                return false;
            }
        }
    }
    return true;
}

    