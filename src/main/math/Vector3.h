//
// Created by Khyber on 10/14/2018.
//

#ifndef VECTOR_3_H
#define VECTOR_3_H

#include <math.h>
#include <stdint.h>

#include "src/main/math/clamp.h"
#include "src/main/util/numbers.h"

typedef union {
    struct {
        float x;
        float y;
        float z;
    };
    u8 bits[3 * sizeof(float)];
} Vector3;

#define Vector3_new(_x, _y, _z) (Vector3) {.x = (_x), .y = (_y), .z = (_z)}

#define Vector3_norm2(v) ((v).x * (v).x + (v).y * (v).y + (v).z * (v).z)

#define Vector3_magnitude2(v) Vector3_norm2(v)

#define Vector3_norm(v) sqrtf(Vector3_norm2(v))

#define Vector3_magnitude(v) Vector3_norm(v)

#define Vector_iScale(v, c) { \
    const float _c = c; \
    (v).x *= _c; \
    (v).y *= _c; \
    (v).z *= _c; \
}

Vector3 Vector3_scale(Vector3 v, float c);

#define Vector3_iNormalize(v) Vector_iScale(v, 1 / Vector3_norm(v))

Vector3 Vector3_normalize(Vector3 v);

#define Vector3_iAdd(v1, v2) { \
    (v1).x += (v2).x; \
    (v1).y += (v2).y; \
    (v1).z += (v2).z; \
}

#define Vector3_iMulAdd(v1, v2, c) \
{ \
    const float _c = c; \
    (v1).x += (v2).x * (c); \
    (v1).y += (v2).y * (c); \
    (v1).z += (v2).z * (c); \
}

Vector3 Vector3_add(Vector3 v1, Vector3 v2);

float Vector3_dist2(Vector3 v1, Vector3 v2);

#define Vector3_dist(v1, v2) sqrtf(Vector_dist2(v1, v2))

#define Vector3_inRadius(v1, v2, r) Vector3_dist(v1, v2) < (r) * (r)

#define Vector3_clamp(v, minX, minY, maxX, maxY, minZ, maxZ) \
    clamp((v).x, minX, maxX); \
    clamp((v).y, minY, maxY); \
    clamp((v).z, minZ, maxZ);

#define pv3(v) printf(#v": (%g, %g, %g)\n", (v).x, (v).y, (v).z)

#endif // VECTOR_3_H
