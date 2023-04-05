#include <SPI.h>
#include <Arduino.h>
#include "Motor.h"
#include "RF24.h"
MOTOR M1(24, 26, 2);
MOTOR M2(28, 30, 3);
MOTOR M3(25, 27, 4);
MOTOR M4(29, 31, 5);

RF24 radio(49, 48);
const byte address[6] = "00001";
unsigned long lastReceiveTime = 0;
unsigned long currentTime = 0;

int sensorVal[4];
double x, y, xC, yC, sinC, cosC, s1, s0;
int s;


void setup() {
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_LOW);
  radio.startListening();

  pinMode(9, OUTPUT);

  Serial.begin(9600);
  
}

void loop() {
    // start measuring time in millis
    currentTime = millis();
    if ( currentTime - lastReceiveTime > 1000 ) { 
      stop();
    }
   if(radio.available()){
    radio.read(&sensorVal, sizeof(sensorVal)); // recieve information from controller
    lastReceiveTime = millis();
   }
    s0 = constrain(map(sensorVal[0], -230,230,-255,255), -255, 255);
    s1 = constrain(map(sensorVal[1], -230,230,-255,255), -255, 255);

    double rad = atan2(s1, s0);
    double hyp = hypot(s0, s1);
    

    sinC = sin(rad);
    cosC = cos(rad);

    y = hyp * sinC;
    x = hyp * cosC;

    xC = x / 255;
    yC = y / 255;

    //Serial.println(xC);
    if(sensorVal[2] == 0){
      digitalWrite(9, HIGH);
    }else{
      digitalWrite(9, LOW);
    }
    if(sensorVal[3] == 0){
        if(xC > .95){
          s = 9;
        }else if (xC < -.95){
          s = 10;
        }else{
          s = 0;
        }
    }else{
      if (xC > .95) {
        //Serial.println("moveSidewaysRight()");
        s = 3;
      }else if (xC < -.95) {
        //Serial.println("moveSidewaysLeft();");
       s = 4;
      }else if (yC > .95) {
        //Serial.println("forward();");
        s = 1;
      }else if (yC < -.95) {
        //Serial.println("backward();");
        s = 2;
      }else if ((yC > .50 && yC < 1.00) && (xC > .50 && xC < 1.00)) {
        //Serial.println("moveRightForward();");
       s = 5;
      }else if ((yC < 1.00 && yC > .50) && (xC > -1.00 && xC < -.50)) {
        //Serial.println("moveLeftForward();");
       s = 6;
      }else if ((yC > -1.00 && yC < -.50) && (xC > .50 && xC < 1.00)) {
        //Serial.println("moveRightBackward();");
        s = 7;
      }else if ((yC > -1.00 && yC < -.50) && (xC < -.50 && xC > -1.00)) {
        //Serial.println("moveLeftBackward();");
        s = 8;
       }else{
        s = 0;
       }
     }
     Serial.println(sensorVal[3]);
     motorCall(s);
     delay(50);
   
}
void motorCall(int s){
  switch(s){
    case 1:
      forward();
      break;
    case 2:
      backward();
      break;
    case 3:
      moveSidewaysRight();
      break;
    case 4:
      moveSidewaysLeft();
      break;
    case 5:
      moveRightForward();
      break;
    case 6:
      moveLeftForward();
      break;
    case 7:
      moveRightBackward();
      break;
    case 8:
      moveLeftBackward();
      break;
    case 9:
      turnRight();
      break;
    case 10:
      turnLeft();
      break;
    default:
      stop();
  }
}

void forward(){
  M1.forward();
  M2.forward();
  M3.forward();
  M4.forward();
}

void backward(){
  M1.backward();
  M2.backward();
  M3.backward();
  M4.backward();
}
void moveSidewaysRight(){
  M1.backward();
  M2.forward();
  M3.backward();
  M4.forward();
}

void moveSidewaysLeft(){
  M1.forward();
  M2.backward();
  M3.forward();
  M4.backward();
}

void moveRightForward(){
  M2.forward();
  M1.stop();
  M4.forward();
  M3.stop();
}

void moveLeftForward(){
  M2.stop();
  M1.forward();
  M3.forward();
  M4.stop();
}

void moveRightBackward(){
  M2.stop();
  M1.backward();
  M3.backward();
  M4.stop();
}

void moveLeftBackward(){
  M2.backward();
  M3.stop();
  M4.backward();
  M1.stop();
}

void turnLeft(){
  M1.forward();
  M4.backward();
  M2.forward();
  M3.backward();
}

void turnRight(){
  M4.forward();
  M2.backward();
  M3.forward();
  M1.backward();
}


void stop(){
  M1.stop();
  M2.stop();
  M3.stop();
  M4.stop();
}
