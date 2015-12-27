// See the README for a complete "talk-through" of the project.

#include <Servo.h>
#include <NewPing.h>
#include <HX711.h>

//Establish which pins attach to which items.

Servo lidServo;
const int markPin = A1;
const int twainPin = A2;
const int scaleData = A3;
const int scaleClock = A4;
const int foodDispensorPin = 3;
const int weighCorrectCatPin = 4;
const int dispensorAtTopPin = 5;
const int reservoirLowLED = 6;
const int bowlWeightPin = 7;
const int selectorFactor0 = 8;
const int selectorFactor1 = 9;
const int selectorFactor2 = 10;
const int selectorFactor3 = 11;
const int selectorFactor4 = 12;
const int thereIsACatPin = 13;


const int lidClosedAngle = 93;
const int lidOpenAngle = 175;

const int max_distance = 20;
NewPing sonar(markPin, twainPin, max_distance);

HX711 scale(scaleData, scaleClock);
float calibration_factor = -4700;

// Varaibles
float medianCatWeight = 0;
int doorsOpen = 0;
int ration = 3;
int selectorPosition = 0;
int lidAngle = lidClosedAngle;
float allowedWeightVariance = 1;

// variables for weigh-in
float readingTally = 0;
int readingNumber = 0;
float highReading = 0;
float lowReading = 1000;
float averageReading = 0;

void setup() {
  Serial.begin(9600);
  // Establich which pins are innies, which are outies
  lidServo.attach(A0);
  pinMode(thereIsACatPin, OUTPUT);
  pinMode(reservoirLowLED, OUTPUT);
  pinMode(foodDispensorPin, OUTPUT);
  pinMode(dispensorAtTopPin, INPUT_PULLUP);
  pinMode(weighCorrectCatPin, INPUT_PULLUP);
  pinMode(correctCatWeightPin, INPUT_PULLUP);
  pinMode(selectorFactor0, INPUT_PULLUP);
  pinMode(selectorFactor1, INPUT_PULLUP);
  pinMode(selectorFactor2, INPUT_PULLUP);
  pinMode(selectorFactor3, INPUT_PULLUP);
  pinMode(selectorFactor4, INPUT_PULLUP);

  // initialize the scale
  scale.set_scale(calibration_factor);
  scale.tare();  //Reset the scale to 0
}

void loop() {
  // check the distance from the lid to the top of the food pile in the reservoir
  int uS = sonar.ping_median();
  if (uS / US_ROUNDTRIP_CM > 6) {
    digitalWrite(reservoirLowLED, HIGH);
  } else {
    digitalWrite(reservoirLowLED, LOW);
  }

  // See where the selector is and change the ration as needed;
  rationRead();

  // when scale is empty, tare if the baseline drifts too much.
  if(abs(scale.get_units()) >= 0.1 && scale.get_units() < 1){
    scale.tare();
  }

  // push a button to weigh in the correct cat,
  // sets the medianCatWeight if a good reading is achieved
  if (digitalRead(weighCorrectCatPin) == LOW) {
    weighIn();
  }

  // If it reads the cat weight range, set this number to the new median & open up
  // during open-time, keep checking for the weight to drop and stay low for a second then close door.
  // also check for weight to jump by 1/4 a cat and stay high for a second then sound a buzzer
  // buzzer cuts when the weight drops to original cat weightish
  // if there is still a second cat after 3 seconds, the door closes.

  // ? is it a constant power draw? This might be a problem, might need another source if it interferes with other powers.

  // Because we're using digital PULLUP, LOW is HIGH and HIGH is LOW for all switches & sensors
  if (abs(scale.get_units() - medianCatWeight) < allowedWeightVariance) {
    digitalWrite(thereIsACatPin, HIGH);
  } else {
    digitalWrite(thereIsACatPin, LOW);
  }

  // If the cat weighs the right ammount
  // todo: make this a weight range rather than a switch
  if (digitalRead(correctCatWeightPin) == LOW) {
    // Open the lid to the open angle
    for (lidAngle = lidClosedAngle; lidAngle < lidOpenAngle; lidAngle++) {
      lidServo.write(lidAngle);
      delay(60);
    }
    doorsOpen = 1;
    // drop the aloted food portion(s).
    feed();
    delay(2000);
  }

  // Now the cat eats. The doors remain open until it leaves the scale.

  while (digitalRead(correctCatWeightPin) == LOW && doorsOpen == 1) {

  }

  // checking to be sure the doors are open, then closing because the cat is off the scale.
  if (doorsOpen == 1) {
    for (lidAngle = lidOpenAngle; lidAngle >= lidClosedAngle; lidAngle--) {
      lidServo.write(lidAngle);
      delay(60);
    }
    doorsOpen = 0;
  }
}

