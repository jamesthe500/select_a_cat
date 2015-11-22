// See the README for a complete "talk-through" of the project.

//Establish which pins attach to which items.
const int bowlWeightPin = 8;
const int servoPin = 13;
const int catInRangePin = 4;
const int micPin = 6;
const int thereIsACatPin = 2;

// later, make these pin assignments. Using them as simple constants now.
const int selectorFactor0 = 0;
const int selectorFactor1 = 1;
const int selectorFactor2 = 1;
const int selectorFactor3 = 1;
const int selectorFactor4 = 0;

// Varaibles
int doorsOpen = 0;
int dailyRation = 0;
int todaysFeed = 0;
int selectorPosition = 0;

void setup() {
  Serial.begin(9600);
  // Establich which pins are innies, which are outies
  pinMode(servoPin, OUTPUT);
  pinMode(thereIsACatPin, OUTPUT);
  pinMode(bowlWeightPin, INPUT_PULLUP);
  pinMode(catInRangePin, INPUT_PULLUP);
  pinMode(micPin, INPUT_PULLUP);
}

void loop() {
  // See where the selector is and change the daily ration as needed;
  dailyRationRead();
  
  // Because we're using digital PULLUP, LOW is HIGH and HIGH is LOW for all switches & sensors.
  // an LED indicates that the cat is close enough. This is more for the humans, but who knows? Cats can learn?
  if (digitalRead(catInRangePin) == LOW) {
    digitalWrite(thereIsACatPin, HIGH);
  } else {
    digitalWrite(thereIsACatPin, LOW);
  }

  // If there is a cat in range & it meows the right meow.
  if (digitalRead(catInRangePin) == LOW && digitalRead(micPin) == LOW) {
    // blinking represents the servo in the process of opening
    for (int i = 0; i < 40; i++) {
      digitalWrite(servoPin, HIGH);
      delay(50);
      digitalWrite(servoPin, LOW);
      delay(50);
      i++;
    }
    // light on means it's open
    digitalWrite(servoPin, HIGH);
    doorsOpen = 1;
    // drop a food portion. could double up this function if portions are lacking.
    feed();
    delay(2000);
  }

  // Now the cat eats. The doors remain open until it walks out of range.
  while (digitalRead(catInRangePin) == LOW && doorsOpen == 1) {
    digitalWrite(servoPin, HIGH);
  }

  // blinking represents the servo in the process of closing
  if (doorsOpen == 1) {
    for (int i = 0; i < 40; i++) {
      digitalWrite(servoPin, HIGH);
      delay(50);
      digitalWrite(servoPin, LOW);
      delay(50);
      i++;
    }
    doorsOpen = 0;
  }

  if (digitalRead(catInRangePin) == HIGH) {
    digitalWrite(servoPin, LOW);
  }
}

void feed() {
  // if there's not much food in the bowl, the daily limit of food hasn't been exceeded, and the doors are open, the hopper drops one portion of food.
  if (doorsOpen == 1 && digitalRead(bowlWeightPin) == LOW && dailyRation >= todaysFeed) {

  }
}

void dailyRationRead() {
  selectorPosition = (selectorFactor0 | selectorFactor1 * 2 | selectorFactor2 * 4 | selectorFactor3 * 8 | selectorFactor4 * 16);
  Serial.println(selectorPosition);
  switch (selectorPosition) {
    case 14:
      Serial.println("selected 01110");
      delay(1000);
      dailyRation = 2;
      Serial.println(dailyRation);
      break;
  }
}










