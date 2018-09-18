//
// Created by Khyber on 9/17/2018.
//

#include <values.h>
#include "testStringFormat.h"

#include "../src2/string/String.h"
#include "../src2/util/utils.h"

static const int primes[] = {3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97};
static int primeCounts[arrayLen(primes)] ={};

static inline void checkPrime(const int n) {
    for (int i = 0; i < arrayLen(primes); i++) {
        const int prime = primes[i];
        if (n % prime == 0) {
            primeCounts[i]++;
            return;
        }
    }
}

static inline void countPrimes(const int max) {
    for (int n = 1; n < max; n += 2) {
        checkPrime(n);
    }
    double cumPercentage = 0;
    cumPercentage += 0.5;
    printf("%d: %d, %f, %f\n", 2, max / 2, 0.5, cumPercentage);
    for (int i = 0; i < arrayLen(primes); i++) {
        const int prime = primes[i];
        const int primeCount = primeCounts[i];
        double percentage = primeCount / (double) max;
        cumPercentage += percentage;
        printf("%d: %d, %f, %f\n", prime, primeCount, percentage, cumPercentage);
    }
}

bool testStringFormat() {
    printf("start\n");
    String* const s = String_ofSize(0);
    String_format(s, "%d\n", 10);
    String_appendLiteral(s, "Hello\n");
    printf("%s", s->chars);
    String_free(s);
    printf("end\n");
    
    countPrimes(100000000);
    
    return true;
}