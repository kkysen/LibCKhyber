//
// Created by Khyber on 9/16/2018.
//

#include "src/main/stackTrace/stackTraceSignalHandler/StackTraceSignalHandler.h"

#include <stdint.h>
#include <err.h>

#include "src/main/string/String.h"
#include "src/main/util/functional.h"
#include "src/main/util/signal/sigAction.h"
#include "src/main/util/signal/Signal.h"
#include "src/main/stackTrace/stackTrace/StackTrace.h"
#include "src/main/util/programName/programName.h"
#include "src/main/util/utils.h"

int stackTraceSignalHandlerLevel = 0;

Runnable preStackTraceSignalHandler = NULL;
Runnable postStackTraceSignalHandler = NULL;

/**
 * A signal handler that prints the current stacktrace to stderr.
 *
 * @param signal the signal caught
 * @param sigInfo extra info about the signal caught
 * @param context extra context about the signal caught
 */
static void stackTraceSignalHandlerPosix(int _signal, siginfo_t *sigInfo, void *context) {
    // for some reason stderr is closed in a signal handler,
    // so reassign it to stdout to prevent crashes from writing to stderr
    stderr = stdout;
    if (stackTraceSignalHandlerLevel != 0) {
        perror("Recursive signal raised in StackTraceSignalHandler");
        _Exit(1);
    }
    stackTraceSignalHandlerLevel++;
    
    if (preStackTraceSignalHandler) {
        preStackTraceSignalHandler();
    }
    
    {
        const Signal signal = {
                .signal = _signal,
                .sigInfo = sigInfo,
                .context = context,
        };
        StackTrace stackTrace;
        if (!StackTrace_init(&stackTrace, &signal)) {
            perror("StackTrace_init");
            goto exit;
        }
        StackTrace_toFile(&stackTrace, stderr);
        StackTrace_clear(&stackTrace);
    }
    
    if (postStackTraceSignalHandler) {
        postStackTraceSignalHandler();
    }
    
    stackTraceSignalHandlerLevel--;
    
    exit:
    *((char *) context) = 0;
    exit(EXIT_FAILURE);
}

#undef catch_ILL
#undef catch_FPE
#undef catchSub
#undef catchSignal
#undef printSignal

#define addAction(signal) addSigAction(signal, &sigAction)

void setStackTraceSignalHandler() {
    static bool alreadySet = false;
    if (alreadySet) {
        return;
    }
    alreadySet = true;
    {
        static u8 alternateStack[STACK_SIZE_MAX];
        // setup alternate stack
        stack_t ss = {.ss_sp = alternateStack, .ss_size = STACK_SIZE_MAX, .ss_flags = 0};
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