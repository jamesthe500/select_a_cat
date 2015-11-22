const int rotarySwitchPin = A5;

const int ledPin = 13;

int ledState = HIGH;
int buttonState;
int lastButtonState = LOW;

long lastDebounceTime = 0;
long debounceDelay = 50;

void setup() {
  // put your setup code here, to run once:
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
  pinMode(rotarySwitchPin, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
int reading = analogRead(rotarySwitchPin);

Serial.println(reading);
delay(400);
}
