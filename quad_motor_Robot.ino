#include "Motor.h"

MOTOR M1(4, 42, 43);
MOTOR M2(5, 44, 45);
MOTOR M3(3, 38, 39);
MOTOR M4(2, 40, 41);


void setup() {

}

void loop() {
  stop();
}

void forward(int speed){
  M1.forward(speed);
  M2.forward(speed);
  M3.forward(speed);
  M4.forward(speed);
}

void stop(){
  M1.stop();
  M2.stop();
  M3.stop();
  M4.stop();
}

