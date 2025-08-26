const int buttonPin = 2;
const int ledPin = 12;

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);
}

static bool lastButtonState = LOW;

void loop() {
  static bool ledOn = false;
  static unsigned long ledOnTime = 0;
  

  bool buttonState = digitalRead(buttonPin);

  // Detect button press (transition from HIGH to LOW)
  if (lastButtonState == HIGH && buttonState == LOW && !ledOn) {
    digitalWrite(ledPin, HIGH);
    ledOn = true;
    ledOnTime = millis();
  }

  // Turn off LED after 10 seconds
  if (ledOn && millis() - ledOnTime >= 10000) {
    digitalWrite(ledPin, LOW);
    ledOn = false;
  }

  lastButtonState = buttonState;
}