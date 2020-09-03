#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include "util.h"

void die_with_message (char *format, ...) {

    va_list argp;
    va_start (argp, format);
    vfprintf (stderr, format, argp);
    va_end (argp);
    exit (EXIT_FAILURE);
}
