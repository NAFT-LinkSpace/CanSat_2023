#ifndef BME280_HPP
#define BME280_HPP

#include <Arduino.h>
#include <Adafruit_BME280.h>
#include <SPI.h>
#include "pinassign.hpp"

class bme
{
    private:
        int n=0;
    public:
        int bmestatus;
        // int sstatus;
        void init();
        void getdata(io& Io);
        void getPress(io& Sensors);
        void getAlt(io& Sensors);
        void getTemp(io& Sensors);
};

#endif