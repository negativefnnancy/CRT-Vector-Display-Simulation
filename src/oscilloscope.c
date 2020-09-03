#include <stdlib.h>

#include "oscilloscope.h"

sample_t make_sample (double value, double delta_time) {

    sample_t sample;
    sample.value = value;
    sample.delta_time = delta_time;
    return sample;
}

oscilloscope_t *create_oscilloscope (size_t n_samples) {

    oscilloscope_t *oscilloscope = (oscilloscope_t *) calloc (1, sizeof (oscilloscope_t));
    oscilloscope->n_samples = n_samples;
    oscilloscope->samples = (sample_t *) calloc (n_samples, sizeof (sample_t));
    oscilloscope->ring_pointer = oscilloscope->samples;
    return oscilloscope;
}

void destroy_oscilloscope (oscilloscope_t *oscilloscope) {

    free (oscilloscope->samples);
    free (oscilloscope);
}

sample_t *read_oscilloscope (oscilloscope_t *oscilloscope) {

    /* return the current value pointed to by the ring buffer
     * and then increment/loop the ring pointer for next time */
    return (sample_t *) traverse_ring_buffer (oscilloscope->samples,
                                              oscilloscope->n_samples,
                                              sizeof (sample_t),
                                              (void **) &(oscilloscope->ring_pointer));
}

void log_sample_oscilloscope (oscilloscope_t *oscilloscope,
                              double value, double delta_time) {

    *((sample_t *) traverse_ring_buffer (oscilloscope->samples,
                                         oscilloscope->n_samples,
                                         sizeof (sample_t),
                                         (void **) &(oscilloscope->ring_pointer)))
        = make_sample (value, delta_time);
}