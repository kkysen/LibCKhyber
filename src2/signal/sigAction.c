//
// Created by Khyber on 12/19/2017.
//

#include "sigaction.h"

#include <stdlib.h>
#include <err.h>

#include "../util/utils.h"

void addSigAction(int signal, const struct sigaction *sigAction) {
    if (sigaction(signal, sigAction, NULL) != 0) {
        perror("sigaction(signal, sig_action, NULL)");
        err(EXIT_FAILURE, "sigaction");
    }
}

void addSignalHandler(int signal, SignalHandler signalHandler) {
    struct sigaction sigAction = {.sa_handler = signalHandler, .sa_flags = 0};
    sigemptyset(&sigAction.sa_mask);
    addSigAction(signal, &sigAction);
}

void registerForAllSignals(SignalHandler signalHandler) {
    struct sigaction sigAction = {.sa_handler = signalHandler, .sa_flags = 0};
    sigemptyset(&sigAction.sa_mask);
    for (int signal = 0; signal < NSIG; ++signal) {
        if (signal != SIGKILL) {
            addSigAction(signal, &sigAction);
        }
    }
}

void alwaysRunOnAnyExit(Runnable onExit, SignalHandler signalHandler) {
    if (atexit(onExit) != 0) {
        perror("atexit(on_exit)");
        err(EXIT_FAILURE, "atexit");
    }
    registerForAllSignals(signalHandler);
}