//***********************************************************
// RC Car Controller with Servo and DC Motors via Bluetooth
//***********************************************************

#include <Servo.h>                  // Servo library to control servo motors
#include <SoftwareSerial.h>

// Servo & Bluetooth Module pin definitions for steering & communication
#define servoPin 5                  // Servo motor pin
#define motorPin 3
#define RxD 9                       // Bluetooth module RX pin for receiving data
#define TxD 11                      // Bluetooth module TX pin for sending data

Servo myServo;                      // Servo
Servo myMotor;                      // DC
int servoVal;                       // Int for storing servo angle

SoftwareSerial BTSerial(RxD, TxD);

char command; 			            // Int to store app command from smartphone app
int speedCar = 90; 	                // Default speed for movement
int speedStop = 91;                 // Default speed for stop


void setup() {
    // Initialize servo
    myServo.attach(servoPin);
    myMotor.attach(motorPin);

    // Start serial communication
    Serial.begin(9600);
    BTSerial.begin(9600);
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


void zero() {
    // 90 degrees for center
    servoVal = 90;
    myServo.write(servoVal);
}


// Stop
void stopCar() {
    for(int i = 0; i < 10; i++) {
      myMotor.write(speedStop);     // Initialize dc motor ~96
      speedStop++;    
      Serial.print(speedStop);
      Serial.print('\n');
    }

    speedStop = 90;
    myMotor.write(speedStop);
    Serial.print(speedStop);
}


// Move car forward -- first command!
void goAhead() {
    zero();                         // Straighten out
    
    speedCar += 10;
    myMotor.write(speedCar);        // Increment 10 -> 106
    Serial.print(speedCar);
    Serial.print('\n');
}


// Move car backward
void goBack() {
    zero();                         // Straighten out

    speedCar = 88;
    myMotor.write(speedCar);        // Initialize reverse ~88 (constant speed)
    Serial.print(speedCar);
    Serial.print('\n');
}


// Turn right
void goRight() {                    // 105 degrees for a right turn (reverse angle)
    servoVal = 105;
    myServo.write(servoVal);             
}


// Turn left
void goLeft() {
    servoVal = 72;                  // 72 degrees for a left turn (reverse angle)
    myServo.write(servoVal);               
}


// Diagonal movements -- arc for 3 seconds
void goAheadRight() {
    servoVal = 105;                 // Slight right (reverse angle)
    myServo.write(servoVal);        

    speedCar = 96;
    speedCar += 10;
    myMotor.write(speedCar);        // goAhead
    Serial.print(speedCar);
    Serial.print('\n');
}

void goAheadLeft() {
    servoVal = 72;                  // Slight left (reverse angle)
    myServo.write(servoVal);        

    speedCar = 96;
    speedCar += 10;
    myMotor.write(speedCar);        // goAhead
    Serial.print(speedCar);
    Serial.print('\n');
}

void goBackRight() {
    servoVal = 105;                 // Slight right (reverse angle)
    myServo.write(servoVal);        

    speedCar = 88;
    myMotor.write(speedCar);        // goBack
    Serial.print(speedCar);
    Serial.print('\n');
}

void goBackLeft() {
    servoVal = 72;                  // Slight left (reverse angle)
    myServo.write(servoVal);        

    speedCar = 88;
    myMotor.write(speedCar);        // goBack
    Serial.print(speedCar);
    Serial.print('\n');
}


// Loop
void loop() {
    if (BTSerial.available()) {
        command = BTSerial.read();  // Read incoming byte from app
        Serial.write(command);

        /* Map commands to functionality */
        switch (command) {
            // Servo
            case 'R':               // Tap/Hold right arrow
                goRight();  
                break;
            case 'L':               // Tap/Hold left arrow
                goLeft();
                break;

            // DC
            case 'F':               // Tap/Hold up arrow
                goAhead();
                break;
            case 'B':               // Tap/Hold down arrow
                goBack();
                break;

            // Servo & DC
            case 'G':               // Tap/Hold up right arrow
                goAheadRight();
                break;
            case 'D':               // Tap/Hold up left arrow
                goAheadLeft();
                break;
            case 'N':
                goBackRight();      // Tap/Hold down right arrow
                break;
            case 'C':
                goBackLeft();       // Tap/Hold down left arrow
                break;
            case 'S':                                
                stopCar();          // Automatically observed after button release
                break;
            case 'H':
                zero();             // Tap/Hold middle arrow
                break;
        }
    }
}