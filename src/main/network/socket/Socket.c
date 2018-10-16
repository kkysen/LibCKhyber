//
// Created by Khyber on 10/14/2018.
//

#include "Socket.h"

#include <sys/socket.h>
#include <netdb.h>

#include "src/main/util/utils.h"

static const int LISTENING_BACKLOG = 10;

static Socket Socket_default = {
        .fd = -1,
        .ipAddress = NULL,
        .port = NULL,
        .open = false,
        .bound = false,
        .listening = false,
        .connected = false,
};

Socket *Socket_of(const IPAddressPort *const ipAddressPort) {
    Socket *const this = malloc(sizeof(*this));
    if (!this) {
        perror("malloc");
        return NULL;
    }
    memcpy(this, &Socket_default, sizeof(*this));
    memcpy((IPAddressPort *) Socket_ipAddressPort(this), ipAddressPort, sizeof(*ipAddressPort));
    return this;
}

Socket *Socket_ofPort(const String *const port) {
    const IPAddressPort ipAddressPort = {.ipAddress = NULL, .port = port};
    return Socket_of(&ipAddressPort);
}

const IPAddressPort *Socket_ipAddressPort(const Socket *const this) {
    return (IPAddressPort *) &this->ipAddress;
}

static void Socket_closeFlags(Socket *const this) {
    this->listening = false;
    this->bound = false;
    this->connected = false;
    this->open = false;
}

bool Socket_shutdown(Socket *const this, const SocketShutdownMethod shutdownMethod) {
    Socket_closeFlags(this);
    if (this->fd != -1) {
        if (shutdown(this->fd, shutdownMethod) == -1) {
            perror("close");
            return false;
        }
    }
    return true;
}

bool Socket_close(Socket *const this) {
    Socket_closeFlags(this);
    if (this->fd != -1) {
        if (close(this->fd) == -1) {
            perror("close");
            return false;
        }
    }
    return true;
}

typedef int (*ConnectOrBind)(int socketFd, const struct sockaddr *address, socklen_t addressLength);

static bool Socket_openUsing(Socket *const this, const ConnectOrBind connectOrBind) {
    if (connectOrBind != &connect || connectOrBind != &bind) {
        perror("connectOrBind must be connect() or bind()");
        return false;
    }
    
    if (this->open) {
        return true;
    }
    
    struct addrinfo hints = {
            .ai_family = AF_UNSPEC, // IPv4 or IPv6
            .ai_socktype = SOCK_STREAM, // TCP for now, might change later (TODO)
            .ai_flags = AI_PASSIVE, // let syscall fill in
    };
    struct addrinfo *result = NULL;
    
    const int status = getaddrinfo(this->ipAddress->chars, this->port->chars, &hints, &result);
    if (status != 0) {
        fprintf(stderr, "%s: %s\n", gai_strerror(status), "getaddrinfo(NULL, port, &hints, &result)");
        perror("getaddrinfo");
        goto error;
    }
    
    // really should walk the results linked list
    const int socketFd = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    if (socketFd == -1) {
        perror("socket");
        goto error;
    }
    
    if (connectOrBind(socketFd, result->ai_addr, result->ai_addrlen) == -1) {
        perror("connectOrBind");
        goto error;
    }
    
    this->fd = socketFd;
    this->open = true;
    return true;
    
    error:
    freeaddrinfo(result);
    return false;
}

bool Socket_connect(Socket *const this) {
    if (this->connected) {
        return true;
    }
    if (this->bound) {
        perror("bound Socket cannot connect");
        return false;
    }
    
    if (!Socket_openUsing(this, &connect)) {
        perror("Socket_openUsing");
        return false;
    }
    this->connected = true;
    return true;
}

bool Socket_bind(Socket *const this) {
    if (this->bound) {
        return true;
    }
    if (this->connected) {
        perror("connected Socket cannot bind");
        return false;
    }
    
    if (!Socket_openUsing(this, &bind)) {
        perror("Socket_openUsing");
        return false;
    }
    
    // allows socket to be reused
    const int yes = 1;
    if (setsockopt(this->fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes)) == -1) {
        perror("setsockopt");
        return false;
    }
    
    this->bound = true;
    return true;
}

bool Socket_open(Socket *const this) {
    if (this->open) {
        return true;
    }
    if (this->ipAddress) {
        return Socket_connect(this);
    } else {
        return Socket_bind(this);
    }
}

