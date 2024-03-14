//***********************************************************
// RC Car Controller with Servo and DC Motors via Bluetooth
//***********************************************************

#include <Servo.h>                  // Servo library to control servo motors

// LED Pin Definitions for status and direction indication
#define led_FR 14                   // LED Front Right  pin A0 for Arduino Uno
#define led_FL 15                   // LED Front Left   pin A1
#define led_BR 16                   // LED Back Left    pin A2
#define led_BL 17                   // LED Back Right   pin A3

// Motor Driver Control (DC) Pins
#define motor_IN1 2                 // Motor Driver Right IN1
#define motor_IN2 3                 // Motor Driver Right IN2
#define motor_IN3 4                 // Motor Driver Left IN3
#define motor_IN4 5                 // Motor Driver Left IN4
#define ENA 10                      // Motor Driver Enable A for right side speed control
#define ENB 11                      // Motor Driver Enable B for left side speed control

// Servo & Bluetooth Module pin definitions for steering & communication
#define servoPin 9                  // Servo motor pin
#define BT_RX 7                     // Bluetooth module RX pin for receiving data
// #define BT_TX 8                  // Bluetooth module TX pin for sending data

Servo myServo;                      // Create servo object
int servoVal;                       // Int for storing servo angle

int command; 			            // Int to store app command from smartphone app
int speedCar = 100; 	            // Default speed
int speedCoeff = 4;                 // Coefficient for speed sensitivity adjustment


void setup() {
    // Initialize LED
    pinMode(led_FR, OUTPUT);
    pinMode(led_FL, OUTPUT);
    pinMode(led_BR, OUTPUT);
    pinMode(led_BL, OUTPUT);
    
	// Initialize Motor Driver pins
    pinMode(motor_IN1, OUTPUT);
    pinMode(motor_IN2, OUTPUT);
    pinMode(motor_IN3, OUTPUT);
    pinMode(motor_IN4, OUTPUT);
    pinMode(ENA, OUTPUT);
    pinMode(ENB, OUTPUT);

    // Initialize servo
    myServo.attach(servoPin);

    // Start serial communication
    Serial.begin(9600);
}


// Function prototypes
void goAhead();
void goBack();
void goRight();
void goLeft();
void goAheadRight();
void goAheadLeft();
void goBackRight();
void goBackLeft();
void stopCar();


// Move car forward
void goAhead() {
    digitalWrite(motor_IN1, HIGH);
    digitalWrite(motor_IN2, LOW);
    digitalWrite(motor_IN3, HIGH);
    digitalWrite(motor_IN4, LOW);
    analogWrite(ENA, speedCar);
    analogWrite(ENB, speedCar);
}


// Move car backward
void goBack() {
    digitalWrite(motor_IN1, LOW);   // Reverse polarity compared to going forward
    digitalWrite(motor_IN2, HIGH);
    digitalWrite(motor_IN3, LOW);
    digitalWrite(motor_IN4, HIGH);
    analogWrite(ENA, speedCar);
    analogWrite(ENB, speedCar);
}


// Turn right
void goRight() {
    // 135 degrees for a right turn
    servoVal = 135;
    myServo.write(servoVal);             
}


// Turn left
void goLeft() {
    // 45 degrees for a left turn
    servoVal = 45;
    myServo.write(servoVal);               
}


// Diagonal movements & speed adjustments
void goAheadRight() {
    // Increase speed on left & decrease on right
    analogWrite(ENA, speedCar/speedCoeff);
    analogWrite(ENB, speedCar);

    // Set both sides to move forward
    digitalWrite(motor_IN1, HIGH);
    digitalWrite(motor_IN2, LOW);
    digitalWrite(motor_IN3, HIGH);
    digitalWrite(motor_IN4, LOW);
}

void goAheadLeft() {
    // Increase speed on right & decrease on left
    analogWrite(ENA, speedCar);
    analogWrite(ENB, speedCar/speedCoeff);

    // Set both sides to move forward
    digitalWrite(motor_IN1, HIGH);
    digitalWrite(motor_IN2, LOW);
    digitalWrite(motor_IN3, HIGH);
    digitalWrite(motor_IN4, LOW);
}

void goBackRight() {
    // Decrease speed on left & increase on right
    analogWrite(ENA, speedCar/speedCoeff);
    analogWrite(ENB, speedCar);
    
    // Set both sides to move backwards
    digitalWrite(motor_IN1, LOW);
    digitalWrite(motor_IN2, HIGH);
    digitalWrite(motor_IN3, LOW);
    digitalWrite(motor_IN4, HIGH);
}

void goBackLeft() {
    // Decrease speed on right & increase on left
    analogWrite(ENA, speedCar);
    analogWrite(ENB, speedCar/speedCoeff);

    // Set both sides to move backwards
    digitalWrite(motor_IN1, LOW);
    digitalWrite(motor_IN2, HIGH);
    digitalWrite(motor_IN3, LOW);
    digitalWrite(motor_IN4, HIGH);
}


// Stop
void stopCar() {
    digitalWrite(motor_IN1, LOW);
    digitalWrite(motor_IN2, LOW);
    digitalWrite(motor_IN3, LOW);
    digitalWrite(motor_IN4, LOW);
    digitalWrite(ENA, 0);
    digitalWrite(ENB, 0);
}


// Loop
void loop() {
    if (Serial.available() > 0) {
        command = Serial.read();
        stopCar();                     // Stop car before changing directions         

        // Decode the command
        switch (command) {
            case 'F': goAhead();        break;
            case 'B': goBack();         break;
            case 'R': goRight();        break;
            case 'L': goLeft();         break;
            case 'I': goAheadRight();   break;
            case 'G': goAheadLeft();    break;
            case 'J': goBackRight();    break;
            case 'H': goBackLeft();     break;

            case '0': speedCar = 100;   break;
            case '1': speedCar = 115;   break;
            case '2': speedCar = 130;   break;
            case '3': speedCar = 145;   break;
            case '4': speedCar = 160;   break;
            case '5': speedCar = 175;   break;
            case '6': speedCar = 190;   break;
            case '7': speedCar = 205;   break;
            case '8': speedCar = 220;   break;
            case '9': speedCar = 235;   break;
            case 'q': speedCar = 255;   break;
        }
    }
}