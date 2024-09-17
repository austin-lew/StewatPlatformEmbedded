# Embedded pipeline
Make sure you have the PlatformIO extension installed in VSCode.

The main code is [main.cpp](src/main.cpp). This is where the RTOS with motor controller PIDs and RPi 5 commuincation threads live.

Libraries can be included in the [lib](lib) folder or using the PlatformIO Library Manager. [Readme](lib/README) for more info.

Headers will live in the [include](include) folder. [Readme](include/README) for more info.

## Steps to compile and upload:

1. ctrl+alt+b / cmd-shift-b / ctrl-shift-b to Build Project

2. ctrl+alt+u to Upload Firmware

3. ctrl+alt+s to Open Serial Port Monitor