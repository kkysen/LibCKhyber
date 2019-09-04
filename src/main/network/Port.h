//
// Created by Khyber on 11/1/2018.
//

#ifndef PORT_H
#define PORT_H

#include <stdbool.h>

#include "src/main/util/numbers.h"

// TODO use String * instead of char * in LibCKhyber

typedef enum PortError {
    PortError_NONE = 0,
    PortError_OVERFLOW,
    PortError_NAN,
} PortError;

typedef struct Port {
    union {
        u16 port;
        i64 overflow;
    };
    enum PortError error;
    const char *string;
} Port;

Port Port_parse(const char *string);

bool Port_check(struct Port this, bool printErrors);

void suggestPort();

#endif // PORT_H
