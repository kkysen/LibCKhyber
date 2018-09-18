//
// Created by Khyber on 9/6/2018.
//

#include "stackTraceAddr2Line.h"
#include "../programName.h"
#include "../util/utils.h"
#include "../util/setField.h"
#include "addr2Line.h"

static void StackTrace_free(StackTrace* const lines) {
    Strings_clear((Strings*) &lines->lines);
    setField(lines->ok, false);
}

#define INDENT "    "
#define STACK_TRACE_HEADER "Stacktrace:\n"

static size_t StackTrace_printLength(const StackTrace stackTrace) {
    const Strings lines = stackTrace.lines;
    size_t size = 0;
    size += literalStringLength(STACK_TRACE_HEADER);
    for (size_t i = 0; i < lines.size; ++i) {
        size += literalStringLength(INDENT);
        size += lines.strings[i].size;
        size += literalStringLength("\n");
    }
    return size;
}

static void StackTrace_toString(StackTrace stackTrace, String* out) {
    String_ensureMoreCapacity(out, StackTrace_printLength(stackTrace));
    const Strings lines = stackTrace.lines;
    String_appendLiteral(out, STACK_TRACE_HEADER);
    for (size_t i = 0; i < lines.size; ++i) {
        String_appendLiteral(out, INDENT);
        String_append(out, lines.strings[i]);
        String_appendLiteral(out, "\n");
    }
}



static StackTrace runAddr2LineStatically(const Addresses addresses) {
    const String programName = getProgramName();
    const Addr2LineOptions options = {
            .demangleNames = true,
            .prettyPrint = true,
            .showAddresses = true,
            .showBaseNames = true,
            .showFunctions = true,
            .showInlinedFunctions = true,
            .fileName = &programName,
            .addresses = addresses.addresses,
            .numAddresses = addresses.numAddresses,
    };
    return addr2Line(&options);
}



static String* getAddr2LineCommandBase() {
    #ifdef __APPLE__
    #define addr2line_base "atos -o "
    #else
    #define addr2LineBase "addr2line -f -s -p -e "
    #endif
    
    static String* base = NULL;
    if (base) {
        return String_copy(*base);
    }
    
    base = String_ofSize(arrayLen(addr2LineBase) + PATH_MAX + arrayLen(" ") + PTR_MAX_STRLEN);
    String_appendLiteral(base, addr2LineBase);
    String_append(base, getProgramName());
    String_appendLiteral(base, " ");
    String_shrinkToSize(base);
    return getAddr2LineCommandBase();
}

static String* getAddr2LineCommand(const Addresses addresses) {
    String* const command = getAddr2LineCommandBase();
    for (size_t i = 0; i < addresses.numAddresses; ++i) {
        String_format(command, "%p", addresses.addresses[i]);
        String_appendLiteral(command, " ");
    }
    return command;
}

#define AVG_ADDR_2_LINE_LENGTH 40

static bool addr2LineCommandLineRawOutput(const char* const command, String* const buffer) {
    FILE* const output = popen(command, "r");
    if (!output) {
        perror("popen");
        return false;
    }
    
    const size_t bufSize = String_appendStream(buffer, output);
    if (bufSize == 0) {
        return false;
    }
    const int retVal = pclose(output);
    if (retVal == -1) {
        return false;
    }
    if (WEXITSTATUS(retVal) != 0) { // NOLINT
        return false;
    }
    return true;
}

static StackTrace runAddr2LineCommandLineDirectly(const char* const command, const size_t numLines) {
    const StackTrace error = StackTrace_invalid();
    
    String* const buf = String_ofSize((numLines + 1) * AVG_ADDR_2_LINE_LENGTH);
    if (!addr2LineCommandLineRawOutput(command, buf)) {
        String_free(buf);
        return error;
    }
    
    StackTrace stackTrace = {
            .ok = true,
    };
    const Strings* const lines = String_split(*buf, *String_of("\n"));
    memcpy((Strings*) &stackTrace.lines, lines, sizeof(Strings));
    return stackTrace;
}

static StackTrace runAddr2LineCommandLine(const Addresses addresses) {
    String* const addr2LineCommand = getAddr2LineCommand(addresses);
    addresses.numAddresses;
    const StackTrace lines = runAddr2LineCommandLineDirectly(addr2LineCommand->chars, addresses.numAddresses);
    String_free(addr2LineCommand);
    return lines;
}



bool runAddr2Line(const Addresses addresses, String* const out) {
    StackTrace lines = runAddr2LineStatically(addresses);
    if (!lines.ok) {
        // try again
        lines = runAddr2LineCommandLine(addresses);
    }
    if (!lines.ok) {
        return false;
    }
    
    StackTrace_toString(lines, out);
    StackTrace_free(&lines);
    return true;
}
