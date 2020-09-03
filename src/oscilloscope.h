#ifndef OSCILLOSCOPE_H
#define OSCILLOSCOPE_H

#include "util.h"
#include "pixel_buffer.h"

/* a sample with a variable delta time since previous sample */
typedef struct sample_t {

    /* the actual sample value */
    double value;

    /* the amount of time that has passed since the previous sample */
    double delta_time;

} sample_t;

/* function to initialize and return a sample */
sample_t make_sample (double value, double delta_time);

/* holds information for an oscilloscope viewer */
typedef struct oscilloscope_t {

    /* the amount of samples the oscilloscope can store in memory */
    size_t n_samples;

    /* the sample memory ring buffer */
    sample_t *samples;

    /* pointer for traversing the ring buffer */
    sample_t *ring_pointer;

} oscilloscope_t;

/* create a new oscilloscope instance given a sample buffer size */
oscilloscope_t *create_oscilloscope (size_t n_samples);

/* destroy a previously created oscilloscope instance */
void destroy_oscilloscope (oscilloscope_t *oscilloscope);

/* read the next sample from the ring buffer */
sample_t *read_oscilloscope (oscilloscope_t *oscilloscope);

/* write the next sample to the ring buffer */
void log_sample_oscilloscope (oscilloscope_t *oscilloscope,
                              double value, double delta_time);

/* render the oscilloscope to a buffer */

#endif /* OSCILLOSCOPE_H */
