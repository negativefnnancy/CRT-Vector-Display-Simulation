#include <math.h>

#include "vector.h"

vec2_t make_vec2 (double x, double y) {

    vec2_t vector;
    vector.x = x;
    vector.y = y;
    return vector;
}

double length_vec2 (vec2_t vector) {

    /* pythagorean theorem */
    return sqrt (vector.x * vector.x + vector.y * vector.y);
}

vec2_t add_vec2 (vec2_t a, vec2_t b) {

    return make_vec2 (a.x + b.x, a.y + b.y);
}

vec2_t subtract_vec2 (vec2_t a, vec2_t b) {

    return make_vec2 (a.x - b.x, a.y - b.y);
}

vec2_t multiply_vec2_scalar (vec2_t vector, double scalar) {

    return make_vec2 (vector.x * scalar, vector.y * scalar);
}

vec2_t divide_vec2_scalar (vec2_t vector, double scalar) {

    return make_vec2 (vector.x / scalar, vector.y / scalar);
}
