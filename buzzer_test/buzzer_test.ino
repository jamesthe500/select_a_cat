const int buzz = 12;

void setup() {
  // put your setup code here, to run once:
pinMode(buzz, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
digitalWrite(buzz, HIGH);
delay(20);
digitalWrite(buzz, LOW);
delay(20);
}
