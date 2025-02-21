const int potentiometerPin = A1;
const int buttonPin = 2;
const int ledPins[] = {8, 9, 10, 11};
const int numLeds = 4;

bool lastButtonState = HIGH;
unsigned long lastDebounceTime = 0;
const long debounceDelay = 50;

void setup() {
  Serial.begin(9600);
  pinMode(buttonPin, INPUT_PULLUP);

  for (int i = 0; i < numLeds; i++) {
    pinMode(ledPins[i], OUTPUT);
  }

  Serial.println("Setup completed");
}

void loop() {
  bool buttonState = digitalRead(buttonPin);
  unsigned long currentMillis = millis();

  int sensorValue = analogRead(potentiometerPin);
  int scaledValue = map(sensorValue, 0, 1023, 0, 20);

  int percentage = map(scaledValue, 0, 20, 0 ,100);
  int ledIndex = map(scaledValue, 0, 20, 0, numLeds - 1);

  for (int i = 0; i < numLeds; i++) {
    digitalWrite(ledPins[i], (i == ledIndex) ? HIGH : LOW);
  }

  if (buttonState == LOW && lastButtonState == HIGH && (currentMillis - lastDebounceTime) > debounceDelay) {
    lastDebounceTime = currentMillis;
    lastButtonState = LOW;

    int progressBar = map(scaledValue, 0, 20, 0, 100);
    Serial.print("[");

    for (int i = 0; i < (percentage / 5); i++) Serial.print('#');
    for (int i = (percentage / 5); i < 20; i++) Serial.print('.');

    Serial.print("] ");
    Serial.print(percentage);
    Serial.println("%");
  }
  
  lastButtonState = buttonState;
}