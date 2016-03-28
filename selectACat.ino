// See the README for a complete "talk-through" of the project.

#include <Servo.h>
#include <NewPing.h>
#include <HX711.h>

//Establish which pins attach to which items.

Servo doorServo;

const int markPin = A1;
const int twainPin = A2;
const int scaleData = A3;
const int scaleClock = A4;
const int deterrentDevice = 2;
const int foodDispensorPin = 3;
const int weighCorrectCatPin = 4;
const int dispensorAtTopPin = 5;
const int reservoirLowLED = 6;

const int thereIsACatPin = 13;


const int doorClosedAngle = 93;
const int doorOpenAngle = 175;

const int max_distance = 20;
NewPing sonar(markPin, twainPin, max_distance);

HX711 scale(scaleData, scaleClock);
float calibration_factor = -4700;

// Varaibles
float medianCatWeight = 0;
int doorOpen = 0;
int ration = 3;
int selectorPosition = 0;
int doorAngle = doorClosedAngle;
float allowedWeightVariance = 1;
const int minimumPossibleCat = 6;

// variables for weigh-in
float readingTally = 0;
int readingNumber = 0;
float highReading = 0;
float lowReading = 1000;
float averageReading = 0;

void setup() {
  Serial.begin(9600);
  // Establich which pins are innies, which are outies
  doorServo.attach(A0);
  pinMode(deterrentDevice, OUTPUT);
  pinMode(thereIsACatPin, OUTPUT);
  pinMode(reservoirLowLED, OUTPUT);
  pinMode(foodDispensorPin, OUTPUT);
  pinMode(dispensorAtTopPin, INPUT_PULLUP);
  pinMode(weighCorrectCatPin, INPUT_PULLUP);

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
  if (abs(scale.get_units()) >= 0.05 && scale.get_units() < 0.1) {
    scale.tare();
  }

  // for testing purposes
  Serial.print("Scale reading: ");
  Serial.println(scale.get_units());

  // Because we're using digital PULLUP, LOW is HIGH and HIGH is LOW for all switches

  // push a button to weigh in the correct cat,
  // sets the medianCatWeight if a good reading is achieved
  if (digitalRead(weighCorrectCatPin) == LOW) {
    weighIn();
  }
  
  // first see that there is a cat (>6lbs) then read its weight
  if (scale.get_units() > minimumPossibleCat) {
    // get a reading and set it for this fn
    float catOnScaleWeight = readCatWeight(true);
    Serial.print("catOnScale: ");
    Serial.println(catOnScaleWeight);

    // see if in range
    if (abs(catOnScaleWeight - medianCatWeight) <= allowedWeightVariance) {
      // make this the new median weight
      medianCatWeight = catOnScaleWeight;
      Serial.print("New Median Cat Weight: ");
      Serial.println(medianCatWeight);
      // do the things for the right cat
      digitalWrite(thereIsACatPin, HIGH);
      openDoor();

      bool stillFeeding = true;
      int intruderPresenceScore = 0;
      while (stillFeeding == true) {
        // start with a 1 second reading for this iteration
        float checkWeight = readCatWeight(false);
        Serial.print("checkWeight: ");
        Serial.println(checkWeight);
        // if the cat has stepped off the scale, as indicated by the weight dropping to less than 1/3
        if (checkWeight < (medianCatWeight / 3)) {
          // close doors, end loop
          closeDoor();
          stillFeeding = false;

          // if the weight is up by the allowed variance, we have an intruider
        } else if (checkWeight - medianCatWeight > allowedWeightVariance ) {
          intruderPresenceScore += 1;
          // if the extra cat has stuck around
          if (intruderPresenceScore > 3) {
            closeDoor();
            stillFeeding = false;
          } else {
            deterrent(1000);
          }
        }
      } // end of while feeding

      intruderPresenceScore = 0;
    }

  } // end of checking the weight of the cat

} // end of main loop




void openDoor() {
  // Open the door to the open angle
  for (doorAngle = doorClosedAngle; doorAngle < doorOpenAngle; doorAngle++) {
    doorServo.write(doorAngle);
    delay(60);
  }
  doorOpen = 1;
  // drop the aloted food portion(s).
  feed();
  delay(1000);
}

void closeDoor() {
  // checking to be sure the door is open, then close it
  if (doorOpen == 1) {
    for (doorAngle = doorOpenAngle; doorAngle >= doorClosedAngle; doorAngle--) {
      doorServo.write(doorAngle);
      delay(60);
    }
    doorOpen = 0;
  }
}

void feed() {
  // use the too-much-food function? look back to commits pre 12/26/15
  // if there's not much food in the bowl and the doors are open, the hopper starts dropping portions of food.
  if (doorOpen == 1) {
    // start rotating the motor. 
    // When it gets back to the top it checks weight (a higher value than above) 
    // and to see that it's under ration before continuing with the rotate.
    /* Serial.print("ration: ");
      Serial.println(ration); */
    for (int i = 0 ; doorOpen == 1 && ration > i ; i++) {
      // dispensor at top will be determined by a contact to a metal plate on a disc that rotates with the dispensor ball,
      // so when it hits that plate it'll be oriented to the fill position. When it starts back up, it'll still be in contact for a bit
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
  resetWeighVars();
  Serial.print("Calibrated Median Cat Weight: ");
  Serial.println(medianCatWeight);
}

void resetWeighVars() {
  readingTally = 0;
  readingNumber = 0;
  highReading = 0;
  lowReading = 1000;
  averageReading = 0;
}

// for when a weight greater than 6 lbs steps on the scale
// read for 1 second to find an average
float readCatWeight(bool doorClosed) {
  float thisCatsWeight;
  unsigned long startMillis = millis();
  while (scale.get_units() > minimumPossibleCat && millis() - startMillis < 1000) {
    ledBlink(thereIsACatPin, 50, 50);
    readScale();
  }
  // jibbering is not allowed for a door opener.
  if (highReading - lowReading > .5 && doorClosed) {
    thisCatsWeight = 0;
    resetWeighVars();
    return thisCatsWeight;

  } else {
    // throw out extremes
    averageReading = (readingTally - highReading - lowReading) / (readingNumber - 2);
    if (averageReading == 500) {
      thisCatsWeight = 0;
      return thisCatsWeight;
    } else {
      thisCatsWeight = averageReading;
      resetWeighVars();
      return thisCatsWeight;
    }
  }
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

void deterrent(int deterTimeMs) {
  unsigned long startMillis = millis();
  while (millis() - startMillis < deterTimeMs) {
    digitalWrite(deterrentDevice, HIGH);
    delay(20);
    digitalWrite(deterrentDevice, LOW);
    delay(20);
  }

}


// uses binary to give each input from the rotary switch a unique value to add to the int, sets ration acordingly. This is mapped out, see the red grid notebook.
// straight up is 1, going clockwise from there. The flat part of the shaft is what was used to idicate direction.
void rationRead() {
  // todo: replace this with a user interface.
  ration = 3;
}










