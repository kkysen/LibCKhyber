//
// Created by Khyber on 9/16/2018.
//

#ifndef STACK_TRACE_FRAME_H
#define STACK_TRACE_FRAME_H

#include <stdbool.h>

#include "src/main/stackTrace/stackTrace/stack_size_t.h"
#include "src/main/string/String.h"

typedef struct StackFrame StackFrame;

struct StackFrame {
    const void *address;
    const String *message;
    
    bool ok;
    const String *filePath;
    const String *fileName;
    const String *mangledFunctionName;
    const String *functionName;
    size_t lineNumber;
    
    stack_size_t inlinedDepth;
    const StackFrame *inlinedBy;
};

void StackFrame_clear(const StackFrame *this);

void StackFrame_free(const StackFrame *this);

void StackFrame_toString(const StackFrame *this, String *out);

#endif // STACK_TRACE_FRAME_H
