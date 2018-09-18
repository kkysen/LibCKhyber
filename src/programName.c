//
// Created by Khyber on 9/5/2018.
//

#include "programName.h"

#include <stdbool.h>

#include "util/utils.h"

String getProgramName() {
    static bool alreadyRead = false;
    static String programName;
    if (alreadyRead) {
        return programName;
    }
    programName = String_onStackOfSize(PATH_MAX);
    if (readlink("/proc/self/exe", programName.chars, PATH_MAX) == -1) {
        perror("readlink");
        String_clear(&programName);
        return programName;
    }
    String_shrinkToSize(&programName);
    alreadyRead = true;
    return programName;
}