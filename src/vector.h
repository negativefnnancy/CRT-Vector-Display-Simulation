#ifndef VECTOR_H
#define VECTOR_H

/* a simple struct to store a 2d vector */
typedef struct vec2_t {

    double x;
    double y;

} vec2_t;

/* initialize and return a vec2_t struct */
vec2_t make_vec2 (double x, double y);

/* return the length of a vector */
double length_vec2 (vec2_t vector);

/* add two vectors */
vec2_t add_vec2 (vec2_t a, vec2_t b);

/* subtract two vectors */
vec2_t subtract_vec2 (vec2_t a, vec2_t b);

/* multiply a vector by a scalar */
vec2_t multiply_vec2_scalar (vec2_t vector, double scalar);

/* divide a vector by a scalar */
vec2_t divide_vec2_scalar (vec2_t vector, double scalar);

#endif /* VECTOR_H */
