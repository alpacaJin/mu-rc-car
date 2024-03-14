# RC Car Control System - Lightning MuQueen

This repository hosts the Arduino source code for a remote-controlled car project, including motor management, steering, speed control, and Bluetooth communication. The objective is to enable precise control over the RC car through a custom-built mobile application.

## Features

### Motor Control for Maneuverability

The RC car is equipped with both DC motors and a servo motor, enabling a wide range of movements.

- DC Motors: Four DC motors power the car's movement, with two motors allocated to each side of the car for differential drive capabilities. This setup allows the car to execute forward and backward motions as well as nuanced steering adjustments.
  - goAhead(): Engages all DC motors to propel the car forward
  - goBack(): Reverses the polarity on the DC motors to move the car backward

- Servo Motor: A single servo motor controls the steering mechanism, allowing for precise directional changes. The servo's angle is adjusted to steer the car left or right.
  - goRight(): Adjusts the servo to 135 degrees for turning right
  - goLeft(): Adjusts the servo to 45 degrees for turning left

### Speed Control

Speed adjustments are made through dynamic Pulse Width Modulation (PWM) signal modulation, affecting the DC motors' operation speed. This is achieved by varying the duty cycle of the PWM signals sent to the motors, allowing for real-time speed adjustments during operation.

- Variable speed settings for direct forward and backward movements
- Diagonal movement capabilities
  - goAheadRight(), goAheadLeft(), goBackRight(), and goBackLeft(): Adjusts the speed differential between the two sides of the car

### Bluetooth Module Integration

A Bluetooth module enables wireless communication between the RC car and a custom mobile application, allowing for remote operation.

- Reception of command signals from a mobile application, which are then interpreted by the car's microcontroller to execute specific movements or speed adjsutments
- Support for a broad range of commands, enabling not only directional control but also speed variations and immediate stop actions

## Installation

- Clone the repository
- Upload the provided Arduino script to your Arduino Uno
- Install and configure the mobile app to communicate with the RC car
