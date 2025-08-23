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
  static int male1Count = 3;
  static int male2Count = 0;
  static int female1Count = 0;
  static int female2Count = 0;
  static bool male1Started = true;
  static bool male2Started = true;
  static bool female1Started = false;
  static bool female2Started = false;

  // Blink durations
  int onTime = 300;   // ms LED ON
  int offTime = 300;  // ms LED OFF

  // Blink both maleLEDs
  while (male1Started && male2Started) {
    if(male1Count >= 6){
      male1Count = 0;
      female1Started = true;  // female1 starts after male1 finishes
      male1Started = false; // reset male1Started
    }
    else{
      digitalWrite(maleLed2, HIGH);
      delay(onTime);
      digitalWrite(maleLed1, HIGH);
      delay(onTime);
      digitalWrite(maleLed2, LOW);
      delay(offTime);
      digitalWrite(maleLed1, LOW);
      delay(offTime);

      male1Count++;
      male2Count++;
    }
  }

  // Blink male2Started & female1Started
  while (male2Started && female1Started) {
    if(male2Count >= 6){

      male2Count = 0;
      female2Started = true;  // female2 starts after male2 finishes
      male2Started = false; // reset male2Started
    }
    else{
      digitalWrite(femaleLed1, HIGH);
      delay(onTime);
      digitalWrite(maleLed2, HIGH);
      delay(onTime);
      digitalWrite(femaleLed1, LOW);
      delay(offTime);
      digitalWrite(maleLed2, LOW);
      delay(offTime);

      male2Count++;
      female1Count++;
    }
  }

  // Blink both femaleLEDs
  while (female1Started && female2Started) {
    if(female1Count >= 6){
      female1Count = 0;
      male1Started = true;  // male1 starts after female1 finishes
      female1Started = false; // reset female1Started
    }
    else{
      digitalWrite(femaleLed2, HIGH);
      delay(onTime);
      digitalWrite(femaleLed1, HIGH);
      delay(onTime);
      digitalWrite(femaleLed2, LOW);
      delay(offTime);
      digitalWrite(femaleLed1, LOW);
      delay(offTime);
      
      female1Count++;
      female2Count++;
    }
  }

  // Blink male1Started & female2Started
  while (male1Started && female2Started) {
    if(female2Count >= 6){
      female2Count = 0;
      male2Started = true;  // male2 starts after female2 finishes
      female2Started = false; // reset female2Started
    }
    else{
      digitalWrite(maleLed1, HIGH);
      delay(onTime);
      digitalWrite(femaleLed2, HIGH);
      delay(onTime);
      digitalWrite(maleLed1, LOW);
      delay(offTime);
      digitalWrite(femaleLed2, LOW);
      delay(offTime);

      male1Count++;
      female2Count++;
    }
  }
}