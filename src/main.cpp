#include <Arduino.h>
#include <AccelStepper.h>
#include <MultiStepper.h>
#include <pinout.h>
#include <motors.h>
#include <serial.h>

#define MIN_MOTOR_ANGLE_RAD (-90*DEG_TO_RAD)
#define MAX_MOTOR_ANGLE_RAD (90*DEG_TO_RAD)

#define MAX_SPEED_RAD (1*REV_TO_RAD)
#define MAX_ACCEL_RAD (3*REV_TO_RAD)

#define SERIAL_BAUD_RATE (115200)

/* When performing relative moves, we scale down speed and acceleration for safety */
#define RELATIVE_MOVE_FACTOR (0.25)

bool TARED = false;

void setup() {
    /* Setup serial */
    Serial.begin(SERIAL_BAUD_RATE);
    Serial.setTimeout(2);
    /* Setup motors */
    setupMotors(MAX_SPEED_RAD, MAX_ACCEL_RAD);
    pinMode(LED_PIN, OUTPUT);
}

void loop() {
    /* This is an instance of the communication with the Pi */
    InputMessenger rPi;
    /* If we have a new serial command, parse it and store it */
    if(Serial.available() && rPi.getUpdates()){
        /* Get motor angles from command */
        long motorSteps[NUM_MOTORS] = {0};
        for (int i=0; i<NUM_MOTORS; i++){
            /* Convert radians to steps and store them */
            motorSteps[i] = radToStep(rPi.getMotorAngle(i));
        }
        /* Go through all three possible commands: tare, absolute move, and relative move */
        switch(rPi.getCommand()){
            /* If we received a TARE command, set the current position of the motors to the desired value */
            case InputMessenger::TARE:{
               for (int i=0; i<NUM_MOTORS; i++){
                    Motors[i]->setCurrentPosition(motorSteps[i]);
                }
                /* Let the Pi know that we have successfully tared */
                TARED = true;
                Serial.println("TARE"); 
                break;
            }
            case InputMessenger::ABSOLUTE_MOVE:{
                if (!TARED){
                    Serial.println("Absolute move failed: Motor is not tared");
                    break;
                }
                for (int i=0; i<NUM_MOTORS; i++){
                    /* Prevent the motor from over-rotating or under-rotating */
                    long minMotorAngleSteps = radToStep(MIN_MOTOR_ANGLE_RAD);
                    long maxMotorAngleSteps = radToStep(MAX_MOTOR_ANGLE_RAD);
                    long motorStepConstrained = constrain(motorSteps[i], minMotorAngleSteps, maxMotorAngleSteps);
                    Motors[i]->moveTo(motorStepConstrained);
                }
                /* Scale speed and acceleration such that all motors arrive at the same time */
                scaleSpeedAndAccel(Motors, MAX_SPEED_RAD, MAX_ACCEL_RAD);
                break;
            }
            case InputMessenger::RELATIVE_MOVE:{
                for (int i=0; i<NUM_MOTORS; i++){
                    Motors[i]->move(motorSteps[i]);
                }
                /* Scale speed and acceleration such that all motors arrive at the same time */
                scaleSpeedAndAccel(Motors, RELATIVE_MOVE_FACTOR*MAX_SPEED_RAD, RELATIVE_MOVE_FACTOR*MAX_ACCEL_RAD);
                break;
            }
        }
    }
    /* Run all motors */
    for (int i=0; i<NUM_MOTORS; i++){
        Motors[i]->run();
    }
}

