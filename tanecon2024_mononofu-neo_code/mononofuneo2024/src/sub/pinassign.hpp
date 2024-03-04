#ifndef PINASSIGN_HPP
#define PINASSIGN_HPP

#define pi 3.14159282
#define SEALEVELPRESSURE_HPA 1013.25
#define CS_SD 5U

#define GOAL_lon 35.1574375
#define GOAL_lat 136.9657873
#define Earth_Radius 6378137

#define Setting 0
#define Ready 1
#define Fall 2
#define Landing 3
#define Start 4
#define Check 5
#define Checkmate 6
    
const int led_R_1=A19;
const int led_R_2=A18;
const int led_L_1=A4;
const int led_L_2=A5;
const int led_heat_1=A14;
const int led_heat_2=A17;

//センサーの状態
class io
{
private:
public:
int accuracy_BNO_ = 2;   //0 : Not calibrated, 1 : calibrated, 2 : fully calibrated
int accuracy_GPS_ = 2;   //0 : No Satelites, 1 : A few satelites(1~4), 2 : Many satelites(5~)
float press[3]={0,0,0};
float prepress;
float presscount;
float press_bme;
float alt_bme;
float tempe_bme;
unsigned int now_time;
int heatstart_time;
int heating_time;
int sd_time;
int status;
int accel_norm_bno;
double lat;
double lon;
float SIV;
float distance;
float deltatheta;



};

#endif