//
// Created by Khyber on 11/8/2017.
//

#ifndef STACKTRACE_H
#define STACKTRACE_H

#include "../signal/sigAction.h"

extern int stackTraceLevel;

extern Runnable preStackTrace;
extern Runnable postStackTrace;

/**
 * Print the stacktrace and PID of a thread to stderr.
 */
void printStackTrace();

/**
 * Set the signal handler to a
 * signal handler that will print the current stacktrace.
 */
void setStackTraceSignalHandler();

#endif // STACKTRACE_H
