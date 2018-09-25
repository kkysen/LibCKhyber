//
// Created by Khyber on 9/25/2018.
//

#ifndef NUMBERS_H
#define NUMBERS_H

#include <stdint.h>

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

#if sizeof(float) == 32
typedef float f32;
#endif

#if sizeof(double) == 64
typedef double f64;
#endif

#if sizeof(long double) == 128
typedef long double f128;
#endif

#endif // NUMBERS_H
