#ifndef MOTOR_HPP
#define MOTOR_HPP

#include <Arduino.h>
#include "pinassign.hpp"
#include "bno055.hpp"
#include <SoftwareSerial.h>
#include <codecvt>
#include <string>
#include <cassert>
#include <locale>

class motor
{
private:
public:

    void init();
    void moving(io& Io);
    void forward(int speed);
    void forwardlow(int speed);
    void coast();
    void backward(int speed);
    void stop();
    void turnright(int speed);
    void turnleft(int speed);
    void heating();
    void cooling();
    String raspiserial;
    void moveraspi();
    void raspisend(String mess);
    void raspirecive(io& Io);
};

#endif