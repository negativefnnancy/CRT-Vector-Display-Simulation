#include "pixel_buffer.h"

pixel_buffer_t make_buffer (void *pixels, int width, int height, SDL_PixelFormat *format) {

    pixel_buffer_t buffer;
    buffer.pixels = pixels;
    buffer.width = width;
    buffer.height = height;
    buffer.format = format;
    return buffer;
}

Uint32 make_pixel (pixel_buffer_t *buffer, double r, double g, double b, double a) {

    return SDL_MapRGBA (buffer->format, r * 255,
                                        g * 255,
                                        b * 255,
                                        a * 255);
}

void *get_pixel_address (pixel_buffer_t *buffer, size_t index) {

    /* multiply the memory offset by the number of bytes per pixel */
    return (uint8_t *) buffer->pixels + index * buffer->format->BytesPerPixel;
}

void *get_pixel_address_from_coordinates (pixel_buffer_t *buffer, int x, int y) {

    /* convert the x and y coordinates into an index value */
    return get_pixel_address (buffer, x + y * buffer->width);
}

void set_pixel (pixel_buffer_t *buffer, int x, int y, Uint32 pixel) {

    void *destination = get_pixel_address_from_coordinates (buffer, x, y);
    memcpy (destination, &pixel, buffer->format->BytesPerPixel);
}

void set_pixel_rgba (pixel_buffer_t *buffer,
                     int x, int y,
                     double r, double g, double b, double a) {

    set_pixel (buffer, x, y, make_pixel (buffer, r, g, b, a));
}
