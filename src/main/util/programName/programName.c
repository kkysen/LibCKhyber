//
// Created by Khyber on 9/5/2018.
//

#include "src/main/util/programName/programName.h"

#include "src/main/util/utils.h"

static void freeProgramName() {
    String_free(getProgramName());
}

const String *getProgramName() {
    static String *programName = NULL;
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
    atexit(&freeProgramName);
    return programName;
}