#ifndef MOTOR_HPP
#define MOTOR_HPP

#include <Arduino.h>
#include "pinassign.hpp"
#include "bno055.hpp"

class motor
{
private:
    // io Io;
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
};

#endif