#ifndef BUFFER_H
#define BUFFER_H

#include <stdint.h>

#include <SDL2/SDL.h>

/* holds all the data related to a pixel buffer */
typedef struct buffer_t {

    /* the buffer of raw pixel values */
    void *pixels;

    /* the dimensions of the pixel buffer */
    int width, height;

    /* the pixel format of the buffer */
    SDL_PixelFormat *format;

} buffer_t;

/* initialize and return a buffer_t struct */
buffer_t make_buffer (void *pixels, int width, int height, SDL_PixelFormat *format);

/* return a pixel value appropriate for a given buffer
 * given the normalized (0 to 1) component values */
Uint32 make_pixel (buffer_t *buffer, double r, double g, double b, double a);

/* get the address of a desired pixel given its index */
void *get_pixel_address (buffer_t *buffer, size_t index);

/* get the address of a desired pixel given its x and y coordinates */
void *get_pixel_address_from_coordinates (buffer_t *buffer, int x, int y);

/* set a pixel value given the coordinates */
void set_pixel (buffer_t *buffer, int x, int y, Uint32 pixel);

/* set a pixel value given the coordinates and the normalized component values */
void set_pixel_rgba (buffer_t *buffer, int x, int y,
                                       double r, double g, double b, double a);

#endif /* BUFFER_H */
