// Instruction/ Notice:
// For this code follow the same set up as audioPlayerSchematics but remove the buttons.
// Only the speaker and player are required for this code.

#include <SoftwareSerial.h>
#include <DFRobotDFPlayerMini.h>

SoftwareSerial mySoftwareSerial(10, 11); // RX, TX
DFRobotDFPlayerMini dfPlayer;

void setup() {
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
  // Nothing here
}