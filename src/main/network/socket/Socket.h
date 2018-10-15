//
// Created by Khyber on 10/14/2018.
//

#ifndef SOCKET_H
#define SOCKET_H

#include <stdbool.h>

#include "../../string/String.h"
#include "../IPAddressPort.h"
#include "../../serialize/buffer/Buffer.h"

typedef struct Socket {
    int fd;
    IPAddressPort ipAddressPort;
    bool open;
    bool bound;
    bool listening;
    bool connected;
} Socket;

typedef enum SocketShutdownMethod {
    SocketShutdown_RECEIVING = 0,
    SocketShutdown_TRANSMITTING = 1,
    SocketShutdown_BOTH = 2,
} SocketShutdownMethod;

Socket *Socket_of(const IPAddressPort *ipAddressPort);

Socket *Socket_ofPort(const String *port);

bool Socket_shutdown(Socket *this, SocketShutdownMethod shutdownMethod);

bool Socket_close(Socket *this);

bool Socket_connect(Socket *this);

bool Socket_bind(Socket *this);

bool Socket_open(Socket *this);

bool Socket_listen(Socket *this);

bool Socket_sendAcknowledgment(const Socket *this);

bool Socket_checkAcknowledgment(const Socket *this);

bool Socket_writeSize(const Socket *this, size_t size);

bool Socket_writeRemaining(const Socket *this, Buffer *buffer);

bool Socket_writeAll(const Socket *this, Buffer *buffer);

bool Socket_readRemaining(const Socket *this, Buffer *buffer);

bool Socket_readSize(const Socket *this, size_t *size);

bool Socket_readAll(const Socket *this, Buffer *buffer);

#endif // SOCKET_H
