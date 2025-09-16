#include <SoftwareSerial.h>
#include <DFRobotDFPlayerMini.h>

const int button1Pin = 2;
const int button2Pin = 3;

SoftwareSerial mySerial(10, 11); // RX, TX
DFRobotDFPlayerMini myDFPlayer;

void setup() {
  pinMode(button1Pin, INPUT_PULLUP);
  pinMode(button2Pin, INPUT_PULLUP);

  mySerial.begin(9600);
  Serial.begin(9600);

  if (!myDFPlayer.begin(mySerial)) {
    Serial.println("Unable to begin DFPlayer Mini:");
    while(true);
  }
  myDFPlayer.volume(20); // Set volume (0-30)
}

void loop() {
  if (digitalRead(button1Pin) == LOW) {
    myDFPlayer.play(1); // Play 0001.mp3
    delay(500); // Debounce
  }
  if (digitalRead(button2Pin) == LOW) {
    myDFPlayer.play(2); // Play 0002.mp3
    delay(500); // Debounce
  }
}