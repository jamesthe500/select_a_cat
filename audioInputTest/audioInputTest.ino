//Simple Audio In
//by Amanda Ghassaei
//http://www.instructables.com/id/Arduino-Audio-Input/
//Sept 2012

/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
*/

int incomingAudio;
boolean clippingHigh = 0;
boolean clippingLow = 0;
int clippingHighCounter = 100;
int clippingLowCounter = 100;
int signalThen;
int signalNow;

void setup(){
  Serial.begin(9600);
  pinMode(2, OUTPUT);
  pinMode(A4, OUTPUT);
}

void loop(){
  incomingAudio = analogRead(A1);//read input from A0
  //do stuff with the variable "incomingAudio"
  //Serial.println(incomingAudio);

  
  
  signalNow = incomingAudio;

  

  if (abs(signalNow - signalThen) > 130 ){
    digitalWrite(2,HIGH);
    clippingHigh = 1;
    clippingHighCounter = 50;
  }
  if(clippingHigh){
    if (clippingHighCounter > 0){
      clippingHighCounter--;
    } else {
      clippingHigh = 0;
      digitalWrite(2,LOW);
    }
  }
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
  
  if (incomingAudio == 0){
    digitalWrite(A4,HIGH);
    clippingLow = 1;
    clippingLowCounter = 100;
  }
  if(clippingLow){
    if (clippingLowCounter > 0){
      clippingLowCounter--;
      
    } else {
      clippingLow = 0;
      digitalWrite(A4,LOW);
    }
  }
}


