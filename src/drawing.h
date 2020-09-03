#ifndef DRAWING_H
#define DRAWING_H

#include "pixel_buffer.h"
#include "vector.h"
#include "color.h"

/* draw a point at a given location using a given color */
void draw_point (pixel_buffer_t *buffer, vec2_t position, color_t color);

/* draw a straight line segment from point a to point b using the given color */
void draw_line (pixel_buffer_t *buffer, vec2_t a, vec2_t b, color_t color);

#endif /* DRAWING_H */
