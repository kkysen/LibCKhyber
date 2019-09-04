//
// Created by Khyber on 10/23/2018.
//

#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <stdbool.h>

#include "src/main/stackTrace/stackTrace/StackTrace.h"

#define Exception_MAX_SIMULTANEOUS 1024

typedef struct Exception {
    const StackTrace *const stackTrace;
    const bool tooManyExceptions;
    const int code;
    const String *const name;
    void *const exception;
    void (*const free)(const void *exception);
    void (*const toString)(const void *exception, String *out);
    void (*const toFile)(const void *exception, FILE *out);
} Exception;

void Exception_clear(const Exception *this);

void Exception_free(const Exception *this);

bool tryCatch();

bool tryCatchException(const Exception **exception);

bool tryCatchExceptionMut(Exception **exception);

void __attribute__((noreturn)) throw(const Exception *exception);

void Exception_toString(const Exception *this, String *out);

void Exception_toFile(const Exception *this, FILE *out);

void Exception_print(const Exception *this);

#endif // EXCEPTION_H
