// ** Notice:
//Given the schematics image provided in this folder there are some issues with the code.
// Please change this code as needed. Thank you!

int led = 9;         // the PWM pin the LED is attached to
int led2 = 8;        // the PWM pin the second LED is attached to

int brightness = 0;  // how bright the LED is
int fadeAmount = 5;  // how many points to fade the LED by

int brightness2 = 128; // start led2 at mid-brightness (offset)
int fadeAmount2 = -5;  // fade in opposite direction

// Fade speeds (delay in ms for each speed)
int fadeSpeeds[] = {30, 10, 60, 10}; // speed 1, 2, 3, 4
int fadesPerSpeed[] = {4, 3, 1, 2}; // number of fades per speed
int currentSpeed = 0;
int fadeCount = 0;
int numSpeeds = sizeof(fadeSpeeds) / sizeof(fadeSpeeds[0]);

void setup() {
  pinMode(led, OUTPUT);
  pinMode(led2, OUTPUT);
}

void loop() {
  analogWrite(led, brightness);
  analogWrite(led2, brightness2);

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
