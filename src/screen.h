#ifndef SCREEN_H
#define SCREEN_H

#include "pixel_buffer.h"
#include "oscilloscope.h"

/* idealized input voltage when the power supply is plugged in */
#define MAINS_AC_VOLTAGE 110

/* the "dirtiness" of the mains AC signal */
#define MAINS_AC_NOISE 0.1

/* frequency of the AC signal in hertz */
#define MAINS_AC_FREQUENCY 60

/* the number of samples that the oscilloscope can hold in memory */
#define OSCILLOSCOPE_MEMORY 10240

/* the number of signals that the oscilloscope can display */
#define OSCILLOSCOPE_N_SIGNALS 1

/* the horizontal scaling for the screen's debug oscilloscope */
#define OSCILLOSCOPE_TIME_SCALE 0.1

/* the vertical scaling for the screen's debug oscilloscope */
#define OSCILLOSCOPE_VOLTAGE_SCALE 170

/* the context for a crt/vector display simulation */
typedef struct screen_t {

    /* time of the last advancement */
    double last_time;

    /* oscilloscope for debugging signals */
    oscilloscope_t *oscilloscope;

    /* POWER SUPPLY STUFF */

    /* idealized ac voltage from the mains power
     * this is what we want/expect the input voltage into the power supply to be */
    double ideal_mains_ac_voltage; /* i.e. 110 volts */

    /* this is the final output voltage after being filtered through the power supply */
    double power_supply_output_voltage;

} screen_t;

/* create a new instance of a simulation */
screen_t *create_screen (double time);

/* destroy a previously created instance */
void destroy_screen (screen_t *screen);

/* generate a mains AC signal */
double generate_mains_ac_signal (double time, double rms, double frequency, double noise);

/* power on the power supply */
void power_on (screen_t *screen);

/* power off the power supply */
void power_off (screen_t *screen);

/* advance the simulation given the current time */
void advance_screen (screen_t *screen, double time);

/* render the current state of the simulation onto a pixel buffer */
void draw_screen (screen_t *screen, pixel_buffer_t *buffer);

/* draw the oscilloscope for debugging purposes */
void draw_screen_oscilloscope (screen_t *screen, pixel_buffer_t *buffer);

#endif /* SCREEN_H */
