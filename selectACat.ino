// See the README for a complete "talk-through" of the project.

#include <Servo.h>

//Establish which pins attach to which items.

Servo lidServo;
const int foodDispensorPin = 3;
const int catInRangePin = 4;
const int dispensorAtTopPin = 5;
const int micPin = 6;
const int bowlWeightPin = 7;
const int selectorFactor0 = 8;
const int selectorFactor1 = 9;
const int selectorFactor2 = 10;
const int selectorFactor3 = 11;
const int selectorFactor4 = 12;
const int thereIsACatPin = 13;

const int lidClosedAngle = 90;
const int lidOpenAngle = 175;

// Varaibles
int doorsOpen = 0;
int ration = 3;
int selectorPosition = 0;
int lidAngle = 90;

void setup() {
  Serial.begin(9600);
  // Establich which pins are innies, which are outies
  lidServo.attach(A0);
  pinMode(thereIsACatPin, OUTPUT);
  pinMode(foodDispensorPin, OUTPUT);
  pinMode(dispensorAtTopPin, INPUT_PULLUP);
  pinMode(bowlWeightPin, INPUT_PULLUP);
  pinMode(catInRangePin, INPUT_PULLUP);
  pinMode(micPin, INPUT_PULLUP);
  pinMode(selectorFactor0, INPUT_PULLUP);
  pinMode(selectorFactor1, INPUT_PULLUP);
  pinMode(selectorFactor2, INPUT_PULLUP);
  pinMode(selectorFactor3, INPUT_PULLUP);
  pinMode(selectorFactor4, INPUT_PULLUP);
}

void loop() {
  // See where the selector is and change the ration as needed;

  // un-comment when rotary switch is all hooked up.
   rationRead();

  // Because we're using digital PULLUP, LOW is HIGH and HIGH is LOW for all switches & sensors.
  // an LED indicates that the cat is close enough. This is more for the humans, but who knows? Cats can learn?
  if (digitalRead(catInRangePin) == LOW) {
    digitalWrite(thereIsACatPin, HIGH);
  } else {
    digitalWrite(thereIsACatPin, LOW);
  }

  // If there is a cat in range & it meows the right meow.
  if (digitalRead(catInRangePin) == LOW && digitalRead(micPin) == LOW) {
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

  // Now the cat eats. The doors remain open until it walks out of range.

   while (digitalRead(catInRangePin) == LOW && doorsOpen == 1) {
    
  }

  
  if (doorsOpen == 1) {
    for (lidAngle = lidOpenAngle; lidAngle >= lidClosedAngle; lidAngle--) {
      lidServo.write(lidAngle);
      delay(60);
    }
    doorsOpen = 0;
  }
}

void feed() {
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

// uses binary to give each input from the rotary switch a unique value to add to the int, sets ration acordingly. This is mapped out, see the red grid notebook.
// straight up is 1, going clockwise from there. The flat part of the shaft is what was used to idicate direction.
void rationRead() {
  selectorPosition = (!digitalRead(selectorFactor0) | !digitalRead(selectorFactor1) * 2 | !digitalRead(selectorFactor2) * 4 | !digitalRead(selectorFactor3) * 8 | !digitalRead(selectorFactor4) * 16);
  // TODO Eliminate this if for production. It's here so that one doesn't have to hold the selector switch in place.
  if(selectorPosition == 0) {
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










