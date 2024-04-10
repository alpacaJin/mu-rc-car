//***********************************************************
// RC Car Controller with Servo and DC Motors via Bluetooth
//***********************************************************

#include <Servo.h>                  // Servo library to control servo motors

// Servo & Bluetooth Module pin definitions for steering & communication
#define servoPin 5                  // Servo motor pin
#define motorPin 9
#define BT_RX 7                     // Bluetooth module RX pin for receiving data
#define BT_TX 8                     // Bluetooth module TX pin for sending data

Servo myServo;                      // servo
Servo myMotor;                      // dc
int servoVal;                       // Int for storing servo angle

int command; 			            // Int to store app command from smartphone app
int speedCar = 90; 	                // Default speed


void setup() {
    // Initialize servo
    myServo.attach(servoPin);
    myMotor.attach(motorPin);

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


void zero() {
    // 90 degrees for center
    servoVal = 90;
    myServo.write(servoVal);
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
    servoVal = 120;                  // Slight right (reverse angle)
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
    servoVal = 120;                  // Slight right (reverse angle)
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


// Stop
void stopCar() {
    for(int i = 0; i < 10; i++) {
      myMotor.write(speedCar);
      speedCar++;    
      Serial.print(speedCar);
      Serial.print('\n');
      delay(200);                  // Initialize forward ~96
    }

    speedCar = 91;
    myMotor.write(speedCar);
    Serial.print(speedCar);
}


// Loop
void loop() {
    if (Serial.available() > 0) {
        // Read the incoming byte
        int command = Serial.parseInt(); // Parses an integer from incoming serial data
        
        // Echo the command back to the serial terminal
        Serial.print("Command received: ");
        Serial.println(command);

        switch (command) {
            // servo
            case 1: zero();           break;   
            case 2: goRight();        break;    
            case 3: goLeft();         break;

            // dc
            case 4: stopCar();        break;
            case 5: goAhead();        break;   
            case 6: goBack();         break;

            case 7: goAheadRight();   break;
            case 8: goAheadLeft();    break;
            case 9: goBackRight();    break;
            case 10: goBackLeft();    break;

            delay(10);
    }
}

    /* Preliminary Bluetooth module code */
    // if (Serial.available() > 0) {
    //     command = Serial.read();
    //     stopCar();                     // Stop car before changing directions         

    //     // Decode the command
    //     switch (command) {
    //         case 'F': goAhead();        break;
    //         case 'B': goBack();         break;
    //         case 'R': goRight();        break;
    //         case 'L': goLeft();         break;
    //         case 'I': goAheadRight();   break;
    //         case 'G': goAheadLeft();    break;
    //         case 'J': goBackRight();    break;
    //         case 'H': goBackLeft();     break;
    //     }
    // }
}