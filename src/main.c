#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#include <SDL2/SDL.h>

#include "util.h"

/* default window dimensions */
#define WIDTH 640
#define HEIGHT 480

void draw (SDL_Surface *surface) {

    /* get the pixel buffer */
    uint8_t *buffer = (uint8_t *) surface->pixels;

    /* TODO: dont make assumptions about the pixel format */

    /* TODO */
}

int main (int argc, char **argv) {

    SDL_Window *window;
    SDL_Surface *surface;
    SDL_Event event;

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

        /* redraw the screen */
        surface = SDL_GetWindowSurface (window);
        SDL_LockSurface (surface);
        draw (surface);
        SDL_UnlockSurface (surface);
        SDL_UpdateWindowSurface (window);
    }
quit:

    /* cleanup and exit */
    SDL_DestroyWindow (window);
    SDL_Quit ();
    return EXIT_SUCCESS;
}
