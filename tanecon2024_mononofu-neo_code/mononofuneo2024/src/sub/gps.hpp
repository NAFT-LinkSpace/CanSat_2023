#ifndef GPS_HPP
#define GPS_HPP

#include <Arduino.h>
#include "pinassign.hpp"
#include <SparkFun_u-blox_GNSS_Arduino_Library.h>
#include "bno055.hpp"
// #include 

class GPS
{
private:
SFE_UBLOX_GNSS myGNSS;
// bno055 Bno;
public:
    bool status_GPS;
    void GPS_init();
    void main_GPS(io& Io,bno055& Bno);
    float azimuth(float x1,float y1,float x2,float y2);
    float distance(float x1,float y1,float x2,float y2);
};

#endif