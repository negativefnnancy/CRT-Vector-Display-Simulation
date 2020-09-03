#ifndef COLOR_H
#define COLOR_H

#include <SDL2/SDL.h>

/* a normalized color value with red, green, blue, and alpha components */
typedef struct color_t {

    double red;
    double green;
    double blue;
    double alpha;

} color_t;

/* initialize and return a color_t struct */
color_t make_color (double red, double green, double blue, double alpha);

/* return the color white with a given alpha */
color_t make_white_with_alpha (double alpha);

/* convert a packed pixel value of a given format into a normalized color value */
color_t color_from_pixel (Uint32 pixel, SDL_PixelFormat *format);

/* perform alpha blending given the source and destination colors */
color_t alpha_blend (color_t source, color_t destination);

#endif /* COLOR_H */
