#ifndef PINASSIGN_HPP
#define PINASSIGN_HPP

#define pi 3.14159282
#define SEALEVELPRESSURE_HPA 1013.25
#define SCLK 30
#define MOSI 23
#define MISO 31
#define CS_SD 5
#define TX 12
#define RX 14

//会場
#define GOAL_lon 130.9600000
#define GOAL_lat 30.3741667
//こうわ
// #define GOAL_lon 130.8999304
// #define GOAL_lat 30.4254240


#define Earth_Radius 6378137

#define Setting 0
#define Ready 1
#define Fall 2
#define Landing 3
#define Start 4
#define Check 5
#define Checkmate 6
#define only_run 7
    
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
float press_init;
float alt_bme;
float tempe_bme;
unsigned int now_time;
int ready_time;
int ready_in_time;
int heatstart_time;
int heating_time;
int run_start_time;
int running_time;
int run_GPS_time;
int sd_time;
int status;
int accel_norm_bno;
double lat;
double lat__[5]={0,0,0,0,0};
double lat_ave;
double lon;
double lon__[5]={0,0,0,0,0};
double lon_ave;
float SIV;
float theta;
float distance;
int deltatheta;

String message="pien";


};

#endif