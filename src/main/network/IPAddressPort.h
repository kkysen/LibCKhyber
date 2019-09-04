//
// Created by Khyber on 10/14/2018.
//

#ifndef IP_ADDRESS_PORT_H
#define IP_ADDRESS_PORT_H

#include "src/main/string/String.h"
#include "src/main/network/Port.h"

typedef struct IPAddressPort {
    const String *ipAddress;
    const Port *port;
} IPAddressPort;

#endif // IP_ADDRESS_PORT_H
