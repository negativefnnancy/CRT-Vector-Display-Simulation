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

/* a single signal of an oscilloscope */
typedef struct signal_t {

    /* the amount of samples the oscilloscope can store in memory */
    size_t n_samples;

    /* the sample memory ring buffer */
    sample_t *samples;

    /* pointer for traversing the ring buffer */
    sample_t *ring_pointer;

} signal_t;

/* instantiate a signal */
signal_t *create_signal (size_t n_samples);

/* destroy a signal instance */
void destroy_signal (signal_t *signal);

/* holds information for an oscilloscope viewer */
typedef struct oscilloscope_t {

    /* the number of signals the oscilloscope can log */
    size_t n_signals;

    /* the signals */
    signal_t **signals;

} oscilloscope_t;

/* create a new oscilloscope instance given a sample buffer size
 * and number of signals */
oscilloscope_t *create_oscilloscope (size_t n_signals, size_t n_samples);

/* destroy a previously created oscilloscope instance */
void destroy_oscilloscope (oscilloscope_t *oscilloscope);

/* read the next sample from the ring buffer for a given signal id */
sample_t *read_oscilloscope (oscilloscope_t *oscilloscope, int signal_id);

/* write the next sample to the ring buffer */
void log_sample_oscilloscope (oscilloscope_t *oscilloscope, int signal_id,
                              double value, double delta_time);

/* render the oscilloscope to a pixel buffer
 * horizontal scale is how many seconds fit on screen
 * and the vertical scale is how many volts fit from center to top and bottom */
void draw_oscilloscope (oscilloscope_t *oscilloscope, pixel_buffer_t *buffer,
                        double x_scale, double y_scale);

#endif /* OSCILLOSCOPE_H */
