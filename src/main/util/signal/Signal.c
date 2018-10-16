//
// Created by Khyber on 9/17/2018.
//

#include "src/main/util/signal/Signal.h"

#define SIGNAL_MSG_SIZE_OVERESTIMATE 50

#define printSignal(signal, message) \
    { \
        String_appendChars(out, signal); \
        String_appendChars(out, ": "); \
        String_appendChars(out, message); \
        break; \
    }

#define catchSignal(signal, message) case signal: printSignal(#signal, message)

#define catchSub(signal, subSignal, message) \
    case subSignal: { \
        String_appendChars(out, #signal); \
        String_appendChars(out, " ("); \
        String_appendChars(out, #subSignal); \
        String_appendChars(out, "): "); \
        String_appendChars(out, message); \
        break; \
    }

#define catch_FPE(subSignal, message) catchSub(SIGFPE, subSignal, message)
#define catch_ILL(subSignal, message) catchSub(SIGILL, subSignal, message)

/**
 * Catch the actual signal and append a message to the String \param out.
 *
 * @param signal the signal caught
 * @param code the siginfo->si_code of the signal caught
 * @param out the String to append the message to
 */
static void catchSignalAndPrintMessage(int signal, int code, String *const out) {
    switch (signal) {
        catchSignal(SIGSEGV, "Segmentation Fault");
        catchSignal(SIGINT, "Interrupt: Interactive attention signal, usually Ctrl+C");
        catchSignal(SIGTERM, "Termination: a termination request was sent to the program");
        catchSignal(SIGABRT, "Abort: usually caused by an abort() or assert()");
        catchSignal(SIGALRM, "Alarm");
//        catch_signal(SIGQUIT, "Quit");
        catchSignal(SIGTSTP, "Terminal stop");
        case SIGFPE:
            switch (code) {
                catch_FPE(FPE_INTDIV, "integer division by zero");
                catch_FPE(FPE_INTOVF, "integer overflow");
                catch_FPE(FPE_FLTDIV, "floating-point division by zero");
                catch_FPE(FPE_FLTUND, "floating-point overflow");
                catch_FPE(FPE_FLTRES, "floating-point underflow");
                catch_FPE(FPE_FLTINV, "floating-point inexact result");
                catch_FPE(FPE_FLTSUB, "subscript out of range");
                default: printSignal("SIGFPE", "Arithmetic Exception");
            }
            break;
        case SIGILL:
            switch (code) {
                catch_ILL(ILL_ILLOPC, "illegal opcode");
                catch_ILL(ILL_ILLOPN, "illegal operand");
                catch_ILL(ILL_ILLADR, "illegal addressing mode");
                catch_ILL(ILL_ILLTRP, "illegal trap");
                catch_ILL(ILL_PRVOPC, "privileged opcode");
                catch_ILL(ILL_PRVREG, "privileged register");
                catch_ILL(ILL_COPROC, "coprocessor stackTrace");
                catch_ILL(ILL_BADSTK, "internal stack stackTrace");
                default: printSignal("SIGILL", "Illegal Instruction");
            }
            break;
        default: printSignal("Unknown Signal", "Unknown Cause");
    }
}

void Signal_toString(const Signal *const this, String *const out) {
    String_ensureMoreCapacity(out, SIGNAL_MSG_SIZE_OVERESTIMATE);
    catchSignalAndPrintMessage(this->signal, this->sigInfo->si_code, out);
}