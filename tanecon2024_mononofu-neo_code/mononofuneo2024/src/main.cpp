#include <Arduino.h>
#include "sub/pinassign.hpp"
#include "sub/motor.hpp"
#include "sub/bno055.hpp"
#include "sub/GPS.hpp"
#include "sub/bme280.hpp"
#include "sub/sd.hpp"
#include <Adafruit_SSD1306.h>
#include <SPI.h>

motor Motor;
bno055 Bno;
io Io;
GPS Gps;
bme Bme;
sd Sd;

int n=0;

void setup() {
Serial.begin(9600);
Motor.init();
Bno.init();
delay(100);
Bme.init();
Gps.GPS_init();
delay(100);
    // Motor.heating();

Io.status=4;

// Motor.heating();
// delay(120000);
// Motor.cooling();

}

void loop() {
  Io.now_time=millis();
  Bno.main();
  Bme.getdata(Io);
  // Sd.makebuffer(Io);
  //   Sd.logWrite(Io);
  //   Serial.print("append try");
  // if(Io.now_time-Io.sd_time>5000){
  //   Io.sd_time=Io.now_time;
  // }
  Serial.print(Io.now_time);
  Serial.print(",");
  Serial.print(Io.status);
  Serial.print(",");
  Serial.print(Bno.YAW);
  Serial.print(",");
  // Serial.print(Io.lat);
  // Serial.print(",");
  // Serial.print(Io.lon);
  // Serial.print(",");
  Serial.print(Io.SIV);
  Serial.print(",");

  // delay(100);

  switch (Io.status)
  {
  case Setting:
    Motor.stop();
    if(Io.now_time>10000){
      Io.status=Ready;
    }
    break;
  case Ready:
    Serial.print(Io.presscount);
    delay(50);
    if(Io.press_bme-Io.prepress>0.5){
      Io.presscount++;
    }else{
      Io.presscount=0;
    }
    if(Io.presscount>5){
      Io.status=Fall;
    Motor.heating();
      Io.heatstart_time=Io.now_time;
    }
    Io.prepress=Io.press_bme;
    break;
  case Fall:
    Io.heating_time=Io.now_time-Io.heatstart_time;
    // delay(10000);
    if(Io.heating_time>60000){
      Motor.cooling();
      Io.status=Landing;
    }

    break;
  case Landing:
    //落下検知どうしようね
    if(Io.alt_bme<20){
      Io.status=Start;
    }
    break;
  case Start:
  Gps.main_GPS(Io,Bno);
  Serial.print(Io.lon,7);
  Serial.print(",");
  Serial.print(Io.lat,7);
  Serial.print(",");
  Serial.print(Bno.YAW);
  Serial.print(",");
  // Serial.print(Io.SIV);
    if(Io.distance<5){
      // Motor.stop();
    }else{
    Motor.moving(Io);
    }
    // delay(100);

    // if(Io.distance<5){
    //   Io.status=Check;
    // }
    break;
  case Check:
  Gps.main_GPS(Io,Bno);
    if(Io.distance>10){
      Io.status=Start;
    }
    // else if(camera){
    //   Io.status=checkmate;
    // }
    break;
  case Checkmate:
    Motor.stop();
    break;
  default:
    break;
  }
  // Serial.print(Bno.YAW);
  // Serial.print(",");
  // // Serial.print(Bno.YAW_0_offset);
  // Serial.print(",");
  // Serial.print(Bno.PITCH);
  // Serial.print(",");
  // Serial.print(Bno.ROLL);
  // Serial.print(",");
  // Serial.println(Io.accuracy_BNO_);
}
