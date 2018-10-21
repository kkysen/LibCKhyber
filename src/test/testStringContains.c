//
// Created by Khyber on 10/20/2018.
//

#include "src/test/testStringContains.h"

#include "src/main/string/String.h"
#include "src/main/util/utils.h"

bool testStringContains() {
    const String string = String_usingLiteral("Hello, World.  My name is Khyber Sen");
    const char *const subStrings[] = {
            ",", // 1
            ". ", // 2
            "My", // 2
            "Sen", // 3
            "name", // 4
            "World", // 5
            "Khyber", // 6
            "My name", // 7
            "Hello, W", // 8
            "My name is", // 10
            "My name is Khyber Sen", // 21
    };
    bool passed = true;
    for (size_t i = 0; i < arrayLen(subStrings); i++) {
        const String subString = String_usingChars((char *) subStrings[i]);
        if (!String_contains(&string, &subString)) {
            printf("`%s` not found in `%s`\n", subString.chars, string.chars);
            passed = false;
        }
    }
    return passed;
}