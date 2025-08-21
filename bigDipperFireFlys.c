/*
This LED light sequence represents the Big Dipper firefly light sequence 
 -- 6 short blinks from the males (Whith a few extra sets of males to avoid empty space in light)
 -- 6 short blinks from the females
*/

int maleLed1 = 9;         // the PWM pin the LED is attached to
int maleLed2 = 8;        // the PWM pin the second LED is attached to

int femaleLed1 = 7;      // the PWM pin the third LED is attached to
int femaleLed2 = 6;      // the PWM pin the fourth LED is attached to

int brightness = 0;  // how bright the LED is
int fadeAmount = 60;  // how many points to fade the LED by

int brightness2 = 128; // start led2 at mid-brightness (offset)
int fadeAmount2 = -60;  // fade in opposite direction

// Fade speeds (delay in ms for each speed)
int fadeSpeeds[] = {120};
int fadesPerSpeed[] = {6}; // number of fades per speed
int currentSpeed = 0;
int fadeCount = 0;
int numSpeeds = sizeof(fadeSpeeds) / sizeof(fadeSpeeds[0]);

bool malesTurn = true; // Track whose turn it is

void setup() {
  pinMode(maleLed1, OUTPUT);
  pinMode(maleLed2, OUTPUT);
  pinMode(femaleLed1, OUTPUT);
  pinMode(femaleLed2, OUTPUT);
}

void loop() {
  // Blink counters
  static int male1Count = 0;
  static int male2Count = 0;
  static int female1Count = 0;
  static int female2Count = 0;
  static bool male1Started = true;
  static bool male2Started = false;
  static bool female1Started = false;
  static bool female2Started = false;

  // Blink durations
  int onTime = 300;   // ms LED ON
  int offTime = 300;  // ms LED OFF

  // Blink femaleLed1
  if (female1Started) {
    if(female1Count >= 6){
      female1Count = 0;
      male1Started = true;  // male1 starts after female1 finishes
      female1Started = false; // reset female1Started
    }
    digitalWrite(femaleLed1, HIGH);
    delay(onTime);
    digitalWrite(femaleLed1, LOW);
    delay(offTime);
    female1Count++;

    // Start femaleLed2 after 3 blinks of femaleLed1
    if (female1Count == 3) {
      female2Started = true;
    }
  }

  // Blink femaleLed2 if started
  if (female2Started) {
    // Reset female2Count after 6 blinks
    if(female2Count >= 6){
      female2Count = 0;
      male2Started = true; // start male2 after female2 finishes
      female2Started = false; // reset female2Started
    }
    digitalWrite(femaleLed2, HIGH);
    delay(onTime);
    digitalWrite(femaleLed2, LOW);
    delay(offTime);
    female2Count++;
  }

  // Blink maleLed1 if started
  if (male1Started) {
    if(male1Count >= 6){
      male1Count = 0;
      female1Started = true;
      male1Started = false;
    }
    digitalWrite(maleLed1, HIGH);
    delay(onTime);
    digitalWrite(maleLed1, LOW);
    delay(offTime);
    male1Count++;

    // Start maleLed2 after 3 blinks of maleLed1
    if (male1Count == 3) {
      male2Started = true;
    }
  }

  // Blink maleLed2 if started
  if (male2Started && male2Count <= 6) {
    if(male2Count >= 6){
      male2Count = 0;
      female2Started = true;
      male2Started = false;
    }
    digitalWrite(maleLed2, HIGH);
    delay(onTime);
    digitalWrite(maleLed2, LOW);
    delay(offTime);
    male2Count++;
  }
}