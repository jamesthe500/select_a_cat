//Simple Audio In
//by Amanda Ghassaei
//http://www.instructables.com/id/Arduino-Audio-Input/
//Sept 2012

/*
   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 3 of the License, or
   (at your option) any later version.

*/

int incomingAudio;
boolean clippingHigh = 0;
boolean clippingLow = 0;
int clippingHighCounter = 100;
int clippingLowCounter = 100;
int signalThen;
int signalNow;
int freqSampleTime1;
int freqSampleTime2;
int frequencyAddend;
unsigned long frequencyTally;
int frequency;
int sampleSize;

void setup() {
  Serial.begin(9600);
  pinMode(2, OUTPUT);
  pinMode(A4, OUTPUT);
}

void loop() {
  incomingAudio = analogRead(A1);//read input from A0

  signalNow = incomingAudio;

  if (abs(signalNow - signalThen) > 130 ) {
    sampleSize = 0;
    for (int timerStart = millis(), endThis = millis() + 1 ; (endThis - timerStart) < 100 ; sampleSize++) {
      freqSampleTime1 = 0;
      freqSampleTime2 = 0;
      for (int i = 0 ; i < 10 ;) {
        signalNow = analogRead(A1);
        if (signalNow > signalThen) {
          int j = 1000;
          while (signalNow > signalThen) {
            signalThen = analogRead(A1);
            signalNow = analogRead(A1);
          }

          if (freqSampleTime1 == 0) {
            freqSampleTime1 = micros();

          }
          i++;
        } else {
          signalThen = analogRead(A1);
        }
      }
      freqSampleTime2 = micros();
      frequencyAddend = (freqSampleTime2 - freqSampleTime1) / 10;
      frequencyTally += frequencyAddend;
      //Serial.println(frequencyAddend);
      endThis = millis();
    }
    frequency = frequencyTally / sampleSize ;
    if (sampleSize > 1 && frequency > 700 ) {
      
      Serial.println(sampleSize);
      Serial.println(frequency);
    }
  }
  frequencyTally = 0;
  signalThen = incomingAudio;

  /*if (incomingAudio == 1023){
    digitalWrite(2,HIGH);
    clippingHigh = 1;
    clippingHighCounter = 100;
    }
    if(clippingHigh){
    if (clippingHighCounter > 0){
      clippingHighCounter--;
    } else {
      clippingHigh = 0;
      digitalWrite(2,LOW);
    }
    }*/

  if (incomingAudio == 0) {
    digitalWrite(A4, HIGH);
    clippingLow = 1;
    clippingLowCounter = 100;
  }
  if (clippingLow) {
    if (clippingLowCounter > 0) {
      clippingLowCounter--;

    } else {
      clippingLow = 0;
      digitalWrite(A4, LOW);
    }
  }
}


