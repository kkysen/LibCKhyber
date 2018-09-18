//
// Created by Khyber on 9/16/2018.
//

#include "Addr2Line.h"

#include "../util/setField.h"

Addr2Line* Addr2Line_new(const Addr2LineArgs* const args) {
    Addr2Line *const this = malloc(sizeof(*this));
    if (!this) {
        perror("malloc");
        return NULL;
    }
    
    // TODO
}

void Addr2Line_free(const Addr2Line* const this) {
    // TODO
}

void Addr2Line_convert(const Addr2Line* const this, StackFrame* const frame,
                       const void* const address, const String* const message) {
    frame->address = address;
    frame->message = message;
    
    // TODO
}