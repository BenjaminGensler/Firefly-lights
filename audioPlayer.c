#include <SoftwareSerial.h>
#include <DFRobotDFPlayerMini.h>

const int button1Pin = 2;
const int button2Pin = 3;

SoftwareSerial mySoftwareSerial(10, 11); // RX, TX
DFRobotDFPlayerMini dfPlayer;
//Used the below documentation for functions of DFPlayer Mini
//https://github.com/jonnieZG/DFPlayerMini

void setup() {
  pinMode(button1Pin, INPUT_PULLUP);
  pinMode(button2Pin, INPUT_PULLUP);

  // Start software serial for DFPlayer Mini communication
  Serial.begin(9600); 
  mySoftwareSerial.begin(9600);

  Serial.println("Initializing DFPlayer Mini...");

  if (!dfPlayer.begin(mySoftwareSerial)) {  // Use softwareSerial to communicate with mp3.
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1. Please recheck the connection!"));
    Serial.println(F("2. Please insert the SD card!"));
    while(true);
  }

  dfPlayer.volume(20);  // Set volume value (0~30).
  dfPlayer.EQ(DFPLAYER_EQ_NORMAL);
  dfPlayer.outputDevice(DFPLAYER_DEVICE_SD);

  delay(500);

  // Play file 0001.mp3 in root folder
  dfPlayer.play(1);

  // If you want to play from a specific folder, use:
  // dfPlayer.playFolder(1, 1); // Play 0001.mp3 in folder 01

  Serial.println("Playing file...");
}

void loop() {
  if (digitalRead(button1Pin) == LOW) {
    Serial.println("Button 1 pressed"); // Debug message
    dfPlayer.stop(); // Stop any current playback
    dfPlayer.play(1); // Play 0001.mp3
    delay(500); // Debounce
  }
  if (digitalRead(button2Pin) == LOW) {
    Serial.println("Button 2 pressed"); // Debug message
    dfPlayer.stop(); // Stop any current playback
    dfPlayer.play(2); // Play 0002.mp3
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
