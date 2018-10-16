//
// Created by Khyber on 9/17/2018.
//

#include "src/test/testStringFormat.h"

#include "src/main/string/String.h"

bool testStringFormat() {
    printf("start\n");
    String* const s = String_empty();
    String_format(s, "%d\n", 10);
    String_appendLiteral(s, "Hello\n");
    printf("%s", s->chars);
    String_free(s);
    printf("end\n");
    
    return true;
}