#include <math.h>

#include "screen.h"
#include "util.h"

double generate_mains_ac_signal (double time, double rms, double frequency, double noise) {

    double peak_voltage;
    double pure_signal;
    double noise_signal;

    /* calculate the neutral to peak voltage given the rms voltage */
    peak_voltage = sqrt (2) * rms;

    /* calculate the ideal sine waveform */
    pure_signal = sin (time * 2 * M_PI) * peak_voltage;

    /* get the noise component */
    noise_signal = white_noise () * pure_signal;

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

void advance_screen (screen_t *screen, double delta_time) {

}

void draw_screen (screen_t *screen, buffer_t *buffer) {

    /* this is all just temporary, i just want to test the mains AC signal generator */
}

