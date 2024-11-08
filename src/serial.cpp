#include <Arduino.h>
#include <serial.h>

#define DATA_START '<'
#define DELIMITER ','
#define DATA_END '>'

#define TARE_STR "t"
#define RELATIVE_MOVE_STR "r"
#define ABSOLTUE_MOVE_STR "a"

/* Constructor */
InputMessenger::InputMessenger(){}

/* Check the serial for any valid data */
bool InputMessenger::getUpdates(){
    /* If the input buffer is empty, do nothing and return */
    if (!Serial.available()){
        return false;
    }
    /* Get everything from the serial buffer as a string */
    _rx = Serial.readString();
    /* Remove whitespace and make lowercase */
    _rx.replace(" ", "");
    _rx.toLowerCase();
    /* Find the last occurring substring of the form "<a,b,c>" */
    int dataStartIdx = _rx.lastIndexOf(DATA_START);
    int dataEndIdx = _rx.lastIndexOf(DATA_END);
    if (dataStartIdx==-1 || dataEndIdx==-1){
        return false;
    }
    String vecStr = _rx.substring(dataStartIdx+1, dataEndIdx);
    /* Find the delimiters */
    int delim1 = vecStr.indexOf(DELIMITER);
    int delim2 = vecStr.indexOf(DELIMITER, delim1+1);
    int delim3 = vecStr.indexOf(DELIMITER, delim2+1);
    if (delim1<0 || delim2<0 || delim3<0){
        return false;
    }
    /* Extract the command character */
    String commandChar = vecStr.substring(0, delim1);
    /* Store the command character */
    if (commandChar == TARE_STR)
        _command = TARE;
    else if (commandChar == ABSOLTUE_MOVE_STR)
        _command = ABSOLUTE_MOVE;
    else if (commandChar == RELATIVE_MOVE_STR)
        _command = RELATIVE_MOVE;
    else
        return false;
    /* Extract and store the three floats */
    _motorAnglesRad[0] = vecStr.substring(delim1+1, delim2).toFloat();
    _motorAnglesRad[1] = vecStr.substring(delim2+1, delim3).toFloat();
    _motorAnglesRad[2] = vecStr.substring(delim3+1).toFloat();
    return true;
}

/* Return the motor command enum */
InputMessenger::CommandType InputMessenger::getCommand(){
    return _command;
}

/* Return the motor angle */
float InputMessenger::getMotorAngle(int motorNum){
    return _motorAnglesRad[motorNum];
}