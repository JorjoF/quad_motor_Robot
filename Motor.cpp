#include "Motor.h"

MOTOR::MOTOR(int ENA, int M1, int M2){
  enaPin = ENA;
  pinOne = M1;
  pinTwo = M2;

  pinMode(enaPin, OUTPUT);
  pinMode(pinOne, OUTPUT);
  pinMode(pinTwo, OUTPUT);
}

void MOTOR::forward(int speed){
  analogWrite(enaPin, speed);
  digitalWrite(pinOne, HIGH);
  digitalWrite(pinTwo, LOW);
}

void MOTOR::backward(int speed){
  analogWrite(enaPin, speed);
  digitalWrite(pinOne, LOW);
  digitalWrite(pinTwo, HIGH);
}

void MOTOR::stop(){
  analogWrite(enaPin, 0);
}



