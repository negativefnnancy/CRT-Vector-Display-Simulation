#include <stdlib.h>

#include "oscilloscope.h"
#include "color.h"
#include "vector.h"
#include "drawing.h"

sample_t make_sample (double value, double delta_time) {

    sample_t sample;
    sample.value = value;
    sample.delta_time = delta_time;
    return sample;
}

signal_t *create_signal (size_t n_samples) {

    signal_t *signal = (signal_t *) calloc (1, sizeof (signal_t));
    signal->n_samples = n_samples;
    signal->samples = (sample_t *) calloc (n_samples, sizeof (sample_t));
    signal->ring_pointer = signal->samples;
    return signal;
}

void destroy_signal (signal_t *signal) {

    free (signal->samples);
    free (signal);
}

oscilloscope_t *create_oscilloscope (size_t n_signals, size_t n_samples) {

    int i;
    oscilloscope_t *oscilloscope = (oscilloscope_t *) calloc (1, sizeof (oscilloscope_t));
    oscilloscope->n_signals = n_signals;
    oscilloscope->signals = (signal_t **) calloc (n_signals, sizeof (signal_t *));
    for (i = 0; i < n_signals; i++)
        oscilloscope->signals[i] = create_signal (n_samples);
    return oscilloscope;
}

void destroy_oscilloscope (oscilloscope_t *oscilloscope) {

    int i;
    for (i = 0; i < oscilloscope->n_signals; i++)
        destroy_signal (oscilloscope->signals[i]);
    free (oscilloscope->signals);
    free (oscilloscope);
}

sample_t *read_oscilloscope (oscilloscope_t *oscilloscope, int signal_id) {

    /* return the current value pointed to by the ring buffer
     * and then increment/loop the ring pointer for next time */
    return (sample_t *)
        traverse_ring_buffer (oscilloscope->signals[signal_id]->samples,
                              oscilloscope->signals[signal_id]->n_samples,
                              sizeof (sample_t),
                              (void **) &(oscilloscope->signals[signal_id]->ring_pointer));
}

void log_sample_oscilloscope (oscilloscope_t *oscilloscope, int signal_id,
                              double value, double delta_time) {

    *((sample_t *)
        traverse_ring_buffer (oscilloscope->signals[signal_id]->samples,
                              oscilloscope->signals[signal_id]->n_samples,
                              sizeof (sample_t),
                              (void **) &(oscilloscope->signals[signal_id]->ring_pointer)))
        = make_sample (value, delta_time);
}

void draw_oscilloscope (oscilloscope_t *oscilloscope, pixel_buffer_t *buffer,
                        double x_scale, double y_scale) {

    /* the end points on the line segment being drawn */
    vec2_t a, b;

    /* current index when iterating the samples and signals */
    int i, j;

    /* the sample being read */
    sample_t *sample;

    /* draw a horizontal line down the middle, marking the origin */
    double center_y = buffer->height / 2.0;
    draw_line (buffer, make_vec2 (0,             center_y),
                       make_vec2 (buffer->width, center_y),
                       make_color (1, 0, 0, 1));

    /* iterate each signal */
    for (j = 0; j < oscilloscope->n_signals; j++) {

        /* iterate each sample
         * by reading n_samples, the ring pointer will loop back around
         * first get the initial sample */
        sample = read_oscilloscope (oscilloscope, j);
        a = make_vec2 (0, center_y - sample->value * center_y / y_scale);
        for (i = 0; i < oscilloscope->signals[j]->n_samples - 1; i++) {

            /* get the subsequent sample */
            sample_t *sample = read_oscilloscope (oscilloscope, j);
            b = make_vec2 (a.x + sample->delta_time * buffer->width / x_scale,
                           center_y - sample->value * center_y / y_scale);
        
            /* draw the line and then shift the second end poit to be the 
             * first endopoint of the line drawn in the following iteration */
            draw_line (buffer, a, b, make_color (1 ,1, 1, 1));
            a = b;
        }
    }
}
