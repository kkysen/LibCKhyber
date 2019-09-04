//
// Created by Khyber on 10/24/2018.
//

#include "src/test/testException.h"

#include "src/main/stackTrace/exception/Exception.h"

bool testException() {
    printf("Testing Exception\n");
    const Exception *exception = NULL;
    if (tryCatchException(&exception)) {
        Exception_toFile(exception, stderr);
        Exception_clear(exception);
        return true;
    } else {
        const String name = String_usingLiteral("MyException");
        const Exception throwing = {
                .code = 1,
                .name = &name,
        };
        printf("should be null: %p\n", exception);
        printf("throwing\n");
        throw(&throwing);
    }
    return false;
}