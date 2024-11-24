#include <Arduino.h>
#include <motors.h>

#define sgn(x) ((x) < 0 ? -1 : ((x) > 0 ? 1 : 0))

AccelStepper* Motors[NUM_MOTORS];
AccelStepper Motor1, Motor2, Motor3;

void setupMotors(float maxSpeedRad, float maxAccelRad){
    /* Initialize Motor objects */
    Motor1 = AccelStepper(AccelStepper::DRIVER, X_STEP, X_DIR);
    Motor2 = AccelStepper(AccelStepper::DRIVER, Y_STEP, Y_DIR);
    Motor3 = AccelStepper(AccelStepper::DRIVER, E_STEP, E_DIR);
    Motors[0] = &Motor1;
    Motors[1] = &Motor2;
    Motors[2] = &Motor3;
    for (int i=0; i<NUM_MOTORS; i++){
        /* Set max permissible speed */
        float maxSpeedSteps = radToStep(maxSpeedRad);
        Motors[i]->setMaxSpeed(maxSpeedSteps);
        /* Set acceleration */
        float maxAccelSteps = radToStep(maxAccelRad);
        Motors[i]->setAcceleration(maxAccelSteps);
        /* Set pulse width */
        Motors[i]->setMinPulseWidth(MIN_PULSE_MICROSEC);
        /* Tare all three motors */
        Motors[i]->setCurrentPosition(0);
        /* Invert all motor directions */
        Motors[i]->setPinsInverted(DIR_INVERT, STEP_INVERT, EN_INVERT);
    }
    /* Enable X, Y, and E motors */
    enableXYE();

}

void enableXYE(){
    /* Enable X, Y, and E motors */
    pinMode(XYE_ENABLE_inv, OUTPUT);
    digitalWrite(XYE_ENABLE_inv, LOW);
}

void disableXYE(){
    /* Disable X, Y, and E motors */
    pinMode(XYE_ENABLE_inv, OUTPUT);
    digitalWrite(XYE_ENABLE_inv, HIGH);
}

long radToStep(float rad){
    return (long)((rad/REV_TO_RAD)*STEPS_PER_REV);
}

void scaleSpeedAndAccel(AccelStepper** Motors, float maxSpeedRad, float maxAccelRad){
    /* Find the motor that has to travel the longest distance */
    long longestDistance = 0;
    for (int i=0; i<NUM_MOTORS; i++){
        long thisDistance = abs(Motors[i]->distanceToGo());
        if (thisDistance > longestDistance)
            longestDistance = thisDistance;
    }
    /* If there is no movement, do nothing */
    if (longestDistance == 0)
        return;
    /* Make motor speed and acceleration proportional to distance */
    float maxSpeedSteps = radToStep(maxSpeedRad);
    float maxAccelSteps = radToStep(maxAccelRad);
    for (int i=0; i<NUM_MOTORS; i++){
        long thisDistance = Motors[i]->distanceToGo();
        float scaleFactor = (float)thisDistance/longestDistance;
        /* Speed */
        float thisSpeed = scaleFactor*maxSpeedSteps;
        Motors[i]->setMaxSpeed(thisSpeed);
        /* Acceleration */
        float thisAccel = scaleFactor*maxAccelSteps;
        Motors[i]->setAcceleration(thisAccel);
    }
}