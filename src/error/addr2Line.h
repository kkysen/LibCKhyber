//
// Created by Khyber on 9/4/2018.
//

#include <stdbool.h>
#include <bfd.h>

#include "../string/String.h"
#include "stackTraceAddr2Line.h"

#ifndef ADDR2LINE_H
#define ADDR2LINE_H

#ifdef __BFD_H_SEEN__
    const bool ADDR2LINE_IMPLEMENTED = true;
#else
    const bool ADDR2LINE_IMPLEMENTED = false;
#endif

typedef struct {
    
    const bool showAddresses;
    const bool showBaseNames;
    const bool showFunctions;
    const bool showInlinedFunctions;
    const bool prettyPrint;
    const bool demangleNames;
    
    const String* const fileName;
    const void* const *const addresses;
    const size_t numAddresses;
    const String* const sectionName;
    const String* const demangleStyle;
    const String* const bfdTarget;
    
} Addr2LineOptions;

/**
 * A statically linked version of addr2line instead of a command-line version.
 *
 * @param options addr2line "command-line" options
 * @return the StackTrace
 */
StackTrace addr2Line(const Addr2LineOptions* options);

#endif // ADDR2LINE_H
