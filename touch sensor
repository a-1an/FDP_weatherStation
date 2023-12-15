const int touchPin = D2; // the pin where touch sensor is connected
const int ledPin = D0; // the pin where onboard LED is connected

void setup() {
  pinMode(touchPin, INPUT);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  int touchState = digitalRead(touchPin);
  
  if (touchState == HIGH) {
    digitalWrite(ledPin, LOW); // turn on LED when touch sensor is touched
  } else {
    digitalWrite(ledPin, HIGH); // turn off LED when touch sensor is not touched
  }
}
