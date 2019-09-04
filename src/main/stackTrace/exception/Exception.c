//
// Created by Khyber on 10/23/2018.
//

#include "Exception.h"

#include <setjmp.h>

#include "src/main/util/utils.h"

void Exception_clear(const Exception *const this) {
    if (this->exception && this->free) {
        this->free(this->exception);
    }
    StackTrace_free(this->stackTrace);
}

void Exception_free(const Exception *this) {
    if (!this) {
        return;
    }
    Exception_clear(this);
    freeConst(this);
}

bool tryCatch() {
    const Exception *exception = NULL;
    const bool success = tryCatchException(&exception);
    Exception_free(exception);
    return success;
}

// thread local b/c belong to call stack
static __thread jmp_buf jmpBuffers[Exception_MAX_SIMULTANEOUS] = {};
static __thread u32 numJmpBuffers = 0;
static __thread Exception exceptionStack[Exception_MAX_SIMULTANEOUS] = {};

static const Exception Exception_tooManyExceptionsException = {
        .stackTrace = NULL,
        .tooManyExceptions = true,
        .code = 0,
        .exception = NULL,
        .free = NULL,
        .toString = NULL,
        .toFile = NULL,
};

bool tryCatchException(const Exception **const exception) {
    if (numJmpBuffers > Exception_MAX_SIMULTANEOUS) {
        *exception = &Exception_tooManyExceptionsException;
        return true;
    }
    const u32 jmpBufferNum = numJmpBuffers++;
    pz(jmpBufferNum);
    jmp_buf *jmpBuf = jmpBuffers + jmpBufferNum;
    const i32 val = setjmp(*jmpBuf);
    if (val == 0) {
        *exception = NULL;
        return false;
    }
    if (((u32) val) - 1 == jmpBufferNum) {
        *exception = exceptionStack + jmpBufferNum;
        return true;
    }
    // TODO FIXME jmpBufferNum changes after longjmp, same value across multiple runs
    perror("Exception handling broken");
    fprintf(stderr, "jmpBufferNum: %u != %u\n", ((u32) val) - 1, jmpBufferNum);
    exit(1);
}

bool tryCatchExceptionMut(Exception **const exception) {
    return tryCatchException((const Exception **) exception);
}

static const Exception *Exception_copy(const Exception *const this, const StackTrace *const stackTrace) {
    Exception *const copy = malloc(sizeof(*this));
    if (!copy) {
        perror("malloc");
        return NULL;
        // TODO what should happen here
    }
    memcpy(copy, this, sizeof(*this));
    if (copy->stackTrace) {
        StackTrace_free(copy->stackTrace);
    }
    setField(copy->stackTrace, stackTrace);
    return copy;
}

void __attribute__((noreturn)) throw (const Exception *exception) {
    // don't catch signals, should crash on SIGSEGV
    exception = Exception_copy(exception, StackTrace_new(NULL));
    if (numJmpBuffers == 0) {
        Exception_toFile(exception, stderr);
        exit(exception->code);
    }
    const u32 jmpBufferNum = numJmpBuffers - 1;
    memcpy(exceptionStack + jmpBufferNum, exception, sizeof(*exception));
    longjmp(jmpBuffers[jmpBufferNum], jmpBufferNum);
}

void Exception_toString(const Exception *const this, String *const out) {
    String_format(out, "Exception: %s (error code = %d)\n",
                  this->name ? this->name->chars : "[unnamed]", this->code);
    if (this->toString) {
        this->toString(this, out);
    }
    if (this->stackTrace) {
        // TODO check newlines b/w
        StackTrace_toString(this->stackTrace, out);
    }
}

void Exception_toFile(const Exception *const this, FILE *const out) {
    if (!this->toFile) {
        String stringOut = String_onStackOfSize(0);
        Exception_toString(this, &stringOut);
        String_toFile(&stringOut, out);
        String_clear(&stringOut);
    } else {
        fprintf(out, "Exception: %s (error code = %d)\n",
                this->name ? this->name->chars : "[unnamed]", this->code);
        this->toFile(this->exception, out);
        if (this->stackTrace) {
            // TODO check newlines b/w
            StackTrace_toFile(this->stackTrace, out);
        }
    }
}

void Exception_print(const Exception *const this) {
    Exception_toFile(this, stdout);
}