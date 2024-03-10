// controller.ino
// This is the main script for controlling the RC car via Arduino Uno.


// Define all pin numbers and initial states here
#define light_FR 14     // LED Front Right  pin A0 for Arduino Uno
#define light_FL 15     // LED Front Left   pin A1
#define light_BBR 16    // LED Back Left    pin A2
#define light_BL 17     // LED Back Right   pin A3

// ...

int command; 			//Int to store app command state.
int speedCar = 100; 	// 50 - 255.
int speed_Coeff = 4;


// Initialization function
void setup() {
    // ...

    Serial.begin(9600);
}


// Move car forward
void goAhead() {

}


// Move car backward
void goBack() {

}


// Turn left
void goLeft() {

}


// Turn right
void goRight() {

}


// Diagonal movements & speed adjustments
void goAheadRight() {

}

void goAheadLeft() {

}


// Stop
void stopCar() {

}


// Loop
void loop() {
    if(Serial.available() > 0) {
        command = Serial.read();
        stopCar();
    }

    // ...
}


// Error handling
void handleError() {

}