void feed() {
  // use the too-much-food function?
  // if there's not much food in the bowl and the doors are open, the hopper starts dropping portions of food.
  if (doorsOpen == 1 && digitalRead(bowlWeightPin) == HIGH) {
    // start rotating the motor. When it gets back to the top it checks weight (a higher value than above) and to see that it's under ration before continuing with the rotate.
    Serial.println("inside if feed zone, ration:");
    Serial.println(ration);
    for (int i = 0 ; doorsOpen == 1 && digitalRead(bowlWeightPin) == HIGH && ration > i ; i++) {
      // dispensor at top will be determined by a contact to a metal plate on a disc that rotates with the dispensor ball,
      // so when it hits that plate it'll be oriented to the fill position. When it starts back up, it'll still be in contact for a bit
      Serial.println("inside of feed zone");
      while (digitalRead(dispensorAtTopPin) == LOW) {
        // rotates out of the plate zone
        digitalWrite(foodDispensorPin, HIGH);
      }
      while (digitalRead(dispensorAtTopPin) == HIGH) {
        // keeps rotating until it gets back to the plate.
        digitalWrite(foodDispensorPin, HIGH);
      }
    }
    digitalWrite(foodDispensorPin, LOW);
  }
}

void ledBlink(int blinkingLED, int blinkOnLengthMs, int blinkOffLengthMs) {
  unsigned long startMillis = millis();
  digitalWrite(blinkingLED, HIGH);
  while (millis() < startMillis + blinkOnLengthMs);
  digitalWrite(blinkingLED, LOW);
  while (millis() < startMillis + blinkOffLengthMs + blinkOnLengthMs);
}

void weighIn() {
  unsigned long startMillis = millis();
  while (digitalRead(weighCorrectCatPin) == LOW && millis() - startMillis < 2000) {
    ledBlink(thereIsACatPin, 50, 50);
    readScale();
  }
  while (digitalRead(weighCorrectCatPin) == LOW) {
    if (highReading - lowReading < 1 && lowReading > 5) {
      medianCatWeight = averageReading;
      digitalWrite(thereIsACatPin, HIGH);
      delay(2000);
      digitalWrite(thereIsACatPin, LOW);
    } else {
      startMillis = millis();
      while (millis() - startMillis < 4500) {
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

void readScale() {
  float currentReading = scale.get_units();
  readingTally += currentReading;
  readingNumber += 1;
  if (highReading < currentReading) {
    highReading = currentReading;
  }
  if (lowReading > currentReading) {
    lowReading = currentReading;
  }
  averageReading = readingTally / readingNumber;
}


// uses binary to give each input from the rotary switch a unique value to add to the int, sets ration acordingly. This is mapped out, see the red grid notebook.
// straight up is 1, going clockwise from there. The flat part of the shaft is what was used to idicate direction.
void rationRead() {
  selectorPosition = (!digitalRead(selectorFactor0) | !digitalRead(selectorFactor1) * 2 | !digitalRead(selectorFactor2) * 4 | !digitalRead(selectorFactor3) * 8 | !digitalRead(selectorFactor4) * 16);
  // TODO Eliminate this if-statement for production. It's here so that one doesn't have to hold the selector switch in place.
  if (selectorPosition == 0) {
    selectorPosition = 13;
  }
  switch (selectorPosition) {
    case 9:
      ration = 1;
      break;
  }
  switch (selectorPosition) {
    case 11:
      ration = 2;
      break;
  }
  switch (selectorPosition) {
    case 13:
      ration = 3;
      break;
  }
  switch (selectorPosition) {
    case 15:
      ration = 4;
      break;
  }
  switch (selectorPosition) {
    case 24:
      ration = 5;
      break;
  }
  switch (selectorPosition) {
    case 26:
      ration = 6;
      break;
  }
  switch (selectorPosition) {
    case 28:
      ration = 7;
      break;
  }
  switch (selectorPosition) {
    case 30:
      ration = 8;
      break;
  }
  switch (selectorPosition) {
    case 25:
      ration = 9;
      break;
  }
  switch (selectorPosition) {
    case 27:
      ration = 10;
      break;
  }
  switch (selectorPosition) {
    case 29:
      ration = 11;
      break;
  }
  switch (selectorPosition) {
    case 31:
      ration = 12;
      break;
  }
  switch (selectorPosition) {
    case 8:
      ration = 13;
      break;
  }
  switch (selectorPosition) {
    case 10:
      ration = 14;
      break;
  }
  switch (selectorPosition) {
    case 12:
      ration = 15;
      break;
  }
  switch (selectorPosition) {
    case 14:
      ration = 16;
      break;
  }
}










