#include <SPI.h>
#include "Motor.h"
#include "RF24.h"
#define PI 3.1415926535897932384626433832795

MOTOR M1(5, 40, 42);
MOTOR M2(4, 44, 46);
MOTOR M3(3, 41, 43);
MOTOR M4(2, 45, 47);

RF24 radio(10, 11);
const byte address[6] = "00001";

int sensorVal[4];
int theta;


void setup() {
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_LOW);
  radio.startListening();

  Serial.begin(9600);
}

void loop() {
   if(radio.available()){
    radio.read(&sensorVal, sizeof(sensorVal));
    Serial.print("s: ");
    Serial.print(sensorVal[0]);
    theta = atan2(sensorVal[0], -sensorVal[1]);
    if (sensorVal[1] > 200) {
      moveSidewaysLeft();
    }
    else if (sensorVal[1] < 200) {
      moveSidewaysRight();
    }
    else if (sensorVal[0] > 200) {
      forward();
    }
    else if (sensorVal[0] < 200) {
      backward();
    }
    else if (sensorVal[1] < 200 & sensorVal[0] > 200) {
      moveRightForward();
    }
    else if (sensorVal[1] > 200 & sensorVal[0] > 200) {
      //moveLeftForward();
    }
    else if (sensorVal[1] < 200 & sensorVal[0] < 200) {
      //moveRightBackward();
    }
    else if (sensorVal[1] > 200 & sensorVal[0] < 200) {
      //moveLeftBackward();
    }
    else {
      stop();
    }
  }
}

void forward(){
  M1.forward(255);
  M2.forward(255);
  M3.forward(255);
  M4.forward(255);
}

void backward(){
  M1.backward(255);
  M2.backward(255);
  M3.backward(255);
  M4.backward(255);
}

void moveSidewaysRight(){
  M1.backward(255);
  M2.forward(255);
  M3.backward(255);
  M4.forward(255);
}

void moveSidewaysLeft(){
  M1.forward(255);
  M2.backward(255);
  M3.forward(255);
  M4.backward(255);
}

void moveRightForward(){
  M1.forward(255);
  M2.backward(0);
  M3.forward(0);
  M4.backward(255);
}


void stop(){
  M1.stop();
  M2.stop();
  M3.stop();
  M4.stop();
}

