//
// Created by Khyber on 10/14/2018.
//

#ifndef IP_ADDRESS_PORT_H
#define IP_ADDRESS_PORT_H

#include "src/main/string/String.h"

typedef struct IPAddressPort {
    const String *ipAddress;
    const String *port;
} IPAddressPort;

#endif // IP_ADDRESS_PORT_H
