#include <Servo.h>
Servo doorServo;

const int openDoorSignal = 4;
const int doorClosedAngle = 10;
const int doorOpenAngle = 175;
bool doorOpen = 0;
int doorAngle = doorClosedAngle;
int currentServoAngle = 0;


void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  doorServo.attach(A0);
  pinMode(openDoorSignal, INPUT_PULLUP);
  currentServoAngle = doorServo.read();
  Serial.println(currentServoAngle);
  closeDoor();
}

void loop() {
  //Serial.println("Something");
  // put your main code here, to run repeatedly:
  if (doorOpen == false && digitalRead(openDoorSignal) == LOW) {
    openDoor();
  }
  if (doorOpen == true && digitalRead(openDoorSignal) == LOW) {
    closeDoor();
  }
}


void openDoor() {
  // Open the door to the open angle
  for (doorAngle = currentServoAngle; doorAngle < doorOpenAngle; doorAngle++) {
    doorServo.write(doorAngle);
    delay(60);
  }
  doorOpen = true;
  currentServoAngle = doorServo.read();
}

void closeDoor() {
  for (doorAngle = currentServoAngle; doorAngle >= doorClosedAngle; doorAngle--) {
    doorServo.write(doorAngle);
    delay(60);
  }
  doorOpen = false;
  currentServoAngle = doorServo.read();
}