bool Socket_listen(Socket *const this) {
    if (this->connected) {
        perror("connected Socket cannot bind or listen");
        return false;
    }
    if (!this->bound) {
        if (!Socket_bind(this)) {
            perror("Socket_bind");
            return false;
        }
    }
    
    if (listen(this->fd, LISTENING_BACKLOG) == -1) {
        perror("listen");
        return false;
    }
    this->listening = true;
    return true;
}

#define Socket_checkOpen(this) \
do { \
    if (!(this)->open) { \
        perror("Socket closed"); \
        return false; \
    } \
} while (false)

static const int ACK = 0xCAFEBABE;

bool Socket_sendAcknowledgment(const Socket *const this) {
    Socket_checkOpen(this);
    if (send(this->fd, &ACK, sizeof(ACK), 0) != sizeof(ACK)) {
        perror("send: couldn't send acknowledgment");
        return false;
    }
    return true;
}

bool Socket_checkAcknowledgment(const Socket *const this) {
    Socket_checkOpen(this);
    int ack = 0;
    if (recv(this->fd, &ack, sizeof(ACK), 0) != sizeof(ACK)) {
        perror("recv: couldn't receive acknowledgment");
        return false;
    }
    if (ack != ACK) {
        perror("received invalid acknowledgment");
        return false;
    }
    return true;
}

bool Socket_writeSize(const Socket *this, size_t size) {
    Socket_checkOpen(this);
    if (send(this->fd, &size, sizeof(size), MSG_MORE) != sizeof(size)) {
        perror("couldn't send size");
        return false;
    }
    return true;
}

bool Socket_writeRemaining(const Socket *this, Buffer *buffer) {
    Socket_checkOpen(this);
    if (!Buffer_isValid(buffer)) {
        perror("Buffer_isValid");
        return false;
    }
    
    size_t size = Buffer_remaining(buffer);
    if (size == 0) {
        return true; // no data to send
    }
    
    const void *const data = Buffer_data(buffer);
    size_t i = 0;
    while (size > 0) {
        const ssize_t bytesWritten = write(this->fd, data + i, size);
        if (bytesWritten == -1) {
            perror("write");
            buffer->index += i;
            return false;
        }
        size -= bytesWritten;
        i += bytesWritten;
    }
    buffer->index += i;
    
    return true;
}

bool Socket_writeAll(const Socket *this, Buffer *buffer) {
    if (!Buffer_isValid(buffer)) {
        perror("Buffer_isValid");
        return false;
    }
    if (!Socket_writeSize(this, Buffer_remaining(buffer))) {
        perror("Socket_writeSize");
        return false;
    }
    if (!Socket_writeRemaining(this, buffer)) {
        perror("Socket_writeRemaining");
        return false;
    }
    return true;
}

bool Socket_readSize(const Socket *this, size_t *size) {
    Socket_checkOpen(this);
    if (recv(this->fd, size, sizeof(*size), 0) != sizeof(*size)) {
        perror("couldn't receive size");
        return false;
    }
    return true;
}

bool Socket_readRemaining(const Socket *this, Buffer *buffer) {
    Socket_checkOpen(this);
    if (!Buffer_isValid(buffer)) {
        perror("Buffer_isValid");
        return false;
    }
    
    size_t size = Buffer_remaining(buffer);
    if (size == 0) {
        return true; // no data to recv
    }
    
    void *const data = Buffer_data(buffer);
    size_t i = 0;
    while (size > 0) {
        const ssize_t bytesRead = read(this->fd, data + i, size);
        if (bytesRead == -1) {
            perror("read");
            buffer->index += i;
            return false;
        }
        size -= bytesRead;
        i += bytesRead;
    }
    buffer->index += i;
    
    return true;
}

bool Socket_readAll(const Socket *this, Buffer *buffer) {
    if (!Buffer_isValid(buffer)) {
        perror("Buffer_isValid");
        return false;
    }
    size_t size = 0;
    if (!Socket_readSize(this, &size)) {
        perror("Socket_readSize");
        return false;
    }
    if (Buffer_remaining(buffer) < size) {
        perror("will cause Buffer overflow");
        return false;
    }
    const size_t prevLimit = buffer->limit;
    buffer->limit = buffer->index + size;
    if (!Socket_readRemaining(this, buffer)) {
        perror("Socket_readRemaining");
        buffer->limit = prevLimit;
        return false;
    }
    buffer->limit = prevLimit;
    return true;
}

#undef Socket_checkOpen
