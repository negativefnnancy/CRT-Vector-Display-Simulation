#ifndef PIXEL_BUFFER_H
#define PIXEL_BUFFER_H

#include <stdint.h>

#include <SDL2/SDL.h>

#include "color.h"

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

/* return a pixel value appropriate for a given buffer given a normalized color value */
Uint32 make_pixel (pixel_buffer_t *buffer, color_t color);

/* get the address of a desired pixel given its index */
void *get_pixel_address (pixel_buffer_t *buffer, size_t index);

/* get the address of a desired pixel given its x and y coordinates */
void *get_pixel_address_from_coordinates (pixel_buffer_t *buffer, int x, int y);

/* set a pixel value given the coordinates */
void set_pixel (pixel_buffer_t *buffer, int x, int y, Uint32 pixel);

/* get a pixel value given the coordinates */
Uint32 get_pixel (pixel_buffer_t *buffer, int x, int y);

/* set a pixel value given the coordinates and normalized color value */
void set_pixel_color (pixel_buffer_t *buffer, int x, int y, color_t color);

/* get a nomalized color from a pixel value value given the coordinates */
color_t get_pixel_color (pixel_buffer_t *buffer, int x, int y);

/* blend a given color with an existing pixel's color at the given coordinates
 * and then overwrite that pixel with the new blended color */
void blend_pixel (pixel_buffer_t *buffer, int x, int y, color_t color);

#endif /* PIXEL_BUFFER_H */
