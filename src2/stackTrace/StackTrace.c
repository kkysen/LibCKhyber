//
// Created by Khyber on 9/16/2018.
//

#include "StackTrace.h"

#include <execinfo.h>
#include <string.h>

#include "../Addr2Line/Addr2Line.h"
#include "../programName/programName.h"

bool StackTrace_init(StackTrace* const stackTrace, const Signal* const signal) {
    #define MAX_STACK_FRAMES SIGSTKSZ
    static void* addresses[MAX_STACK_FRAMES];
    const int traceSize = backtrace(addresses, MAX_STACK_FRAMES);
    #undef MAX_STACK_FRAMES
    if (traceSize < 0) {
        perror("backtrace");
        return false;
    }
    const size_t numFrames = (size_t) traceSize;
    
    const char** const charMessages = (const char**) backtrace_symbols(addresses, traceSize);
    if (!charMessages) {
        perror("backtrace_symbols");
        return false;
    }
    
    const Addr2LineArgs addr2LineArgs = {
            .fileName = getProgramName(),
            // TODO
    };
    const Addr2Line* const addr2Line = Addr2Line_new(&addr2LineArgs);
    if (!addr2Line) {
        // malloc here too
        perror("Addr2Line_new");
        free(charMessages);
        return false;
    }
    
    StackFrame* const frames = malloc(sizeof(*frames) * numFrames);
    if (!frames) {
        // have to be especially careful with malloc here,
        // because this is probably being run when the program crashed,
        // and so it may be out of memory
        perror("malloc");
        Addr2Line_free(addr2Line);
        free(charMessages);
        return false;
    }
    
    for (size_t i = 0; i < numFrames; i++) {
        const String* const message = String_ofChars(charMessages[i]);
        Addr2Line_convert(addr2Line, frames + i, addresses + i, message);
    }
    
    free(charMessages);
    
    const StackTrace localStackTrace = {
            .numFrames = numFrames,
            .frames = frames,
            .signal = signal,
    };
    memcpy(stackTrace, &localStackTrace, sizeof(localStackTrace));
    return true;
}

const StackTrace* StackTrace_new(const Signal* const signal) {
    StackTrace* const stackTrace = malloc(sizeof(*stackTrace));
    if (!stackTrace) {
        perror("malloc");
        return NULL;
    }
    if (!StackTrace_init(stackTrace, signal)) {
        free(stackTrace);
        return NULL;
    }
    return stackTrace;
}

void StackTrace_free(const StackTrace* const this) {
    for (size_t i = 0; i < this->numFrames; i++) {
        StackTraceFrame_free(this->frames + i);
    }
    free((StackFrame*) this->frames);
    free((StackTrace*) this);
}

void StackTrace_toString(const StackTrace* const this, String* out) {
    if (this->signal) {
        // TODO clean up output format
        Signal_toString(this->signal, out);
    }
    for (size_t i = 0; i < this->numFrames; i++) {
        StackTraceFrame_toString(this->frames + i, out);
        String_appendLiteral(out, "\n");
    }
}

void StackTrace_print(const StackTrace* this, FILE* out) {
    String* const stringOut = String_ofSize(0);
    StackTrace_toString(this, stringOut);
    fputs(stringOut->chars, out);
    String_free(stringOut);
}

void StackTrace_printNow(FILE* out) {
    StackTrace this;
    StackTrace_init(&this, NULL);
    StackTrace_print(&this, out);
}