/*
  Talk through
  Meow-trigger
  1. push and hold a button (LED acknowledges) to record a few seconds of the cat's meow.
  2. That sound is anylized for (?) pitch or whatever, which is stored.
  3. A mic listens for that pitch or something quite close to it.
  4. When heard, a sensor looks for a sitting cat within a certain range...
  5. ... which triggers a servo to rotate the food bowl cover plates to the open position while an LED flashes the stays on for open.
  6. The cat should bend down to eat now, this is sensed with a lower distance sensor & that the upper one senses nothing.
      (these sensors have LED feedback as well)
  7. if the cat doesn't bend down within 10 seconds, it closes (LED flashes).
  8. if the cat does, it stays open until it senses the cat has sat up, at which point it immediately closes (LED flashes).
  9. Neither closing nor opening will happen very quickly.
  10. A protected button & app button will allow humans to trigger the opening and closing of the cover plates.
      If the plates are locked open, all other functions can happen, just with a blinking LED instead of sliding plates.

  bowl-filler
  1. The bowl will be connected to a reservoir via a covered cheute.
  2. At the top of the cheute/bottom of the reservoir will be a flap or cup or something that releases food.
  3. A sensor in the food bowl will check to see how full it is.
  4. At the same time, it will keep track of the ammout of food dispensed on the current day.
  5. There will be dial on the back of the device or a selector in the app for the setting of the allowed maximum.
  6. If the bowl is low & the ammount dispensed hasn't exceeded the allotted maximum, a motor/servo will be triggered to dispense more food.
  7. It will dispense one unit then wait a moment (for food to finish falling) then check to see if either condition has been met before looping though again.
  8. If it cycles thorough (say) 10 times and neither condition has been met, there is trouble and the humans will be alerted through blinking light and app alert.
  9. A sensor in the reservoir will track the level of food in it and alert a low level via LED and app-alert.
  10. A button will allow the humans to manually dispense more food via app & device itself.

  the app (a stretch-goal as this introduces the World of WiFi)
  1. Will show current reservoir level
  2. Last 10 meow opening times.
  3. Allow a remote open/close via button
  4. Allow a remote refill via button
  5. Control the setting of allowed daily maximum.
  6. Display any alerts when things don't work right.

*/
const int upperSensorPin = 8;
const int servoPin = 13;
const int lowerSensorPin = 4;
const int micPin = 6;

int bowlState = 0;

void setup() {
  Serial.begin(9600);
  pinMode(servoPin, OUTPUT);
  pinMode(upperSensorPin, INPUT_PULLUP);
  pinMode(lowerSensorPin, INPUT_PULLUP);
  pinMode(micPin, INPUT_PULLUP);
}

void loop() {

  if (digitalRead(upperSensorPin) == LOW && digitalRead(lowerSensorPin) == LOW && digitalRead(micPin) == LOW) {
    // blinking represents the servo in the process of opening
    for (int i = 0; i < 40; i++) {
      digitalWrite(servoPin, HIGH);
      delay(50);
      digitalWrite(servoPin, LOW);
      delay(50);
      i++;
    }
    bowlState = 1;
    // light on means it's open
    digitalWrite(servoPin, HIGH);
    delay(2000);
  }
  // PROBLEM: not entering this while loop because it is misreading the buttons as both being low,
  // no mater what the buttons are doing IRL
  // it's as if the bowlState affects these to make them down.
  // If I remove the bowl state factor, it enters the while loop but won't exit.
  // if I remove the preceeding delay, that has no affect.
  // SOLVED: it didn't like the variables in place of digitalRead...

  while (digitalRead(upperSensorPin) == HIGH && digitalRead(lowerSensorPin) == LOW && bowlState == 1) {
    Serial.println("inWhile");

    digitalWrite(servoPin, HIGH);
    }
  
  // blinking represents the servo in the process of closing
  if (bowlState == 1) {
    for (int i = 0; i < 40; i++) {
      digitalWrite(servoPin, HIGH);
      delay(50);
      digitalWrite(servoPin, LOW);
      delay(50);
      i++;
    }
    bowlState = 0;
    Serial.println("bowl:");
    Serial.println(bowlState);
  }

  if (digitalRead(upperSensorPin) != LOW || digitalRead(lowerSensorPin) != LOW || digitalRead(micPin) != LOW) {
    digitalWrite(servoPin, LOW);
  }
}











