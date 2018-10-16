//
// Created by Khyber on 9/25/2018.
//

#ifndef FNV1A_H
#define FNV1A_H

#include <stdlib.h>

#include "src/main/util/numbers.h"

u64 fnv1a64Hash(const void *bytes, size_t size);

#endif // FNV1A_H
