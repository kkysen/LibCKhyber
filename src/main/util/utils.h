//
// Created by Khyber on 11/9/2017.
//

#ifndef UTILS_H
#define UTILS_H

#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>

typedef unsigned int uint;

#define arrayLen(array) (sizeof((array)) / sizeof(*(array)))

#define literalStringLength(literalString) arrayLen(literalString) - 1

#define PTR_MAX_STRLEN (((sizeof(void *) * 8) / 4) + 1)

#ifndef PATH_MAX
#define PATH_MAX 4096
#endif

#define extreme(cmp, a, b) \
    ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a cmp _b ? _a : _b; })

#define min(a, b) extreme(<, a, b)

#define max(a, b) extreme(>, a, b)

#define memcpy_add(dst, src, size) \
    memcpy(dst, src, size); \
    (dst) += (size);

extern const char *HOME;

/**
 * Initialize the HOME global the environment variable HOME.
 */
void init_home();

#define einval_ret(assertion, message, ret_val) \
    if (assertion) { \
        fprintf(stderr, "Invalid Argument: %s\n", message); \
        return ret_val; \
    }

#define einval(assertion, message) einval_ret(assertion, message, EXIT_FAILURE)

#define check(expr) if ((expr) == -1) return -1
#define check_perror(expr) if ((expr) == -1) return perror(#expr), -1
#define check_msg(expr, msg) if ((expr) == -1) return perror(msg), -1

#define check_null(expr) if ((expr) == NULL) return -1;
#define check_null_perror(expr) if ((expr) == NULL) return perror(#expr), -1
#define check_null_msg(expr, msg) if ((expr) == NULL) return perror(msg), -1

#define p(s) printf(s"\n")
#define pn() p("")
#define ps(var) printf(#var": `%s` (%zu)\n", (char *) (var), strlen(var))
#define pz(var) printf(#var": %zu\n", (size_t) (var))
#define pd(var) printf(#var": %zd\n", (ssize_t) (var))
#define pp(var) printf(#var": %p\n", var)
#define pb(var) printf(#var": %s\n", (var) ? "true" : "false")
#define pc(var) printf(#var": %c\n", (char) (var))
#define pf(var) printf(#var": %f\n", (double) (var))
#define pS(var) printf(#var": `%s` (%zu)\n", (var)->chars, (var)->size)

#define _perror(strerror_call, s) \
    fprintf(stderr, \
        "[%d] %s (%s at %s:%d): \n\t%s\n\n", \
        getpid(), strerror_call, __func__, __FILE__, __LINE__, s)

#define perror(s) _perror(strerror(errno), s)

#define perror_assert_expr(expr) do {if (!(expr)) perror(#expr); _Static_assert(false, #expr);} while (false)

#define perror_assert(expr, s) do {if (!(expr)) perror(s); _Static_assert(false, #expr);} while (false)

#define debug() printf("[%d] %s at %s:%d\n", getpid(), __func__, __FILE__, __LINE__)

void doubleSleep(double seconds);

double secondsElapsed(clock_t start, clock_t end);

//#define new_const(type, var_name, initializer)
//    const type _type = initializer;
//    type *const var_name = (type *) malloc(sizeof(type));
//    memcpy(var_name, &_type, sizeof(type))

#define memClear(ptr) memset(ptr, 0, sizeof(*(ptr)))

void freeConst(const void *ptr);

#define uintToStr(s, u, base) \
do { \
    if ((base) < 2 || (base) > 36) { \
        break; \
    } \
    \
    typeof(u) val = u; \
    char *ptr = s; \
    char *start = s; \
    typeof(u) tmp = val; \
    do { \
        tmp = val; \
        val /= (base); \
        *ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz" \
                 [(36 - 1) + (tmp - val * (base))]; \
    } while (val); \
    \
    (s) = ptr; \
    *ptr-- = 0; \
    \
    while (start < ptr) { \
        const char tmp = *ptr; \
        *ptr--= *start; \
        *start++ = tmp; \
    } \
} while (false)

#define intToStr(s, i, base) \
do { \
    if ((base) < 2 || (base) > 36) { \
        break; \
    } \
    \
    typeof(i) val = i; \
    char *ptr = s; \
    char *start = s; \
    typeof(i) tmp = val; \
    do { \
        tmp = val; \
        val /= (base); \
        *ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz" \
                 [(36 - 1) + (tmp - val * (base))]; \
    } while (val); \
    \
    if (tmp < 0) { \
        *ptr++ = '-'; \
    } \
    (s) = ptr; \
    *ptr-- = 0; \
    \
    while (start < ptr) { \
        const char tmp = *ptr; \
        *ptr--= *start; \
        *start++ = tmp; \
    } \
} while (false)

#endif // UTILS_H
