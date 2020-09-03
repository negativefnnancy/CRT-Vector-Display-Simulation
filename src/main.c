#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#include <SDL2/SDL.h>

#include "util.h"
#include "screen.h"
#include "pixel_buffer.h"
#include "oscilloscope.h"

/* default window dimensions */
#define WIDTH 640
#define HEIGHT 480

/* the number of samples that the oscilloscope can hold in memory */
#define OSCILLOSCOPE_RESOLUTION 1024

int main (int argc, char **argv) {

    /* SDL stuff */
    SDL_Window *window;
    SDL_Surface *surface;
    SDL_Event event;

    /* amount of time (seconds) since last frame */
    double delta_time;

    /* the simulation state */
    screen_t *screen;

    /* the drawing buffer information */
    pixel_buffer_t buffer;

    /* an oscilloscope for debugging */
    oscilloscope_t *oscilloscope;

    /* initialize SDL */
    if (SDL_Init (SDL_INIT_VIDEO) == -1)
        die_with_message ("Failed to initialize SDL: %s\n", SDL_GetError ());

    /* create a window */
    if (!(window = SDL_CreateWindow ("CRT / Vector Display Simulation",
                                     SDL_WINDOWPOS_UNDEFINED,
                                     SDL_WINDOWPOS_UNDEFINED,
                                     WIDTH, HEIGHT,
                                     SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE)))
        die_with_message ("Failed to create SDL window: %s\n", SDL_GetError ());

    /* create the oscilloscope */
    oscilloscope = create_oscilloscope (OSCILLOSCOPE_RESOLUTION);

    /* create the simulation */
    /* TODO */

    /* main event loop */
    for (;;) {

        /* handle any incoming SDL events */
        while (SDL_PollEvent (&event) != 0)
            switch (event.type) {

                case SDL_QUIT:
                    goto quit;
            }

        /* get the current surface and buffer information */
        surface = SDL_GetWindowSurface (window);
        buffer = make_buffer (surface->pixels, surface->w, surface->h, surface->format);

        /* clear the screen with a background color */
        clear_buffer (&buffer, make_color (0.1, 0.1, 0.1, 1));

        /* render the oscilloscope for debugging */
        draw_oscilloscope (oscilloscope, &buffer, 0.1, 170);

        /* render the current state of the simulation for this frame */
        SDL_LockSurface (surface);
        draw_screen (screen, &buffer);
        SDL_UnlockSurface (surface);
        SDL_UpdateWindowSurface (window);

        /* advance the simulation for the next frame */
        delta_time = 1.0 / 60; /* TODO: a real delta time */
        advance_screen (screen, delta_time);
    }
quit:

    /* cleanup and exit */
    /* TODO: destroy the simulation */
    destroy_oscilloscope (oscilloscope);
    SDL_DestroyWindow (window);
    SDL_Quit ();
    return EXIT_SUCCESS;
}
