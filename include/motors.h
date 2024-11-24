#ifndef motors_h
#define motors_h

#include <AccelStepper.h>
#include <pinout.h>

/* Step and direction pins*/
#define X_STEP PIN_D7
#define X_DIR PIN_C5

#define Y_STEP PIN_C6
#define Y_DIR PIN_C7

#define E_STEP PIN_B1
#define E_DIR PIN_B0

/* Enable pin for X, Y, and E */
#define XYE_ENABLE_inv PIN_D6

/* All three motor drivers are set to 1/16th microstepping */
#define MICROSTEP (16)
#define STEPS_PER_REV (200*MICROSTEP)

/* The motor driver allows for a minimum pulse width of 1 microsecond. */
#define MIN_PULSE_MICROSEC (2)

/* Conversions */
#define REV_TO_RAD (2*PI)

#define NUM_MOTORS (3)

/* Motor Inversion */
#define DIR_INVERT true
#define STEP_INVERT false
#define EN_INVERT false

/* Variable declarations */
extern AccelStepper* Motors[NUM_MOTORS];

/* Function declarations */
void setupMotors(float maxSpeedRad, float maxAccelRad);
void enableXYE();
void disableXYE();
long radToStep(float rad);
void scaleSpeedAndAccel(AccelStepper** Motors, float maxSpeedRad, float maxAccelRad);

#endif