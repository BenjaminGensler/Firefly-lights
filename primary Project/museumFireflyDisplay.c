#include <SoftwareSerial.h>
#include <DFRobotDFPlayerMini.h>
// Define LED pins
const int led1Pin = 5;
const int led2Pin = 6;
const int led3Pin = 7;
const int led4Pin = 8;
const int led5Pin = 9;

const int button1Pin = 2;
const int button2Pin = 3;
const int button3Pin = 4;

int lastButton1State = HIGH;
int lastButton2State = HIGH;
int lastButton3State = HIGH;
int currentTrack = 0; // Tracks 1, 2, 3

SoftwareSerial mySoftwareSerial(10, 11); // RX, TX
DFRobotDFPlayerMini dfPlayer;
//Used the below documentation for functions of DFPlayer Mini
//https://github.com/jonnieZG/DFPlayerMini

void setup() {
  // Initialize LED pins
  pinMode(led1Pin, OUTPUT);
  pinMode(led2Pin, OUTPUT);
  pinMode(led3Pin, OUTPUT);
  pinMode(led4Pin, OUTPUT);
  pinMode(led5Pin, OUTPUT);

  // Initialize button pins
  pinMode(button1Pin, INPUT_PULLUP);
  pinMode(button2Pin, INPUT_PULLUP);
  pinMode(button3Pin, INPUT_PULLUP);

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

// Helper to turn on one LED and turn off others
void setActiveLED(int ledNum) {
  digitalWrite(led1Pin, ledNum == 1 ? HIGH : LOW);
  digitalWrite(led2Pin, ledNum == 2 ? HIGH : LOW);
  digitalWrite(led3Pin, ledNum == 3 ? HIGH : LOW);
  digitalWrite(led4Pin, ledNum == 4 ? HIGH : LOW);
  digitalWrite(led5Pin, ledNum == 5 ? HIGH : LOW);
}

void loop() {
  int button1State = digitalRead(button1Pin);
  int button2State = digitalRead(button2Pin);
  int button3State = digitalRead(button3Pin);
  
  // Button 1: cycle through tracks 1, 2, 3
  if (button1State == LOW && lastButton1State == HIGH) {
    Serial.print("Button 1 pressed, playing track ");
    Serial.println(currentTrack + 1);
    setActiveLED(currentTrack + 1); // LED 1, 2, or 3
    dfPlayer.play(currentTrack * 2 + 1);
    
    currentTrack++;
    if (currentTrack > 2) currentTrack = 0;
    delay(500); // Debounce
  }
  lastButton1State = button1State;

  // Button 2: play track 4
  if (button2State == LOW && lastButton2State == HIGH) {
    Serial.println("Button 2 pressed, playing track 4");
    setActiveLED(4); // LED 4
    dfPlayer.play(7);
    
    delay(500); // Debounce
  }
  lastButton2State = button2State;

  // Button 3: play track 5
  if (button3State == LOW && lastButton3State == HIGH) {
    Serial.println("Button 3 pressed, playing track 5");
    setActiveLED(5); // LED 5
    dfPlayer.play(9);
    
    delay(500); // Debounce
  }
  lastButton3State = button3State;
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