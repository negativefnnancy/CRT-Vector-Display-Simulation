#include <stdlib.h>
#include <math.h>

#include "screen.h"
#include "util.h"

screen_t *create_screen (double time) {

    screen_t *screen = (screen_t *) calloc (1, sizeof (screen_t));
    screen->oscilloscope = create_oscilloscope (OSCILLOSCOPE_N_SIGNALS,
                                                OSCILLOSCOPE_MEMORY);
    screen->last_time = time;
    return screen;
}

void destroy_screen (screen_t *screen) {

    destroy_oscilloscope (screen->oscilloscope);
    free (screen);
}

double generate_mains_ac_signal (double time, double rms, double frequency, double noise) {

    double peak_voltage;
    double pure_signal;
    double noise_signal;

    /* calculate the neutral to peak voltage given the rms voltage */
    peak_voltage = sqrt (2) * rms;

    /* calculate the ideal sine waveform */
    pure_signal = sin (time * 2 * M_PI * frequency) * peak_voltage;

    /* get the noise component */
    noise_signal = white_noise () * pure_signal * noise;

    /* dirty up the signal LOL */
    return pure_signal + noise_signal;
}

void power_on (screen_t *screen) {

    /* powering on will be simply plugging it in! */
    screen->ideal_mains_ac_voltage = MAINS_AC_VOLTAGE;
}

void power_off (screen_t *screen) {

    /* and powering it off will be unplugging it, voltage goes to 0, dun dun dun */
    screen->ideal_mains_ac_voltage = 0;
}

void advance_screen (screen_t *screen, double time) {

    int i;

    /* calculate delta time since last advance */
    double last_time = screen->last_time;
    double delta_time = time - last_time;

    /* testing the oscilloscope!! */
    for (i = 0; i < 100; i++) {

        double dt = delta_time / 100;
        printf ("%f\n", dt);
        log_sample_oscilloscope (screen->oscilloscope, 0,
                                 generate_mains_ac_signal (last_time + i * dt, 120, 60, 0.05),
                                 dt);
    }

    /* save the last time */
    screen->last_time = time;
}

void draw_screen (screen_t *screen, pixel_buffer_t *buffer) {

}

void draw_screen_oscilloscope (screen_t *screen, pixel_buffer_t *buffer) {

    /* render the oscilloscope for debugging */
    draw_oscilloscope (screen->oscilloscope, buffer, OSCILLOSCOPE_TIME_SCALE,
                                                     OSCILLOSCOPE_VOLTAGE_SCALE);
}
