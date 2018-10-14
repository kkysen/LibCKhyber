//
// Created by Khyber on 12/24/2017.
//

#include "Vector.h"

Vector Vector_scale(const Vector vector, const float scalar) {
    return Vector_new(vector.x * scalar, vector.y * scalar);
}

Vector Vector_normalize(const Vector vector) {
    return Vector_scale(vector, 1 / Vector_norm(vector));
}

Vector Vector_add(const Vector vector1, const Vector vector2) {
	return Vector_new(vector1.x + vector2.x, vector1.y + vector2.y);
}

float Vector_dist2(const Vector vector1, const Vector vector2) {
    const float dx = vector1.x - vector2.x;
    const float dy = vector1.y - vector2.y;
    return dx * dx + dy * dy;
}