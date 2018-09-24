//
// Created by Khyber on 9/16/2018.
//

#include "StackFrame.h"

void StackFrame_clear(const StackFrame *const this) {
    if (this->ok && this->inlinedBy) {
        StackFrame_free(this->inlinedBy);
    }
    #define _free(field) String_free((String *) this->field)
    _free(message);
    if (!this->ok) {
        return;
    }
    _free(filePath);
    _free(fileName);
    _free(mangledFunctionName);
    _free(functionName);
    #undef _free
}

void StackFrame_free(const StackFrame *this) {
    StackFrame_clear(this);
    free((StackFrame *) this);
}

static const char *charsOrQuestionMarks(const String *const s) {
    return s ? s->chars : "??";
}

void StackFrame_toString(const StackFrame *const this, String *const out) {
    if (!this->ok) {
        String_append(out, this->message);
        return;
    }
    
    String_format(out, "%s%s: %s:%zu (%s:%zu)",
                  this->inlinedDepth ? "[inlined] " : "",
                  charsOrQuestionMarks(this->functionName),
                  charsOrQuestionMarks(this->fileName),
                  this->lineNumber,
                  charsOrQuestionMarks(this->filePath),
                  this->lineNumber
    );
}