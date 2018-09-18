//
// Created by Khyber on 9/16/2018.
//

#ifndef STACK_TRACE_H
#define STACK_TRACE_H

#include "StackFrame.h"

#include <stdbool.h>

#include "../string/String.h"
#include "../signal/Signal.h"

typedef struct StackTrace {
    const StackFrame* const frames;
    const size_t numFrames;
    const Signal *const signal;
} StackTrace;

bool StackTrace_init(StackTrace *stackTrace, const Signal *signal);

const StackTrace *StackTrace_new(const Signal *signal);

void StackTrace_free(const StackTrace *this);

void StackTrace_toString(const StackTrace *this, String* out);

void StackTrace_print(const StackTrace *this, FILE *out);

void StackTrace_printNow(FILE *out);

#endif // STACK_TRACE_H
