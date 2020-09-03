#include <math.h>

#include "drawing.h"

void draw_point (pixel_buffer_t *buffer, vec2_t position, color_t color) {

    /* the integer components of the coordinates */
    double int_x, int_y;
    
    /* the coordinates of the adjacent pixels */
    double adj_x, adj_y

    /* the fractional components of the coordinates */
    double frac_x, frac_y;

    /* the weights for distributing the color across the pixels being drawn to */
    double weight_x, weight_y, adj_weight_x, adj_weight_y;

    /* separate out the integer and fractional components of the coordinates */
    int_x = floor (position.x);
    int_y = floor (position.y);
    frac_x = position.x - int_x;
    frac_y = position.y - int_y;

    /* calculate the adjacent pixel coordinates */
    adj_x = int_x + 1;
    adj_y = int_y + 1;

    /* calculate the weights */
    weight_x = 1 - frac_x;
    weight_y = 1 - frac_y;
    adj_weight_x = frac_x;
    adj_weight_y = frac_y;

    /* paint the pixel values */
    set_pixel_rgba (buffer,
                    int_x, int_y,
                    multiply_color (color,
                                    make_white_with_alpha (weight_x * weight_y)));
    set_pixel_rgba (buffer,
                    adj_x, int_y,
                    multiply_color (color,
                                    make_white_with_alpha (adj_weight_x * weight_y)));
    set_pixel_rgba (buffer,
                    int_x, adj_y,
                    multiply_color (color,
                                    make_white_with_alpha (weight_x * adj_weight_y)));
    set_pixel_rgba (buffer,
                    adj_x, adj_y,
                    multiply_color (color,
                                    make_white_with_alpha (adj_weight_x * adj_weight_y)));
}

void draw_line (pixel_buffer_t *buffer, vec2_t a, vec2_t b, color_t color) {

    
}
