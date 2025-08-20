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
int fadeAmount = 20;  // how many points to fade the LED by

int brightness2 = 128; // start led2 at mid-brightness (offset)
int fadeAmount2 = -20;  // fade in opposite direction

// Fade speeds (delay in ms for each speed)
int fadeSpeeds[] = {60};
int fadesPerSpeed[] = {6}; // number of fades per speed
int currentSpeed = 0;
int fadeCount = 0;
int numSpeeds = sizeof(fadeSpeeds) / sizeof(fadeSpeeds[0]);

void setup() {
  pinMode(maleLed1, OUTPUT);
  pinMode(maleLed2, OUTPUT);
  pinMode(femaleLed1, OUTPUT);
  pinMode(femaleLed2, OUTPUT);
}

void loop() {
  analogWrite(maleLed1, brightness);
  analogWrite(maleLed2, brightness2);

  analogWrite(femaleLed1, brightness);
  analogWrite(femaleLed2, brightness2);

  brightness = brightness + fadeAmount;
  brightness2 = brightness2 + fadeAmount2;

  // reverse the direction of the fading at the ends of the fade:
  if (brightness <= 0 || brightness >= 255) {
    fadeAmount = -fadeAmount;
    fadeCount++;

    // Add longer delay when LED is off before fading in again
    if (brightness <= 0 && fadeAmount > 0) {
      delay(1000); // 1000 ms = 1 second, adjust as needed
    }

    // After enough fades at current speed, switch to next speed
    if (fadeCount >= fadesPerSpeed[currentSpeed]) {
      fadeCount = 0;
      currentSpeed = (currentSpeed + 1) % numSpeeds;
    }
  }

  // Reverse led2 at ends
  if (brightness2 <= 0 || brightness2 >= 255) {
    fadeAmount2 = -fadeAmount2;
  }

  // Wait for the current speed's delay
  delay(fadeSpeeds[currentSpeed]);
}