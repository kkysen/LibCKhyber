//
// Created by Khyber on 9/16/2018.
//

#include "StackFrame.h"

void StackTraceFrame_free(const StackFrame* const this) {
    #define free(field) String_free((String *) this->field)
    free(message);
    free(fileName);
    free(mangledFunctionName);
    free(functionName);
    String_free((String *) this->message);
    #undef free
}

void StackTraceFrame_toString(const StackFrame* const this, String* const out) {
    if (!this->ok) {
        String_format(out, "%p: %s", this->address, this->message->chars);
        return;
    }
    
    // TODO
}