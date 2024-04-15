//***********************************************************
// RC Car Controller with Servo and DC Motors via Bluetooth
//***********************************************************

#include <Servo.h>                  // Servo library to control servo motors

// Servo & Bluetooth Module pin definitions for steering & communication
#define servoPin 5                  // Servo motor pin
#define motorPin 9
#define RxD 10                      // Bluetooth module RX pin for receiving data
#define TxD 11                      // Bluetooth module TX pin for sending data

Servo myServo;                      // Servo
Servo myMotor;                      // DC
int servoVal;                       // Int for storing servo angle

SoftwareSerial BTSerial(RxD, TxD);

int incomingA[6];                   // Array to store sequence up t 6
int command; 			            // Int to store app command from smartphone app
int speedCar = 90; 	                // Default speed


void setup() {
    // Initialize servo
    myServo.attach(servoPin);
    myMotor.attach(motorPin);

    // Start serial communication
    Serial.begin(9600);
    BTSerial.begin(38400);
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
      myMotor.write(speedCar);
      speedCar++;    
      Serial.print(speedCar);
      Serial.print('\n');
      delay(200);                   // Initialize forward ~96
    }

    speedCar = 91;
    myMotor.write(speedCar);
    Serial.print(speedCar);
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
void goRight() {
    // 135 degrees for a right turn (reverse angle)
    servoVal = 135;
    myServo.write(servoVal);             
}


// Turn left
void goLeft() {
    // 45 degrees for a left turn (reverse angle)
    servoVal = 45;
    myServo.write(servoVal);               
}


// Diagonal movements -- arc for 3 seconds
void goAheadRight() {
    servoVal = 120;                 // Slight right (reverse angle)
    myServo.write(servoVal);        

    speedCar = 96;
    speedCar += 10;
    myMotor.write(speedCar);        // goAhead
    Serial.print(speedCar);
    Serial.print('\n');

    delay(3000);                    // Wait for 3 seconds
    stopCar();
}

void goAheadLeft() {
    servoVal = 60;                  // Slight left (reverse angle)
    myServo.write(servoVal);        

    speedCar = 96;
    speedCar += 10;
    myMotor.write(speedCar);        // goAhead
    Serial.print(speedCar);
    Serial.print('\n');

    delay(3000);                    // Wait for 3 seconds
    stopCar();
}

void goBackRight() {
    servoVal = 120;                 // Slight right (reverse angle)
    myServo.write(servoVal);        

    speedCar = 88;
    myMotor.write(speedCar);        // goBack
    Serial.print(speedCar);
    Serial.print('\n');

    delay(3000);                    // Wait for 3 seconds
    stopCar();
}

void goBackLeft() {
    servoVal = 60;                  // Slight left (reverse angle)
    myServo.write(servoVal);        

    speedCar = 88;
    myMotor.write(speedCar);        // goBack
    Serial.print(speedCar);
    Serial.print('\n');

    delay(3000);                    // Wait for 3 seconds
    stopCar();
}


// Loop
void loop() {
    if (BTSerial.available() > 0) {
        int incoming = BTSerial.read();                                                 // Read incoming byte from app
        if (incoming != -1) {
            Serial.println(incoming, DEC);
        }

        /*  Parse into command */
        // Store up to six
        if (sequenceIndex < 6) {
            incomingA[sequenceIndex++] = incoming;
        }

        Serial.println(incomingA);

        // Right
        if (incomingA[0] == 128 && incomingA[1] == 128 && incomingA[2] == 120 && 
            incomingA[3] == 248 && incomingA[4] == 128 && incomingA[5] == 120) {        // Tap
            command = 1;
            sequenceIndex = 0;

            if (incomingA[0] != -1) {                                                                                                                   // Next command
                command = 11;
            }
        }

        // Left
        if (incomingA[0] == 0 && incomingA[1] == 128 && incomingA[2] == 120 && 
            incomingA[3] == 128 && incomingA[4] == 120) {                               // Tap
            command = 2;
            sequenceIndex = 0;
        }
        else if (incomingA[0] == 0 && incomingA[1] == 128 && incomingA[2] == 248) {     // Hold
            command = 3;
            if (incomingA[3] == 248 && incomingA[4] == 128 && incomingA[5] == 120) {    // Go until release
                command = 11;
                sequenceIndex = 0;
            }
        }

        // Top
        if (incomingA[0] == 128 && incomingA[1] == 0 && incomingA[2] == 120 && 
            incomingA[3] == 128 && incomingA[4] == 120) {                               // Tap
            command = 4;
            sequenceIndex = 0;
        }
        else if (incomingA[0] == 128 && incomingA[1] == 0 && incomingA[2] == 248) {     // Hold
            command = 5;
            if (incomingA[3] == 248 && incomingA[4] == 128 && incomingA[5] == 120) {    // Go until release
                command = 11;
                sequenceIndex = 0;
            }
        }

        // Bot right
        if (incomingA[0] == 128 && incomingA[1] == 128 && incomingA[2] == 120 && 
            incomingA[3] == 128 && incomingA[4] == 120) {                               // Tap
            command = 11;
            sequenceIndex = 0;
        }
        else if (incomingA[0] == 128 && incomingA[1] == 128 && incomingA[2] == 248) {   // Hold
            command = 6;
            if (incomingA[3] == 248 && incomingA[4] == 128 && incomingA[5] == 120) {    // Go until release
                command = 11;
                sequenceIndex = 0;
            }
        }

        // Top right
        if (incomingA[0] == 248 && incomingA[1] == 0 && incomingA[2] == 120 && 
            incomingA[3] == 128 && incomingA[4] == 120) {                               // Tap
            command = 7;
            sequenceIndex = 0;
        }
        else if (incomingA[0] == 248 && incomingA[1] == 0 && incomingA[2] == 248) {     // Hold
            command = 8;
            if (incomingA[3] == 248 && incomingA[4] == 128 && incomingA[5] == 120) {    // Go until release
                command = 11;
                sequenceIndex = 0;
            }
        }

        // Top left
        if (incomingA[0] == 0 && incomingA[1] == 0 && incomingA[2] == 120 && 
            incomingA[3] == 128 && incomingA[4] == 120) {                               // Tap
            command = 9;
            sequenceIndex = 0;
        }
        else if (incomingA[0] == 0 && incomingA[1] == 0 && incomingA[2] == 248) {       // Hold
            command = 10;
            if (incomingA[3] == 248 && incomingA[4] == 128 && incomingA[5] == 120) {    // Go until release
                command = 11;
                sequenceIndex = 0;
            }
        }


        switch (command) {
            // Servo
            case 1:                 // Hold
                goRight();  
                break;
            case 2:                 // Tap
                goLeft();
                delay(1000);
                stopCar();   
                break;
            case 3:                 // Hold
                goLeft();
                break;

            // DC
            case 4:                 // Tap
                goAhead();
                delay(1000);
                stopCar();   
                break;
            case 5:                 // Hold
                goAhead();
                break;
            case 6:                 // Hold
                goBack();
                break;

            // Servo & DC
            case 7:                 // Tap
                goAheadRight();
                delay(1000);
                stopCar();   
                break;
            case 8:                 // Hold
                goAheadRight();
                break;
            case 9:                 // Tap
                goAheadLeft();
                delay(1000);
                stopCar();   
                break;
            case 10:                // Hold
                goAheadLeft();
                break;
            case 11:                                
                stopCar();
                break;
            delay(10);
        }
    }
}