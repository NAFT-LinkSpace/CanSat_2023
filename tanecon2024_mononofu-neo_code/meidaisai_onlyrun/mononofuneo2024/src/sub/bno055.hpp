#ifndef BNO055_HPP
#define BNO055_HPP

#include <Arduino.h>
#include <Adafruit_BNO055.h>
#include "pinassign.hpp"

class bno055
{
private:
io Io;
public:
    
    Adafruit_BNO055 bno = Adafruit_BNO055(55, 0x28, &Wire);
    sensors_event_t accelerometerData, angVelocityData, magnetometerData;  //orientationData  , linearAccelData, accelerometerData, gravityData
    
//////////(BNO_Calibration)////////////////////
volatile int Status_sys;
volatile int Status_gyro;
volatile int Status_acc;
volatile int Status_mag;

//////////(BNO_Calibration:End)////////////////

//////////(INIT_Orientation)////////////////////
volatile float YAW_0_offset;//Processing表示用，機体前面をPC画面に向けた時のYaw
//////////(INIT_Orientation:End)////////////////

///////////////(RAW_DATA)///////////////////////////
volatile float accX = 0;//加速度センサから求めた加速度
volatile float accY = 0;//加速度センサから求めた加速度
volatile float accZ = 0;//加速度センサから求めた加速度

volatile float gyroX = 0;//ジャイロセンサから求めた角速度
volatile float gyroY = 0;//ジャイロセンサから求めた角速度
volatile float gyroZ = 0;//ジャイロセンサから求めた角速度


volatile float magX = 0;//磁気センサから求めたuT
volatile float magY = 0;//磁気センサから求めたuT
volatile float magZ = 0;//磁気センサから求めたuT

volatile float ROLL  = 0;//ロール角
volatile float PITCH = 0;//ピッチ角
volatile float YAW   = 0;//機体前面を向ける方向が N0°：0°　E0°：90° W0°：-90°

volatile float YAW_0;//機体前面をPCに向けた時を0°とする
///////////////(RAW_DATA:End)///////////////////////
    void init();
    void main();
    void printEvent(sensors_event_t* event);
};

#endif