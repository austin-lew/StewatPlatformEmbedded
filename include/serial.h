#ifndef serial_h
#define serial_h

#include <motors.h>

/* A class for devices that communicates to the motor driver over serial. Tokenizes and parses commands and their associated values */
class InputMessenger {
    public:
        /* Constructor */
        InputMessenger();
        /* Enumeration of commands */
        typedef enum { TARE=0, RELATIVE_MOVE=1, ABSOLUTE_MOVE=2 }CommandType;
        /* Returns the command char from the latest valid data read from serial */
        CommandType getCommand();
        /* Returns the motor angle, in rad, from the latest valid data read from serial */
        float getMotorAngle(int motorNum);
        /* Checks the serial buffer for any valid data */
        bool getUpdates();
    private:
        /* The command character read from the latest valid read from serial */
        CommandType _command;
        /* The data associated with each transmission */
        float _motorAnglesRad[NUM_MOTORS];
        /* The raw string read from the Rx buffer */
        String _rx;
};

#endif