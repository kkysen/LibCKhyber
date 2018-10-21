//
// Created by Khyber on 10/16/2018.
//

#ifndef FUNCTIONAL_H
#define FUNCTIONAL_H

#include <stdbool.h>

typedef void (*Runnable)();

typedef bool (*Equals)(const void *, const void *);

#define Equals_(Equals, T) bool (*(Equals))(const T, const T)

typedef int (*Compare)(const void *, const void *);

#define Compare_(Compare, T) int (*(Compare))(const T, const T)

typedef void (*Consumer)(void *);

#define Consumer_(Consumer, T) void (*(Consumer))(T)

#define Function_(Function, T, R) R (*(Function))(T)

#endif // FUNCTIONAL_H
