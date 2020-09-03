#ifndef PIXEL_BUFFER_H
#define PIXEL_BUFFER_H

#include <stdint.h>

#include <SDL2/SDL.h>

/* holds all the data related to a pixel buffer */
typedef struct pixel_buffer_t {

    /* the buffer of raw pixel values */
    void *pixels;

    /* the dimensions of the pixel buffer */
    int width, height;

    /* the pixel format of the buffer */
    SDL_PixelFormat *format;

} pixel_buffer_t;

/* initialize and return a buffer_t struct */
pixel_buffer_t make_buffer (void *pixels, int width, int height, SDL_PixelFormat *format);

/* return a pixel value appropriate for a given buffer
 * given the normalized (0 to 1) component values */
Uint32 make_pixel (pixel_buffer_t *buffer, double r, double g, double b, double a);

/* get the address of a desired pixel given its index */
void *get_pixel_address (pixel_buffer_t *buffer, size_t index);

/* get the address of a desired pixel given its x and y coordinates */
void *get_pixel_address_from_coordinates (pixel_buffer_t *buffer, int x, int y);

/* set a pixel value given the coordinates */
void set_pixel (pixel_buffer_t *buffer, int x, int y, Uint32 pixel);

/* set a pixel value given the coordinates and the normalized component values */
void set_pixel_rgba (pixel_buffer_t *buffer,
                     int x, int y,
                     double r, double g, double b, double a);

#endif /* PIXEL_BUFFER_H */
