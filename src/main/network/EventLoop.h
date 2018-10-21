//
// Created by Khyber on 10/15/2018.
//

#ifndef EVENT_LOOP_H
#define EVENT_LOOP_H

#include <stdbool.h>

typedef struct EventLoop {
    int epollFd;
} EventLoop;

struct Event;
typedef struct Event Event;

typedef void (*EventLoopCallback)(const Event *event, void *data);

struct Event {
    int fd;
    EventLoopCallback callback;
};

bool EventLoop_init(EventLoop *this);

EventLoop *EventLoop_new();

bool EventLoop_add(EventLoop *this, int fd);

bool EventLoop_remove(EventLoop *this, int fd);

void EventLoop_run();

#endif // EVENT_LOOP_H
