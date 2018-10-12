//
// Created by Khyber on 9/16/2018.
//

#include "StackTrace.h"

#include <execinfo.h>
#include <string.h>
#include <syscall.h>

#include "../../stackTrace/addr2Line/Addr2Line.h"
#include "../../util/programName/programName.h"
#include "../../util/utils.h"

bool StackTrace_initToDepth(StackTrace *const this, const Signal *const signal, const stack_size_t maxDepth) {
    static void *addresses[STACK_SIZE_MAX];
    const int traceSize = backtrace(addresses, STACK_SIZE_MAX);
    if (traceSize < 0) {
        perror("backtrace");
        return false;
    }
    const stack_size_t shift = 0; // TODO remove
    const stack_size_t actualNumFrames = (stack_size_t) (traceSize - shift);
    const stack_size_t numFrames = min(actualNumFrames, maxDepth);
    
    const char **const charMessages = (const char **) backtrace_symbols(addresses, (int) numFrames);
    if (!charMessages) {
        perror("backtrace_symbols");
        return false;
    }
    
    const Addr2LineArgs addr2LineArgs = {
            .filePath = getProgramName(),
            // TODO
    };
    const Addr2Line *const addr2Line = Addr2Line_new(&addr2LineArgs);
    if (!addr2Line) {
        // malloc here too
        perror("Addr2Line_new");
        free(charMessages);
        return false;
    }
    
    StackFrame *const frames = malloc(sizeof(*frames) * numFrames);
    if (!frames) {
        // have to be especially careful with malloc here,
        // because this is probably being run when the program crashed,
        // and so it may be out of memory
        perror("malloc");
        Addr2Line_free(addr2Line);
        free(charMessages);
        return false;
    }
    
    stack_size_t totalNumFrames = 0;
    for (stack_size_t i = 0; i < numFrames; i++) {
        const String *const message = String_ofChars(charMessages[i]);
        StackFrame *const frame = frames + i;
        Addr2Line_convert(addr2Line, frame, addresses[i + shift], message);
        totalNumFrames += 1 + frame->inlinedDepth;
    }
    
    Addr2Line_free(addr2Line);
    free(charMessages);
    
    const StackTrace localStackTrace = {
            .maxFrames = actualNumFrames,
            .numFrames = numFrames,
            .totalNumFrames = totalNumFrames,
            .frames = frames,
            .signal = signal,
            .processId = getpid(),
            .threadId = (pid_t) syscall(SYS_gettid),
    };
    memcpy(this, &localStackTrace, sizeof(localStackTrace));
    return true;
}

bool StackTrace_init(StackTrace *const stackTrace, const Signal *const signal) {
    return StackTrace_initToDepth(stackTrace, signal, STACK_SIZE_MAX);
}

const StackTrace *StackTrace_newToDepth(const Signal *const signal, const stack_size_t maxDepth) {
    StackTrace *const stackTrace = malloc(sizeof(*stackTrace));
    if (!stackTrace) {
        perror("malloc");
        return NULL;
    }
    if (!StackTrace_initToDepth(stackTrace, signal, maxDepth)) {
        free(stackTrace);
        return NULL;
    }
    return stackTrace;
}

const StackTrace *StackTrace_new(const Signal *const signal) {
    return StackTrace_newToDepth(signal, STACK_SIZE_MAX);
}

void StackTrace_clear(const StackTrace *const this) {
    for (stack_size_t i = 0; i < this->numFrames; i++) {
        StackFrame_clear(this->frames + i);
    }
    free((StackFrame *) this->frames);
}

void StackTrace_free(const StackTrace *const this) {
    StackTrace_clear(this);
    free((StackTrace *) this);
}

static void StackTraceFrame_toString(const StackFrame *const this, String *const out) {
    String_appendLiteral(out, "\t");
    StackFrame_toString(this, out);
    String_appendNewLine(out);
}

static bool StackWalker_frameToString(
        const StackFrame *frame, stack_size_t ATTRIBUTE_UNUSED i,
        const StackTrace *ATTRIBUTE_UNUSED this, void *arg) {
    StackTraceFrame_toString(frame, (String *) arg);
    return true;
}

void StackTrace_toString(const StackTrace *const this, String *out) {
    // over malloc in one malloc, instead of many small, exact malloc's
    static const size_t declarationSizeEstimate = 50;
    static const size_t signalSizeEstimate = 50;
    static const size_t frameSizeEstimate = 150;
    const size_t sizeEstimate = (size_t) 1.2 * (
            +declarationSizeEstimate
            + (this->signal ? signalSizeEstimate : 0)
            + frameSizeEstimate * this->totalNumFrames
    );
    String_ensureMoreCapacity(out, sizeEstimate);
    
    String_format(out, "\n\n[pid=%d][tid=%d] StackTrace\n", this->processId, this->threadId);
    if (this->signal) {
        String_appendLiteral(out, "Caused By: ");
        Signal_toString(this->signal, out);
        String_appendNewLine(out);
    }
    
    StackTrace_walkArg(this, StackWalker_frameToString, out);
    
    String_shrinkToSize(out); // trim extra malloc'd memory
}

void StackTrace_print(const StackTrace *this, FILE *out) {
    String *const stringOut = String_empty();
    StackTrace_toString(this, stringOut);
    fputs(stringOut->chars, out);
    String_free(stringOut);
}

void StackTrace_printNow(FILE *out) {
    StackTrace this;
    StackTrace_init(&this, NULL);
    StackTrace_print(&this, out);
    StackTrace_clear(&this);
}

void StackTrace_walkArg(const StackTrace *this, StackWalkerArg walker, void *arg) {
    for (stack_size_t i = 0, frameNum = 0; i < this->numFrames; i++) {
        for (const StackFrame *frame = this->frames + i; frame; frame = frame->inlinedBy) {
            if (!walker(frame, frameNum++, this, arg)) {
                return;
            }
        }
    }
}

void StackTrace_walk(const StackTrace *this, StackWalker walker) {
    for (stack_size_t i = 0; i < this->numFrames; i++) {
        for (const StackFrame *frame = this->frames + i; frame; frame = frame->inlinedBy) {
            if (!walker(frame, i, this)) {
                return;
            }
        }
    }
}