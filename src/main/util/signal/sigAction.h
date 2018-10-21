//
// Created by Khyber on 9/6/2018.
//

#ifndef SIG_ACTION_H
#define SIG_ACTION_H

#include <signal.h>
#include <sys/signal.h>

#include "src/main/util/functional.h"

typedef void (*SignalHandler)(const int);

void addSigAction(int signal, const struct sigaction *sigAction);

void addSignalHandler(int signal, SignalHandler signalHandler);

void registerForAllSignals(SignalHandler signalHandler);

void alwaysRunOnAnyExit(Runnable onExit, SignalHandler signalHandler);

#endif // SIG_ACTION_H
