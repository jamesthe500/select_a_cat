#include <NewPing.h>
 
#define TRIGGER_PIN  2
#define ECHO_PIN     3
#define MAX_DISTANCE 2000
 
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
 
void setup() {
  Serial.begin(115200);
}
 
void loop() {
  delay(2000);
  int uS = sonar.ping_median(50);
  Serial.print("Ping: ");
  Serial.print(uS / US_ROUNDTRIP_CM);
  Serial.println("cm");
}
/*
NewPing sonar(2, 3, 100);

void setup() {
  Serial.begin (115200);
}

void loop() {
  delay(2000);
  int uS = sonar.ping();
  Serial.print("Ping: ");
  Serial.print(uS / US_ROUNDTRIP_CM);
  Serial.println("cm");
  time = hcsr.Timing();
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(triggerPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  mark = micros();
    while(digitalRead(A1) == LOW || micros() - mark < 58000){
    };
    twain = micros() - mark;
    Serial.println("twain");
    Serial.println(twain);
  Serial.println("time");
  Serial.println(time);
  delay(2000);
}*/
