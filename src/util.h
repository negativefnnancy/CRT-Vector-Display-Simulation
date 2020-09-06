#ifndef UTIL_H
#define UTIL_H

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

/* exit the program with a fatal error message */
void die_with_message (char *format, ...);

/* generate an evenly distributed random number between -1 and 1 */
double white_noise ();

/* initialize the noise generation */
void init_noise ();

/* traverse a ring buffer */
void *traverse_ring_buffer (void *buffer, size_t n_items, size_t size, void **pointer);

/* return current time in seconds */
double get_time ();

#endif /* UTIL_H */
