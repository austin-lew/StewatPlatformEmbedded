# Embedded pipeline
This is the software for the motor controller board, which translates instructions from the RPi into physical stepper motor movements.

Upon power-up, the device scans the serial port (via the Mini USB connector) for commands issued by the RPi.

## Configuration
### Motor Configuration
In [motors.h](./include/motors.h), macro definitions are used to configure the following:
- Microstepping (default: 1/16th)
- MCU pinouts for step, direction, and enable pins
- Motor count
- Minimum pulse width for motor driver input step

### Serial Configuration
In [serial.cpp](./src/serial.cpp), macro definisions are used to configure the following:
- Data start, stop, and delimiter bytes (default:, all data is in the form `<a, b, c, d>` -- ex. `<r, 0.12, 0.90, 1.77>`)
- Strings used to indicate the type of command (default: "t" for tare, "r" for relative move, "a" for absolute move)
- More information on the serial communication is detailed in a later section.

### Kinematics Configuration
In [main.cpp](./src/main.cpp), macro definitions are used to configure the following:
- Minimum and maximum motor displacements in rad (default: +/- PI/2)
- Maximum angular speed in rad/s (default: 2PI rad/s)
- Angular acceleration in rad/s^2 (default: 6PI rad/s^2)

Once configured, upload to the board by connecting the USB

## Setup
1. Connect three stepper motors to connectors X, Y, and E.
2. Plug in the 24V power supply to the motor controller board and power on.

## Serial Communication Guide
The *Serial Hardware Interfacing Tether* (S.H.I.T.) is a state-of-the-art serial communication protocol for transmitting instructions and data between the RPi and motor
 controller. Commands sent from the RPi to the motor controller must be in the following format:

    <instruction>
or

    <instruction, rad1, rad2, rad3>
Where *instruction* is an instruction character and *rad1*, *rad2*, and *rad3* are the motor angles in radian associated with the instruction. 
### Instructions
There are three instructions that can be sent to the motor controller: HOME, RELATIVE_MOVE, and ABSOLUTE MOVE.
| Instruction | Character | Command | Description |
| ----------- | --------- |---------| ----------- |
| HOME        | `h`       |`<h>`| Cuts power to motors to let them drop to hardstop |
| RELATIVE_MOVE | `r`     |`<r,rad1,rad2,rad3>`|Rotates the motors by the desired radians, relative to the current position. |
| ABSOLUTE_MOVE | `a`     |`<a,rad1,rad2,rad3>`| Rotates the motors to the desired position in radians, relative to their zero position. |
#### HOME
- Instruction character: `t`. 
- Does not require any motor angles.
- The motors will:
    1. Cut power and drop to the hard stops.
    2. Wait 1 second.
    3. Set its current positions to $-\frac{\pi}{3}$ rad. 
    4. Enable absolute move commands
    5. Transmit `TARE` on the serial port.
- Positive is clockwise.
- Once successfully tared, the motor controller will transmit back `TARE` to confirm with the RPi.
#### RELATIVE_MOVE
- Instruction character: `r`
- The motors will accelerate to a set speed and stop once they have travelled the values of *rad1*, *rad2*, and *rad3*. 
- Positive is clockwise. 
- For example, if the motors are currently at `(1,1,1)`, the command `<r, 1, 0, -1>` will bring the motors to a final position of `(2,1,0)`. 
- **Warning**: The motor controller ignores minimum and maximum rotation bounds when performing RELATIVE_MOVE instructions. This means that this instruction may cause a crash if the wrong data values are sent. 
#### ABSOLUTE_MOVE
- Instruction character: `a`
- The motors will accelerate to a set speed and stop once they are at the positions described by *rad1*, *rad2*, and *rad3*. These positions are relative to their zero position.
- Positive is clockwise. 
- For example, the command `<a, 1, 0, -1>` will bring the motors to a final position of `(1,0,-1)` regardless of their starting position. 
- If the commanded motor position exceeds the preset minimum and maximum rotation bounds, the motor controller will rotate the motors only as far as these bounds.
- The motor controller will not allow an ABSOLUTE_MOVE if it has not yet been tared. If this is attempted, it will return the following message: `Absolute move failed: Motor is not tared`.

### Operation
#### 1. Home Platform
Since the steppers are currently operated with an open loop control, a homing sequence is required upon startup. Use `HOME` commands to move the platform to its home position and calibrate its motor positions.
#### 2. Verify Homed
Once successfully homed, the motor controller will transmit string `HOME` to serial. Ensure that this is received before proceeding.
#### 3. Run Motors
From this point onwards, `ABSOLUTE_MOVE` commands should be used to control the position of the motors indefinitely. 

## Additional Notes
- The motor controller makes its beset effort to keep all three motors *synchronized*. This means that all three motors will start and stop at the same time, regardless of the angle that each motor has to travel. Therefore, motors that need to travel further will also rotate and accelerate faster to compensate. This is in an attempt to rotate the Stewart platform in a "straight line"
- When a new command is received from the RPi while the previous one was executing, the new command will override the old command. The motors will attempt to smoothly transition from to the new command. However, if this happens too frequently, this may cause the motors to lose synchronization over time.
- Whitespace in serial commands are ignored. 
- Serial commands are not case sensitive.
- Any incomplete serial commands are ignored. 
