//
// Created by Khyber on 11/8/2017.
//

#include "stackTrace.h"

#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include <stdbool.h>
#include <stdint-gcc.h>

#include "../util/utils.h"
#include "../string/String.h"
#include "addr2Line.h"
#include "../programName.h"

#ifdef __linux__

#include <execinfo.h>
//#include <bits/sigstack.h>
#endif

int stackTraceLevel = 0;

Runnable preStackTrace = NULL;
Runnable postStackTrace = NULL;

static int runAddr2LineStatically(const void* const* const addresses, const size_t numAddresses, String* const out) {
    const String programName = getProgramName();
    const Addr2LineOptions options = {
            .demangleNames = true,
            .prettyPrint = true,
            .showAddresses = true,
            .showBaseNames = true,
            .showFunctions = true,
            .showInlinedFunctions = true,
            .fileName = &programName,
            .addresses = addresses,
            .numAddresses = numAddresses,
    };
    return addr2Line(&options, out) == NONE ? 0 : -1;
}

static String* getAddr2LineCommandBase() {
    #ifdef __APPLE__
    #define addr2line_base "atos -o "
    #else
    #define addr2LineBase "addr2line -f -s -p -e "
    #endif
    
    static String* base = NULL;
    if (base) {
        return String_copy(*base);
    }
    
    base = String_ofSize(arrayLen(addr2LineBase) + PATH_MAX + arrayLen(" ") + PTR_MAX_STRLEN);
    String_appendLiteral(base, addr2LineBase);
    String_append(base, getProgramName());
    String_appendLiteral(base, " ");
    String_shrinkToSize(base);
    return getAddr2LineCommandBase();
}

static String* getAddr2LineCommand(const void* const* const addresses, const size_t numAddresses) {
    String* const command = getAddr2LineCommandBase();
    for (size_t i = 0; i < numAddresses; ++i) {
        String_format(command, "%p", addresses[i]);
        String_appendLiteral(command, " ");
    }
    return command;
}

/**
 * Use the program addr2line to convert the backtraced symbol address to
 * the file, function, and line number in the stacktrace,
 * appending the output to \param out.
 *
 * @param address the address in the executable to find the line number of
 * @param out the String to append the line number, etc. message to
 * @return -1 if error, else the exit status of the popen() call to the addr2line program
 */
static ssize_t runAddr2LineCommandLineDirectly(const char* const command, String* const out) {
    FILE* const output = popen(command, "r");
    if (!output) {
        perror("popen");
        return -1;
    }
    String_appendChars(out, "    ");
    const size_t streamedBytes = String_appendStream(out, output);
    if (streamedBytes == 0) {
        // if popen() doesn't work for some reason, at least use system
        printf("    ");
        if (system(command) == -1) {
            perror("system");
        }
    }
    const int retVal = pclose(output);
    if (retVal == -1) {
        return -1;
    }
    if (WEXITSTATUS(retVal) != 0) { // NOLINT
        return -1;
    }
    return streamedBytes;
}

static ssize_t
runAddr2LineCommandLine(const void* const* const addresses, const size_t numAddresses, String* const out) {
    String* const addr2LineCommand = getAddr2LineCommand(addresses, numAddresses);
    const ssize_t retVal = runAddr2LineCommandLineDirectly(addr2LineCommand->chars, out);
    String_free(addr2LineCommand);
    return retVal;
}

static ssize_t runAddr2Line(const void* const* const addresses, const size_t numAddresses, String* const out) {
    if (ADDR2LINE_IMPLEMENTED) {
        const retVal = runAddr2LineStatically(addresses, numAddresses, out);
        if (retVal == 0) {
            return 0;
        }
    }
    return runAddr2LineCommandLine(addresses, numAddresses, out);
}

// header for builtin func
int backtrace(void** buffer, int size);

// header for builtin func
char** backtrace_symbols(void* const* buffer, int size);

#define MAX_STACK_FRAMES SIGSTKSZ

static void* stackTraces[MAX_STACK_FRAMES];

#define AVG_ADDR_2_LINE_LENGTH 40

/**
 * Print the stacktrace of a thread to stderr, assuming a POSIX system
 * (i.e. backtrace() and backtrace_symbols() exists).
 *
 * Print the process IDs in the front as [pid : ppid].
 *
 * @param out the String to append the stacktrace to before printing to stderr
 */
