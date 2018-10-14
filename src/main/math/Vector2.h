//
// Created by Khyber on 12/24/2017.
//

#ifndef VECTOR_2_H
#define VECTOR_2_H

#include <math.h>
#include <stdint.h>

#include "../util/numbers.h"
#include "clamp.h"

typedef union {
    struct {
        float x;
        float y;
    };
    u64 bits;
} Vector2;

#define Vector2_new(_x, _y) (Vector2) {.x = (_x), .y = (_y)}

#define Vector2_norm2(v) ((v).x * (v).x + (v).y * (v).y)

#define Vector2_magnitude2(v) Vector2_norm2(v)

#define Vector2_norm(v) sqrtf(Vector2_norm2(v))

#define Vector2_magnitude(v) Vector2_norm(v)

#define Vector_iScale(v, c) { \
    const float _c = c; \
    (v).x *= _c; \
    (v).y *= _c; \
}

Vector2 Vector2_scale(Vector2 v, float c);

#define Vector2_iNormalize(v) Vector_iScale(v, 1 / Vector2_norm(v))

Vector2 Vector2_normalize(Vector2 v);

#define Vector2_iAdd(v1, v2) { \
    (v1).x += (v2).x; \
    (v1).y += (v2).y; \
}

#define Vector2_iMulAdd(v1, v2, c) { \
    const float _c = c; \
    (v1).x += (v2).x * (c); \
    (v1).y += (v2).y * (c); \
}

Vector2 Vector2_add(Vector2 v1, Vector2 v2);

float Vector2_dist2(Vector2 v1, Vector2 v2);

#define Vector2_dist(v1, v2) sqrtf(Vector_dist2(v1, v2))

#define Vector2_inRadius(v1, v2, r) Vector2_dist(v1, v2) < (r) * (r)

//#define Vector2_asSDLPoint(vector) ((SDL_Point) {.x = (vector).x, .y = (vector).y})

#define Vector2_clamp(v, minX, minY, maxX, maxY) \
    clamp((v).x, minX, maxX); \
    clamp((v).y, minY, maxY)

#define pv2(v) printf(#v": (%g, %g)\n", (v).x, (v).y)

#endif // VECTOR_2_H