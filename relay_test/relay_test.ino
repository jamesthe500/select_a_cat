const int tripPin = 2;
const int signalPin = 4;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(signalPin, INPUT);
  pinMode(tripPin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

  if (digitalRead(signalPin) == HIGH) {
    digitalWrite(tripPin, HIGH);
    Serial.println("signal received");
  } else {
    digitalWrite(tripPin, LOW);
  }
}