static void posixPrintStackTrace(String* const out) {
    const int traceSize = backtrace(stackTraces, MAX_STACK_FRAMES);
    if (traceSize < 0) {
        perror("backtrace");
        return;
    }
    const size_t uTraceSize = (size_t) traceSize;
//    pd(trace_size);
//    debug();
    String_ensureMoreCapacity(out, (size_t) (traceSize + 1) * AVG_ADDR_2_LINE_LENGTH);
    String_appendChars(out, "Stacktrace:\n");
//    debug();
    const char** const messages = (const char**) backtrace_symbols(stackTraces, traceSize);
//    debug();
    if (!messages) {
        perror("backtrace_symbols(stack_traces, trace_size)");
        String_clear(out);
        return;
    }
    size_t totalStreamedBytes = 0;
    const ssize_t streamedBytes = runAddr2Line(stackTraces, uTraceSize, out);
    for (int32_t i = 0; i < uTraceSize; ++i) {
        
        if (streamedBytes == -1) {
            fprintf(stderr, "\tstackTrace determining line # for: %s\n", messages[i]);
        } else {
            totalStreamedBytes += streamedBytes;
        }
//        ps(sb->chars);
    }
//    debug();
//    ps(sb->chars);
//    debug();
    
    // fprintf(stderr) hangs and raises SIGSEGV sometimes, so I'm using printf
//    fprintf(stderr, "\n[%d : %d]\n%s\n", getpid(), getppid(), sb->chars);
//    fflush(stderr);
    if (totalStreamedBytes > 0) {
        printf("\n[%d : %d]\n%s\n", getpid(), getppid(), out->chars);
    }
//    debug();
    String_clear(out);
    free(messages);
//    debug();
}

static String* getStackTraceString() {
    static String* stacktraceString = NULL;
    if (!stacktraceString) {
        stacktraceString = String_ofSize(1024);
    }
    return stacktraceString;
}

void printStackTrace() {
    posixPrintStackTrace(getStackTraceString());
}

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
static void catchSignalAndPrintMessage(int signal, int code, String* const out) {
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
                catch_FPE(FPE_INTDIV, "integer divide by zero");
                catch_FPE(FPE_INTOVF, "integer overflow");
                catch_FPE(FPE_FLTDIV, "floating-point divide by zero");
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

/**
 * A signal handler that prints the current stacktrace to stderr.
 *
 * @param signal the signal caught
 * @param sigInfo extra info about the signal caught
 * @param context extra context about the signal caught
 */
static void stackTraceSignalHandlerPosix(int signal, siginfo_t* sigInfo, void* context) {
    if (stackTraceLevel != 0) {
        perror("Recursive signal raised in stacktrace handler");
        _Exit(1);
    }
    stackTraceLevel++;
    if (preStackTrace) {
        preStackTrace();
    }
    String* const out = getStackTraceString();
    String_ensureMoreCapacity(out, SIGNAL_MSG_SIZE_OVERESTIMATE);
    String_appendChars(out, "Caught ");
    catchSignalAndPrintMessage(signal, sigInfo->si_code, out);
    String_appendChars(out, "\n");
//    debug();
    posixPrintStackTrace(out);
//    debug();
    if (postStackTrace) {
        postStackTrace();
    }
    stackTraceLevel--;
    *((char*) context) = 0;
    exit(EXIT_FAILURE);
}

#undef catch_ILL
#undef catch_FPE
#undef catchSub
#undef catchSignal
#undef printSignal

#define addAction(signal) addSigAction(signal, &sigAction)

void setStackTraceSignalHandler() {
    {
        static uint8_t alternateStack[SIGSTKSZ];
        // setup alternate stack
        stack_t ss = {.ss_sp = alternateStack, .ss_size = SIGSTKSZ, .ss_flags = 0};
        if (sigaltstack(&ss, NULL) != 0) {
            err(EXIT_FAILURE, "sigaltstack");
        }
    }
    {
        // register stack trace signal handlers
        int flags = SA_SIGINFO;
        #ifndef __APPLE__
        // for some reason backtrace() doesn't work on macOS when using alternate stack
        flags |= SA_ONSTACK;
        #endif
        struct sigaction sigAction = {.sa_sigaction = stackTraceSignalHandlerPosix, .sa_flags = flags};
        sigemptyset(&sigAction.sa_mask);
        
        addAction(SIGSEGV);
        addAction(SIGFPE);
        addAction(SIGINT);
        addAction(SIGILL);
        addAction(SIGILL);
        addAction(SIGTERM);
        addAction(SIGABRT);
//        add_action(SIGQUIT);
        addAction(SIGTSTP);

//        p("set stacktrace signal handler");
    }
}

#undef addAction
