#ifndef GPS_HPP
#define GPS_HPP

#include <Arduino.h>
#include "pinassign.hpp"
// #include <SparkFun_u-blox_GNSS_Arduino_Library.h>
#include "bno055.hpp"
#include <TinyGPSPlus.h> 
#include <SoftwareSerial.h>



class GPS
{
private:
// SFE_UBLOX_GNSS myGNSS;
TinyGPSPlus gps;
// bno055 Bno;
public:
    bool status_GPS;
    const char *a;
    String b;
    double lat_before;
    double lng_before;
    void GPS_init();
    void main_GPS(io& Io,bno055& Bno);
    float azimuth(float x1,float y1,float x2,float y2);
    float distance(float x1,float y1,float x2,float y2);
    float toRadians(float degree);
    float calculateDistance(float lat1, float lon1, float lat2, float lon2);
};

#endif