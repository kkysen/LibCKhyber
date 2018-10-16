//
// Created by Khyber on 12/24/2017.
//

#include "src/main/math/Vector2.h"

Vector2 Vector2_scale(Vector2 v, float c) {
    return Vector2_new(v.x * c, v.y * c);
}

Vector2 Vector2_normalize(Vector2 v) {
    return Vector2_scale(v, 1 / Vector2_norm(v));
}

Vector2 Vector2_add(Vector2 v1, Vector2 v2) {
	return Vector2_new(v1.x + v2.x, v1.y + v2.y);
}

float Vector2_dist2(Vector2 v1, Vector2 v2) {
    const float dx = v1.x - v2.x;
    const float dy = v1.y - v2.y;
    return dx * dx + dy * dy;
}