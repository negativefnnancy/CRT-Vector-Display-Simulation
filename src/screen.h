#ifndef SCREEN_H
#define SCREEN_H

#include "buffer.h"

/* idealized input voltage when the power supply is plugged in */
#define MAINS_AC_VOLTAGE 110

/* the "dirtiness" of the mains AC signal */
#define MAINS_AC_NOISE 0.1

/* frequency of the AC signal in hertz */
#define MAINS_AC_FREQUENCY 60

/* the context for a crt/vector display simulation */
typedef struct screen_t {

    /* POWER SUPPLY STUFF */

    /* idealized ac voltage from the mains power
     * this is what we want/expect the input voltage into the power supply to be */
    double ideal_mains_ac_voltage; /* i.e. 110 volts */

    /* this is the final output voltage after being filtered through the power supply */
    double power_supply_output_voltage;

} screen_t;

/* generate a mains AC signal */
double generate_mains_ac_signal (double time, double rms, double frequency, double noise);

/* power on the power supply */
void power_on (screen_t *screen);

/* power off the power supply */
void power_off (screen_t *screen);

/* advance the simulation by a given amount of delta time */
void advance_screen (screen_t *screen, double delta_time);

/* render the current state of the simulation onto a pixel buffer */
void draw_screen (screen_t *screen, buffer_t *buffer);

#endif /* SCREEN_H */