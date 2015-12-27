#include "HX711.h"

const int thereIsACatPin = 13;
const int weighCorrectCatPin = 4;
const int scaleData = A3;
const int scaleClock = A4;

HX711 scale(scaleData, scaleClock);
float calibration_factor = -4700;

float readingTally = 0;
int readingNumber = 0;
float highReading = 0;
float lowReading = 1000;
float averageReading = 0;
float medianCatWeight = 0;

void setup() {
  Serial.begin(9600);
  pinMode(thereIsACatPin, OUTPUT);
  pinMode(weighCorrectCatPin, INPUT_PULLUP);

  // initialize the scale
  scale.set_scale(calibration_factor);
  scale.tare();  //Reset the scale to 0
}

void weighIn() {
  unsigned long startMillis = millis();
  while (digitalRead(weighCorrectCatPin) == LOW && millis() - startMillis < 2000) {
    ledBlink(thereIsACatPin, 50, 50);
    readScale();
  }
  while (digitalRead(weighCorrectCatPin) == LOW){
    if(highReading - lowReading < 1 && lowReading > 5){
      medianCatWeight = averageReading;
      digitalWrite(thereIsACatPin, HIGH);
      delay(2000);
      digitalWrite(thereIsACatPin, LOW);
    } else {
      startMillis = millis();
      while(millis() - startMillis < 4500){
        ledBlink(thereIsACatPin, 1000, 500);
      }
    }
  }
  readingTally = 0;
  readingNumber = 0;
  highReading = 0;
  lowReading = 1000;
  averageReading = 0;
  Serial.println(medianCatWeight);
}

void ledBlink(int blinkingLED, int blinkOnLengthMs, int blinkOffLengthMs) {
  unsigned long startMillis = millis();
  digitalWrite(blinkingLED, HIGH);
  while (millis() < startMillis + blinkOnLengthMs);
  digitalWrite(blinkingLED, LOW);
  while (millis() < startMillis + blinkOffLengthMs + blinkOnLengthMs);
}

void readScale() {
  float currentReading = scale.get_units();
  readingTally += currentReading;
  readingNumber += 1;
  if(highReading < currentReading){
    highReading = currentReading;
  }
  if(lowReading > currentReading){
    lowReading = currentReading;
  }
  averageReading = readingTally / readingNumber;
}




