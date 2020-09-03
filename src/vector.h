#ifndef VECTOR_H
#define VECTOR_H

/* a simple struct to store a 2d vector */
typedef struct vec2_t {

    double x;
    double y;

} vec2_t;

/* initialize and return a vec2_t struct */
vec2_t make_vec2 (double x, double y);

#endif /* VECTOR_H */
