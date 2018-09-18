//
// Created by Khyber on 9/16/2018.
//

#include "../stackTrace/StackFrame.h"
#include "../bfd/BinaryFileDescriptor.h"

#ifndef ADDR_2_LINE_H
#define ADDR_2_LINE_H

typedef struct Addr2Line {
    const String *demangleStyle;
    BFD* bfd;
    const Section* section;
    const Symbol* const* symbols;
} Addr2Line;

typedef struct Addr2LineArgs {
    const String* const fileName;
    const String* const sectionName;
    const String* const demangleStyle;
    const String* const bfdTarget;
} Addr2LineArgs;

Addr2Line* Addr2Line_new(const Addr2LineArgs* args);

void Addr2Line_free(const Addr2Line* this);

void Addr2Line_convert(const Addr2Line* this, StackFrame* frame, const void* address, const String* message);

#endif // ADDR_2_LINE_H
