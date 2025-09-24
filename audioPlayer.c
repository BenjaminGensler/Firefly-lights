#include <SoftwareSerial.h>
#include <DFRobotDFPlayerMini.h>

const int button1Pin = 2;
const int button2Pin = 3;

SoftwareSerial mySerial(10, 11); // RX, TX
DFRobotDFPlayerMini myDFPlayer; // DFPlayer object for mp3 reader module
//Used the below documentation for functions of DFPlayer Mini
//https://github.com/jonnieZG/DFPlayerMini

void setup() {
  pinMode(button1Pin, INPUT_PULLUP);
  pinMode(button2Pin, INPUT_PULLUP);

  // Start software serial for DFPlayer Mini communication
  mySerial.begin(9600);
  
  // Initialize Serial for debugging
  Serial.begin(9600);

  if (!myDFPlayer.begin(mySerial)) {
    Serial.println("Unable to begin DFPlayer Mini:");
    while(true);
  }
  myDFPlayer.volume(20); // Set volume (0-30)
}

void loop() {
  if (digitalRead(button1Pin) == LOW) {
    Serial.println("Button 1 pressed"); // Debug message
    myDFPlayer.stop(); // Stop any current playback
    myDFPlayer.playFile(1); // Play 0001.mp3
    delay(500); // Debounce
  }
  if (digitalRead(button2Pin) == LOW) {
    Serial.println("Button 2 pressed"); // Debug message
    myDFPlayer.stop(); // Stop any current playback
    myDFPlayer.playFile(2); // Play 0002.mp3
    delay(500); // Debounce
  }
}

//// Simple pin state tester
// const int testPin = 2; // Change to the pin you want to test

// void setup() {
//   pinMode(testPin, INPUT_PULLUP); // Use internal pull-up
//   Serial.begin(9600);
// }

// void loop() {
//   int state = digitalRead(testPin);
//   Serial.print("Pin ");
//   Serial.print(testPin);
//   Serial.print(" state: ");
//   Serial.println(state); // HIGH = not pressed, LOW = pressed
//   delay(500);
// }