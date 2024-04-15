# RC Car Control System - Lightning MuQueen

This repository hosts the Arduino source code for a remote-controlled car project, including motor management, steering, speed control, and Bluetooth communication. The objective is to enable precise control over the RC car through an Arduino microprocessor and an available mobile application, ArduCar.

## Features

### Motor Control for Maneuverability

The RC car is equipped with both a DC and servo motor, enabling a wide range of movements.

- DC Motor: One DC motor powers the car's movement at the back end of the car to support the movement capabilities of two back wheels. This setup allows the car to execute forward and backward motions as well as nuanced, diagonal steering adjustments.
  - goAhead(): Engages the DC motor to propel the car forward
  - goBack(): Reverses the polarity on the DC motor to move the car backward

- Servo Motor: A single servo motor controls the steering mechanism at the front end of the car, allowing for precise directional changes of two front wheels. The servo's angle is adjusted to steer the car left or right.
  - goRight(): Adjusts the servo to 72 degrees for turning right (reversed to account for upside-down attachment)
  - goLeft(): Adjusts the servo to 105 degrees for turning left (...)
 
- Diagonal movement capabilities:
  - goAheadRight(), goAheadLeft(), goBackRight(), and goBackLeft(): Combines speed and steering capabilities for arc-like movement

### Speed Control

Speed adjustments are made through dynamic Pulse Width Modulation (PWM) signal modulation, affecting the DC motors' operation speed. This is achieved by incrementing or decrementing, respectively, the PWM signals sent to the motors, allowing for real-time speed adjustments during operation.
 
### Additional Control

- zero(): Resets servo motor angle to 90 to straighten out
- stopCar(): Resets dc motor polarity to 90 to stop all movement

### Bluetooth Module Integration

A Bluetooth module enables wireless communication between the RC car and an available mobile application called ArduCar, allowing for remote operation.

- Reception of command signals from a mobile application, which are then interpreted by the car's microcontroller to execute specific movements or speed adjustments
- Support for a broad range of command states (functionality, followed by cease)

## Installation

- Clone the repository
- Upload the provided Arduino script to your Arduino Uno IDE
- Configure digital pins with respect to your microprocessor setup -- compile & upload
- Install and configure the mobile app to communicate with the RC car & test
