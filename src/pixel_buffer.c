#include "pixel_buffer.h"

pixel_buffer_t make_buffer (void *pixels, int width, int height, SDL_PixelFormat *format) {

    pixel_buffer_t buffer;
    buffer.pixels = pixels;
    buffer.width = width;
    buffer.height = height;
    buffer.format = format;
    return buffer;
}

Uint32 make_pixel (pixel_buffer_t *buffer, color_t color) {

    return SDL_MapRGBA (buffer->format, color.red   * 255,
                                        color.green * 255,
                                        color.blue  * 255,
                                        color.alpha * 255);
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

Uint32 get_pixel (pixel_buffer_t *buffer, int x, int y) {

    return *((Uint32 *) get_pixel_address_from_coordinates (buffer, x, y));
}

void set_pixel_color (pixel_buffer_t *buffer, int x, int y, color_t color) {

    set_pixel (buffer, x, y, make_pixel (buffer, color));
}

color_t get_pixel_color (pixel_buffer_t *buffer, int x, int y) {

    return color_from_pixel (get_pixel (buffer, x, y), buffer->format);
}

void blend_pixel (pixel_buffer_t *buffer, int x, int y, color_t color) {

    /* get the existing color at the pixel destination */
    color_t existing = get_pixel_color (buffer, x, y);

    /* blend the new color on top of the existing color */
    color_t new = alpha_blend (color, existing);

    /* write the new color over the old pixel value */
    set_pixel_color (buffer, x, y, new);
}

void clear_buffer (pixel_buffer_t *buffer, color_t color) {

    /* iterate all the pixels in the buffer */
    Uint32 pixel = make_pixel (buffer, color);
    memset (buffer->pixels,
            pixel,
            buffer->format->BytesPerPixel * buffer->width * buffer->height);
}
