#include <NewPing.h>

const int markPin = A1;
const int twainPin = A2;
const int offTare = A5;

const int min_lowDist = 34;
const int max_distance = 45;
NewPing sonar(markPin, twainPin, max_distance);

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(offTare, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
    int uS = sonar.ping_median();
    Serial.println(uS / US_ROUNDTRIP_CM);
  
  if (uS / US_ROUNDTRIP_CM > min_lowDist) {
    ledBlink(offTare, 200, 200);
    } else {
    digitalWrite(offTare, LOW);
  }

}

void ledBlink(int blinkingLED, int blinkOnLengthMs, int blinkOffLengthMs) {
  unsigned long startMillis = millis();
  digitalWrite(blinkingLED, HIGH);
  while (millis() < startMillis + blinkOnLengthMs);
  digitalWrite(blinkingLED, LOW);
  while (millis() < startMillis + blinkOffLengthMs + blinkOnLengthMs);
}
