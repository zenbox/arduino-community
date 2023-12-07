﻿MobaTools
=========
### Arduino library for model railroaders ( and maybe for others too 😉 )
This library contains functionality
- to control up to 16 servos with speed control
- to control up to 6 stepper motors with accelerating and decelerating
- to softly turn leds on and off ( bulb simulation )
- to implement time functions without use of delay().
- to debounce and evaluate up to 32 buttons/switches (per instance)

### Installation

Released versions can be installed by means of the library manager in arduino IDE

#### supported processors
- AVR ATmega
- AVR ATtiny, if it has the 16-bit timer 1 and a SPI or USI hardware
- STM32F103x processors ( the [core of Roger Clark](https://github.com/rogerclarkmelbourne/Arduino_STM32) must be used )
- ESP32 ( minimum core version is 1.0.6 )
- ESP8266 ( with some restrictions, Stepper via SPI does not work )

A documentation file in [german](MobaTools-241-de.pdf) and [english](MobaTools-241-en.pdf) is provided.

**Latest changes:**

| Version |  Release Date  | Description
| ------- |  ------------  | -----------
| 2.4.3 | 2022-04-28| small bugfix to suppress warnings (issue [#10](https://github.com/MicroBahner/MobaTools/issues/10) )
| | | bugfix for setZero(position) for steppers in FULLSTEP mode
| | | bugfix with AccelStepper like method names ( compiler error if both libs have been included )
| | | 2 additional timer examples commented in english
| | | 1 additional stepper example
| 2.4.2 | 2021-12-23| fix bug in MoToStepper.setSpeedSteps ( was possible divide by zero )
| | | ESP crashed
| 2.4.1 | 2021-11-12| fix typo: arduino.h -> Arduino.h ( created an error on linux )
| | | fix bug and minor enhancements in MoToButtons.h
| | | fix some documentation errors
| | | Unfortunately the german documentation is missing in this release. You can download it directly here from GitHub
| 2.4.0 | 2021-05-28| ESP32 processor is now supported
| | | ATTiny processors that have timer 1 (16-bit) and SPI or USI hadware are supported
| | | some optimizing for 32-Bit processors, which leads to significant faster steprates for ESP32 and STM32
| | | ESP32 creates servopulses by hardware ( they are much more stable )
| 2.3.1 | 2020-11-07| fix error in doSteps: motor did not stop with doSteps(0) and no ramp
| 2.3.0 | 2020-07-31| MoToButtons: The longpress event is already triggered when the time for longpress expires, not when the button is released
| | | New class MoToTimebase to create a trigger in regular intervals
| | | When setting the zero point, steps per rotation can be changed also.
| | | fix error in rotate(0) - did not stop under special circumstances
| 2.2.0 | 2020-02-23| MoToButtons: new method 'clicked' to recognize single and double clicks.
| | | MoToButtons: if all buttons/switches are simply connected to input pins, MoToButtons can read them alone without a callback function.
| 2.1.1 | 2020-02-08| Fix error in MoToServo: stopped working with more than one Servo
| 2.1.0 | 2020-02-05| new class 'MoToButtons' to manage multiple buttons and switches ( up to 32 in one instance )
| | | MoToTimer: new method 'expired', which returns a 'true' only with the first call after the timer has expired
| 2.0.0 | 2020-01-13| managing an enable pin for steppers is possible
| | | new method 'getSpeedSteps' returns actual speed
| | | ESP8266 is now supported ( with limitations regarding stepper mode: only step/dir is possible )
| | | classnames have changed ( the old names can still be used for compatibility, but should not be used in new sketches)

### Classes

#### MoToServo: 
Can control up to 16 servos. Compatible with arduino servo lib, but allows to control 
the speed of the servo.

#### MoToStepper: 
A class to control stepper motors. The arduino sketch is not blocked while 
the stepper is moving. After setting a reference point, the stepper can be positioned 
absolutely just like a servo. But without the angle limitation of 0--180 degrees.
V1.1: Ramps can be defined to accelerate/decelerate the Stepper.

#### MoToSoftLed: 
Allows easy softon / softoff of leds. It works on all digital outputs.

#### MoToTimer: 
Allows easy nonblocking timedelays in sketches. You don't have to bother with millis() directly

#### MoToButtons: 
Manage up to 32 buttons and switches with debounce and event handling (pressed, released, short press, long press, click and double click ) in one instance. The buttons/switches can be read in via a user callback function. This enables matrix arrangements and e.g. I2C port expander to be used.


#### Additional Info:
Apart from class MoToButtons, there is no special function that has to be called in the loop frequently. You can even use the delay() function in the loop while servos and steppers are moving.

The library uses Timer1 for all classes (AVR). V1.0: from this version on, timer 3 is used instead of timer 1 if available.
On the STM32F1 platform, timer 4 is used.
MoToButtons and MoToTimer do not use any timer und should be compatible with all plattforms.

With ESP8266 waveform creating fuctions, and IO-interrupts are used. Because the core functions could not be used for this purpose, the integrated functions tone(), analogWrite() and servo() cannot be used together with MobaTools.
To overcome this problem, there exists an additional class exclusively for the ESP8266 platform:
#### MoToPwm ( only ESP8266 ):
Contains Methods to create pwm and tone outputs.


