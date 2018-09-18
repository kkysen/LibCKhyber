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
    programName = String_ofSize(PATH_MAX);
    if (readlink("/proc/self/exe", programName->chars, PATH_MAX) == -1) {
        perror("readlink");
        String_free(programName);
        programName = NULL;
        return NULL;
    }
    String_shrinkToSize(programName);
    return programName;
}