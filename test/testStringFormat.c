//
// Created by Khyber on 9/17/2018.
//

#include "testStringFormat.h"

#include "../src2/string/String.h"

bool testStringFormat() {
    printf("start\n");
    String* const s = String_ofSize(0);
    String_format(s, "%d\n", 10);
    String_appendLiteral(s, "Hello\n");
    printf("%s", s->chars);
    String_free(s);
    printf("end\n");
    
    return true;
}