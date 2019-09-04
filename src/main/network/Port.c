//
// Created by Khyber on 11/1/2018.
//

#include "src/main/network/Port.h"

#include <stdlib.h>
#include <errno.h>
#include <values.h>
#include <stdio.h>
#include <unistd.h>

/**
 * Parse a string into a Port, a u16, using strtoll() and recording parsing errors.
 *
 * If the @param string is not
 */
struct Port Port_parse(const char *const string) {
    char *end = NULL;
    const i64 longPort = strtoll(string, &end, 10);
    // if end is not null-terminated, then there are extra non number characters at the end
    const bool isNaN = *end || errno == EINVAL;
    const bool i64Overflow = (longPort == LLONG_MAX || longPort == LLONG_MIN) && errno == ERANGE;
    const bool u16Overflow = longPort < 0 || longPort > UINT16_MAX;
    struct Port port = {
            .overflow = longPort,
            .error = isNaN ? PortError_NAN : (i64Overflow || u16Overflow) ? PortError_OVERFLOW : PortError_NONE,
            .string = string,
    };
    if (port.error == PortError_NONE) {
        port.port = (u16) longPort;
    }
    return port;
}

/**
 * Check if a Port is valid.
 *
 * @param this this Port
 * @param printErrors if true, print error messages based on Port.error
 * @return if this Port is valid
 */
bool Port_check(const struct Port this, bool printErrors) {
    if (this.error == PortError_NONE) {
        return true;
    }
    if (!printErrors) {
        return false;
    }
    fprintf(stderr, "ERROR: port number `%s` ", this.string);
    switch (this.error) {
        case PortError_OVERFLOW:
            fprintf(stderr, "%sflowed to `%u`, must be a valid unsigned 16-bit unsigned integer in [0, 65535]\n",
                    this.overflow < 0 ? "under" : "over", (u16) this.overflow);
            break;
        case PortError_NAN:
            fprintf(stderr, "is not a number\n");
            break;
        default:
            fprintf(stderr, "is invalid\n");
            break;
    }
    return false;
}

///**
// * Try to suggest a port to the user by popen()ing @see ./find-unused-port.sh.
// *
// * find-unused-port.sh finds the next unused port "allocated" to your uid
// * according to the algorithm in the FAQ email.
// *
// * If find-unused-port.sh succeeds, print the port number as a suggestion to the user.
// */
//void suggestPort() {
//    // try to suggest an unused port using find-unused-port.sh
//    // ok if it fails, just no suggestion
//    // redirect stderr to /dev/null b/c I want to suppress error messages
//    FILE *pipe = popen("./find-unused-port.sh 2> /dev/null", "r");
//    if (!pipe) {
//        return;
//    }
//    char buf[100] = {}; // definitely won't send more than 100 chars
//    const bool error = read(fileno(pipe), buf, sizeof(buf)) == -1;
//    // fgets uses a surprisingly large amount of memory
////    const bool error = !fgets(buf, sizeof(buf), pipe);
//    fclose(pipe);
//    if (error) {
//        return;
//    }
//    stripTrailingNewLine(buf);
//    const struct Port port = Port_parse(buf);
//    if (!Port_check(port, false)) {
//        return;
//    }
//    printf("suggested port: %u\n", port.port);
//}