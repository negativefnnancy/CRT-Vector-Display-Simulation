#include "color.h"

color_t make_color (double red, double green, double blue, double alpha) {

    color_t color;
    color.red = red;
    color.green = green;
    color.blue = blue;
    color.alpha = alpha;
    return color;
}

color_t make_white_with_alpha (double alpha) {

    return make_color (1, 1, 1, alpha);
}

color_t color_from_pixel (Uint32 pixel, SDL_PixelFormat *format) {

    /* the non-normalized constituent color components */
    Uint8 red, green, blue, alpha;

    /* extract the color components */
    SDL_GetRGBA (pixel, format, &red, &green, &blue, &alpha);

    /* convert to normalized color value */
    return make_color (red / 255.0, green / 255.0, blue / 255.0, alpha / 255.0);
}

color_t alpha_blend (color_t source, color_t destination) {

    /* alpha and compliment of alpha */
    double alpha      = source.alpha;
    double compliment = 1 - alpha;

    return make_color (source.red * alpha + destination.red * compliment,
                       source.green * alpha + destination.green * compliment,
                       source.blue * alpha + destination.blue * compliment,
                       destination.alpha + (1 - destination.alpha) * alpha);
}
