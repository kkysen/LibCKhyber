//
// Created by Khyber on 9/17/2018.
//

#ifndef SIGNAL_H
#define SIGNAL_H

#include <signal.h>

#include "../string/String.h"

typedef struct Signal {
    const int signal;
    const siginfo_t *const sigInfo;
    const void *const context;
} Signal;

void Signal_toString(const Signal *this, String *out);

#endif // SIGNAL_H
