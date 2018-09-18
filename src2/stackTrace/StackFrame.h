//
// Created by Khyber on 9/16/2018.
//

#ifndef STACK_TRACE_FRAME_H
#define STACK_TRACE_FRAME_H

#include <stdbool.h>
#include "../string/String.h"

typedef struct StackFrame {
    const void *address;
    const String *message;
    
    bool ok;
    const String *fileName;
    const String *mangledFunctionName;
    const String *functionName;
    size_t lineNumber;
    bool isInlined;
} StackFrame;

void StackTraceFrame_free(const StackFrame* this);

void StackTraceFrame_toString(const StackFrame* this, String* out);

#endif // STACK_TRACE_FRAME_H
