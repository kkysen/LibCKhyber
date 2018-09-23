//
// Created by Khyber on 9/5/2018.
//

#include "programName.h"

#include "../util/utils.h"

static String *programName = NULL;

static void freeProgramName() {
    String_free(programName);
}

const String *getProgramName() {
    if (programName) {
        return programName;
    }
    char *const programNameChars = calloc(PATH_MAX, sizeof(char));
    if (readlink("/proc/self/exe", programNameChars, PATH_MAX) == -1) {
        perror("readlink");
        free(programNameChars);
        programName = NULL;
        return NULL;
    }
    programName = String_ofChars(programNameChars);
    free(programNameChars);
    atexit(freeProgramName);
    return programName;
}