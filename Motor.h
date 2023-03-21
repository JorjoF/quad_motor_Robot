#ifndef MOTOR_h
#define MOTOR_h

#include <Arduino.h>

class MOTOR{
  private:
    int enaPin;
    int pinOne;
    int pinTwo;

  public:
    MOTOR(int ENA, int M1, int M2);
    void forward(int speed);
    void backward(int speed);
    void stop();
};

#endif