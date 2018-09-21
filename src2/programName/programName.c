//
// Created by Khyber on 9/5/2018.
//

#include "programName.h"

#include <stdbool.h>

#include "../util/utils.h"

const String* getProgramName() {
    static String* programName = NULL;
    if (programName) {
        return programName;
    }
    char programNameChars[PATH_MAX] = {};
    if (readlink("/proc/self/exe", programNameChars, PATH_MAX) == -1) {
        perror("readlink");
        String_free(programName);
        programName = NULL;
        return NULL;
    }
    return String_ofChars(programNameChars);
}