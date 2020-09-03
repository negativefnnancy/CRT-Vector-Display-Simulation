#include <stdlib.h>
#include <stdint.h>
#include <stdarg.h>
#include <stdio.h>
#include <time.h>

#include "util.h"

void die_with_message (char *format, ...) {

    va_list argp;
    va_start (argp, format);
    vfprintf (stderr, format, argp);
    va_end (argp);
    exit (EXIT_FAILURE);
}

double white_noise () {

    return rand () / (double) RAND_MAX * 2 - 1;
}

void init_noise () {

    srand (time (0));
}

void *traverse_ring_buffer (void *buffer, size_t n_items, size_t size, void **pointer) {

    /* save the old pointer for convenience */
    void *old_pointer = *pointer;

    /* increment the pointer by one item */
    *((uint8_t **) pointer) += size;

    /* if the point now points past the end of the buffer,
     * then loop it back aroud to the start of the buffer */
    if (*((uint8_t **) pointer) == (uint8_t *) buffer + n_items * size)
        *((uint8_t **) pointer) = buffer;

    /* return the old pointer value for convenience's sake */
    return old_pointer;
}
