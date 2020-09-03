#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#include <SDL2/SDL.h>

#include "util.h"
#include "screen.h"
#include "buffer.h"

/* default window dimensions */
#define WIDTH 640
#define HEIGHT 480

int main (int argc, char **argv) {

    /* SDL stuff */
    SDL_Window *window;
    SDL_Surface *surface;
    SDL_Event event;

    /* amount of time (seconds) since last frame */
    double delta_time;

    /* the simulation state */
    screen_t screen;

    /* the drawing buffer information */
    buffer_t buffer;

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

        /* render the current state of the simulation for this frame */
        SDL_LockSurface (surface);
        draw_screen (&screen, &buffer);
        SDL_UnlockSurface (surface);
        SDL_UpdateWindowSurface (window);

        /* advance the simulation for the next frame */
        delta_time = 1.0 / 60; /* TODO: a real delta time */
        advance_screen (&screen, delta_time);
    }
quit:

    /* cleanup and exit */
    SDL_DestroyWindow (window);
    SDL_Quit ();
    return EXIT_SUCCESS;
}
