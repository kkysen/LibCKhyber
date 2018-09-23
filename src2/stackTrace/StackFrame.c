//
// Created by Khyber on 9/16/2018.
//

#include "StackFrame.h"

void StackFrame_free(const StackFrame *const this) {
    if (this->ok) {
        free((StackFrame *) this->inlined);
    }
    #define free(field) String_free((String *) this->field)
    free(message);
    if (!this->ok) {
        return;
    }
    free(filePath);
    free(fileName);
    free(mangledFunctionName);
    free(functionName);
    #undef free
}

static const char *charsOrQuestionMarks(const String *const s) {
    return s ? s->chars : "??";
}

void StackFrame_toString(const StackFrame *const this, String *const out) {
    if (!this->ok) {
        String_format(out, "%p: %s", this->address, this->message->chars);
        return;
    }
    
    String_format(out, "%s: %s:%zu (%s:%zu)",
                  charsOrQuestionMarks(this->functionName),
                  charsOrQuestionMarks(this->fileName),
                  this->lineNumber,
                  charsOrQuestionMarks(this->filePath),
                  this->lineNumber
    );
    
    if (this->inlined) {
        // TODO should this come before or after rest of toString()
        StackFrame_toString(this->inlined, out);
    }
}