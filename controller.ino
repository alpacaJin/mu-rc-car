//***********************************************************
// RC Car Controller with Servo and DC Motors via Bluetooth
//***********************************************************

#include <Servo.h>                  // Servo library to control servo motors

// Servo & Bluetooth Module pin definitions for steering & communication
#define servoPin 5                  // Servo motor pin
#define BT_RX 7                     // Bluetooth module RX pin for receiving data
#define BT_TX 8                     // Bluetooth module TX pin for sending data

Servo myServo;                      // Create servo object
int servoVal;                       // Int for storing servo angle

int command; 			            // Int to store app command from smartphone app
int speedCar = 96; 	                // Default speed


void setup() {
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
    myServo.write(speedCar);        // Initialize forward ~96

    speedCar += 10;
    myServo.write(speedCar);        // Increment 10 -> 106
    Serial.print(speedCar);
}


// Move car backward
void goBack() {
    speedCar = 88;
    myServo.write(speedCar);        // Initialize reverse ~88
 
    speedCar -= 5;
    myServo.write(speedCar);        // Decrement 5 -> 83
}


// Turn right
void goRight() {
    // 0 degrees for a right turn
    servoVal = 0;
    myServo.write(servoVal);             
}


// Turn left
void goLeft() {
    // 180 degrees for a left turn
    servoVal = 180;
    myServo.write(servoVal);               
}


void zero() {
    // 90 degrees for center
    servoVal = 90;
    myServo.write(servoVal);
}


// Diagonal movements & speed adjustments
void goAheadRight() {
    // Increase speed on left & decrease on right

    // Set both sides to move forward
}

void goAheadLeft() {
    // Increase speed on right & decrease on left

    // Set both sides to move forward
}

void goBackRight() {
    // Decrease speed on left & increase on right
    
    // Set both sides to move backwards
}

void goBackLeft() {
    // Decrease speed on right & increase on left

    // Set both sides to move backwards
}


// Stop
void stopCar() {
    speedCar = 96;
    myServo.write(speedCar);
}


// Loop
void loop() {
    if (Serial.available() > 0) {
        // Read the incoming byte
        int command = Serial.parseInt(); // Parses an integer from incoming serial data
        
        // Echo the command back to the serial terminal (optional):
        Serial.print("Command received: ");
        Serial.println(command);

        switch (command) {
            // servo
            case 1: zero();           break;   
            case 2: goRight();        break;    
            case 3: goLeft();         break;

            // dc
            case 4: goAhead();        break;   
            case 5: goBack();         break;

            case 6: stopCar();        break;

            // case 5: goAheadRight();   break;    // dc
            // case 6: goAheadLeft();    break;    // dc
            // case 7: goBackRight();    break;    // dc
            // case 8: goBackLeft();     break;    // dc

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