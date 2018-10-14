//
// Created by Khyber on 10/14/2018.
//

#include "Vector3.h"

Vector3 Vector3_scale(Vector3 v, float c) {
    return Vector3_new(v.x * c, v.y * c, v.z * c);
}

Vector3 Vector3_normalize(Vector3 v) {
    return Vector3_scale(v, 1 / Vector3_norm(v));
}

Vector3 Vector3_add(Vector3 v1, Vector3 v2) {
    return Vector3_new(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
}

float Vector3_dist2(Vector3 v1, Vector3 v2) {
    const float dx = v1.x - v2.x;
    const float dy = v1.y - v2.y;
    const float dz = v1.z - v2.z;
    return dx * dx + dy * dy + dz * dz;
}