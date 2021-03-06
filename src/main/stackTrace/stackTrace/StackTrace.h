//
// Created by Khyber on 9/16/2018.
//

#ifndef STACK_TRACE_H
#define STACK_TRACE_H

#include <stdbool.h>

#include "src/main/stackTrace/stackTrace/stack_size_t.h"
#include "src/main/stackTrace/stackTrace/StackFrame.h"
#include "src/main/string/String.h"
#include "src/main/util/signal/Signal.h"

typedef struct StackTrace {
    const stack_size_t maxFrames;
    const StackFrame *const frames;
    const stack_size_t numFrames;
    const stack_size_t totalNumFrames; // includes inlined frames
    const Signal *const signal;
    const int errorNum;
    const pid_t processId;
    const pid_t threadId;
} StackTrace;

bool StackTrace_initToDepth(StackTrace *stackTrace, const Signal *signal, stack_size_t maxDepth);

bool StackTrace_init(StackTrace *stackTrace, const Signal *signal);

const StackTrace *StackTrace_newToDepth(const Signal *signal, stack_size_t maxDepth);

const StackTrace *StackTrace_new(const Signal *signal);

void StackTrace_clear(const StackTrace *this);

void StackTrace_free(const StackTrace *this);

void StackTrace_toString(const StackTrace *this, String *out);

void StackTrace_toFile(const StackTrace *this, FILE *out);

void StackTrace_printNow();

typedef bool (*const StackWalkerArg)(const StackFrame *frame, stack_size_t i, const StackTrace *this, void *arg);

typedef bool (*const StackWalker)(const StackFrame *frame, stack_size_t i, const StackTrace *this);

void StackTrace_walkArg(const StackTrace *this, StackWalkerArg walker, void *arg);

void StackTrace_walk(const StackTrace *this, StackWalker walker);

#endif // STACK_TRACE_H
