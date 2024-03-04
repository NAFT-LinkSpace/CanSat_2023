#include "GPS.hpp"

void GPS::GPS_init(){
  status_GPS = myGNSS.begin();

  myGNSS.setI2COutput(COM_TYPE_UBX);
  myGNSS.saveConfigSelective(VAL_CFG_SUBSEC_IOPORT);
}

void GPS::main_GPS(io& Io,bno055& Bno){
    Io.lat=myGNSS.getLatitude()*pow(10,-7);
    Io.lon=myGNSS.getLongitude()*pow(10,-7);
    Io.SIV=myGNSS.getSIV();

    if(Io.SIV=0){
        Io.accuracy_GPS_=0;
    }else if(Io.SIV<5){
        Io.accuracy_GPS_=1;
    }else if(Io.SIV>=5){
        Io.accuracy_GPS_=2;
    }

    Io.distance=distance(Io.lon,Io.lat,GOAL_lon,GOAL_lat);
    float theta=azimuth(Io.lon,Io.lat,GOAL_lon,GOAL_lat);
    // Serial.println(theta);

    Io.deltatheta=Bno.YAW-theta-180+90;
    // Serial.println(Io.deltatheta);
}

float GPS::azimuth(float x1,float y1,float x2,float y2){
    float _x1 = x1 * pi / 180;
    float _y1 = y1 * pi / 180;
    float _x2 = x2 * pi / 180;
    float _y2 = y2 * pi / 180;


    float dx = (pow(_x2, 3) - pow(_x1, 3)) / (pow(_x2, 2) + pow(_x1, 2) + _x2 * _x1);

    float _y = sin(dx);
    float _x = cos(_y1) * tan(_y2) - sin(_y1) * cos(dx);

    volatile float theta = atan2(_y, _x) * 180 / pi;
    return theta;
}

float GPS::distance(float x1,float y1,float x2,float y2){
    float _x1 = x1 * pi / 180;
    float _y1 = y1 * pi / 180;
    float _x2 = x2 * pi / 180;
    float _y2 = y2 * pi / 180;

    volatile float dist = Earth_Radius*acos(sin(_y1)*sin(_y2)+cos(_y1)*cos(_y2)*cos(_x1 -_x2));
    return dist;
}