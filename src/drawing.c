#include <math.h>

#include "drawing.h"

void draw_point (pixel_buffer_t *buffer, vec2_t position, color_t color) {

    /* the integer components of the coordinates */
    double int_x, int_y;
    
    /* the coordinates of the adjacent pixels */
    double adj_x, adj_y;

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
    blend_pixel (buffer,
                 int_x, int_y,
                 multiply_alpha (color, weight_x * weight_y));

    /* dont go out of bounds! */
    if (adj_x < buffer->width)
        blend_pixel (buffer,
                     adj_x, int_y,
                     multiply_alpha (color, adj_weight_x * weight_y));

    /* dont go out of bounds! */
    if (adj_y < buffer->height) {

        blend_pixel (buffer,
                     int_x, adj_y,
                     multiply_alpha (color, weight_x * adj_weight_y));

        /* dont go out of bounds! */
        if (adj_x < buffer->width)
            blend_pixel (buffer,
                         adj_x, adj_y,
                         multiply_alpha (color, adj_weight_x * adj_weight_y));
    }
}

void draw_line (pixel_buffer_t *buffer, vec2_t a, vec2_t b, color_t color) {

    /* draw a line by plotting a bunch of points along the path of the line */
    int i;

    /* figure out how many points to plot
     * according to the distance between the two end points
     * as well as how bright to make each point to normalize the overall 
     * amount of brightens per length */
    vec2_t difference = subtract_vec2 (b, a);
    double distance   = length_vec2   (difference);
    int n_points      = ceil          (distance) + 1;
    double brightness = distance / n_points;

    /* multiply the given color's alpha by the brightnesss to get the color
     * for each point drawn */
    color_t point_color = multiply_alpha (color, brightness);

    /* this is the step along the line to take from one endpoint to the other */
    vec2_t direction = divide_vec2_scalar   (difference, distance);
    vec2_t step      = multiply_vec2_scalar (direction, distance / n_points);

    /* sweep across the line from one endpoint to the other plotting each point */
    vec2_t position = a;
    for (i = 0; i < n_points; i++) {

        draw_point (buffer, position, point_color);
        position = add_vec2 (position, step);
    }
}
