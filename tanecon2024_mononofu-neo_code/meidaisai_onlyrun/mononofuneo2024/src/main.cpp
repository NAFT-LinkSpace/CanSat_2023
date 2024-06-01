#include <Arduino.h>
#include "sub/pinassign.hpp"
#include "sub/motor.hpp"
#include "sub/bno055.hpp"
#include "sub/GPS.hpp"
#include "sub/bme280.hpp"
#include "sub/sd.hpp"
#include <Adafruit_SSD1306.h>
#include <SPI.h>
#include "BluetoothSerial.h" 
 
BluetoothSerial ESP_BT; 


motor Motor;
bno055 Bno;
io Io;
GPS Gps;
bme Bme;
sd Sd;

int n=0;
int nn;

void setup() {
Serial.begin(9600);
// Serial.begin(115200); //Start Serial monitor in 115200
ESP_BT.begin("ESP32_LED_Control"); //Name of your Bluetooth Signal
Serial.println("Bluetooth Device is Ready to Pair");
 
Motor.init();
Bno.init();
delay(100);
Bme.init();
Gps.GPS_init();
delay(100);
// Motor.heating();
Sd.init();

Io.status=7;



///////////////////////////////
//ここを変える

Motor.forward(256);
delay(1000);
Motor.turnleft(256);
delay(600);
Motor.forward(256);
delay(2000);
Motor.turnright(256);
delay(400);
Motor.forward(256);
delay(1500);
Motor.turnright(256);
delay(1500);
Motor.forward(256);
delay(1500);
Motor.coast();

Io.status=6;


/////////////////////////////

}

void loop() {
  Io.now_time=millis();
  Bno.main();
  Bme.getdata(Io);
    // Gps.main_GPS(Io,Bno);
  Sd.makebuffer(Io);
  // Sd.logWrite(Io);
  if(Io.now_time-Io.sd_time>5000){
    Io.sd_time=Io.now_time;
  }

  // Serial.print("nn    : ");
  // Serial.println(nn);
  Serial.print("time    : ");
  Serial.println(Io.now_time);
  Serial.print("status  : ");
  Serial.println(Io.status);
  // Serial.print("prein    : ");
  // Serial.println(Io.press_init);
  // Serial.print("press  : ");
  // Serial.println(Io.press_bme);
  Serial.print("accbno  : ");
  Serial.println(Io.accuracy_BNO_);
  Serial.print("yaw:      ");
  Serial.println(Bno.YAW);
  Serial.print("lat:      ");
  Serial.println(Io.lat_ave,7);
  Serial.print("lon:      ");
  Serial.println(Io.lon_ave,7);
  Serial.print("siv:      ");
  Serial.println(Io.SIV);
  // Serial.print("theta:    ");
  // Serial.println(Io.theta);
  Serial.print("dethe:    ");
  Serial.println(Io.deltatheta);
  Serial.print("distance: ");
  Serial.println(Io.distance);
  Serial.println("");
  Serial.println("");
  Serial.println("");
  Serial.println("");

  
  // ESP_BT.print("time    : ");
  // ESP_BT.println(Io.now_time);
  // ESP_BT.print("status  : ");
  // ESP_BT.println(Io.status);
  // ESP_BT.print("prein    : ");
  // ESP_BT.println(Io.press_init);
  // ESP_BT.print("press  : ");
  // ESP_BT.println(Io.press_bme);
  // ESP_BT.print("accbno  : ");
  // ESP_BT.println(Io.accuracy_BNO_);
  // ESP_BT.print("yaw:      ");
  // ESP_BT.println(Bno.YAW);
  // ESP_BT.print("lat:      ");
  // ESP_BT.println(Io.lat_ave,7);
  // ESP_BT.print("lon:      ");
  // ESP_BT.println(Io.lon_ave,7);
  // ESP_BT.print("siv:      ");
  // ESP_BT.println(Io.SIV);
  // ESP_BT.print("theta:    ");
  // ESP_BT.println(Io.theta);
  // ESP_BT.print("dethe:    ");
  // ESP_BT.println(Io.deltatheta);
  // ESP_BT.print("distance: ");
  // ESP_BT.println(Io.distance);
  // ESP_BT.println("");
  // ESP_BT.println("");
  // ESP_BT.println("");
  // ESP_BT.println("");

  // delay(100);

//デバッグ用
  // if(Io.now_time<20000){
  //   Io.status=0;
  // }else if(Io.now_time<30000){
  //   Io.status=1;
  // }else if(Io.now_time<40000){
  //   Io.status=4;
  // }else if(Io.now_time<50000){
  //   Io.status=5;
  // }else{
  //   Io.status=6;
  // }

  // Motor.raspirecive(Io);
  // Motor.raspisend("33");
  // Serial.println(Io.message);
  // Serial.println("");
  // Serial.println("");
  // Serial.println("");
  // Serial.println("");

////////////////
  switch (Io.status)
  {
  case only_run:
    Motor.forward(256);
    delay(1000);
    Motor.turnleft(256);
    delay(1000);
    break;

  case Setting:
    Motor.stop();
    if(Io.press_bme<Io.press_init-20){//本番は200?
      nn++;
    }else{
      nn=0;
    }
        Motor.raspisend("1,0,0,0,0");
    if(nn>=10){
        Io.status=Ready;
        Io.ready_in_time=millis();
      }
    delay(200);

    break;
  case Ready:
    
    Serial.print(Io.presscount);
    Io.ready_time=Io.now_time-Io.ready_in_time;
    delay(50);
    if(Io.press_bme-Io.prepress>0.5){
      Io.presscount++;
    }else{
      Io.presscount=0;
    }
    if(Io.presscount>6 && Io.ready_time>40000){
      Io.status=Fall;
      Motor.heating();
      Io.heatstart_time=Io.now_time;
    }
    if(Io.ready_time>600000){
      Io.status=Fall;
    }
    Io.prepress=Io.press_bme;
  // ESP_BT.print("readytime: ");
  // ESP_BT.println(Io.ready_time);
    break;
  case Fall:
    Io.heating_time=Io.now_time-Io.heatstart_time;
    // delay(10000);
    if(Io.heating_time>10000){
      // Motor.cooling();
      Io.status=Landing;
      // Io.status=Landing;
    }

    break;
  case Landing:
    Io.heating_time=Io.now_time-Io.heatstart_time;
    //落下検知どうしようね
    if(Io.press_bme>Io.press_init-100 && Io.heating_time>20000){
      Io.status=Start;
      Io.run_start_time=Io.now_time;
    }
    if(Io.heating_time>30000){
      Io.status=Start;
      Io.run_start_time=Io.now_time;
    }
    break;

  case Start:
        // Motor.raspisend("0,1,1,1,1");
    if(Io.heating_time>40000){
      Motor.cooling();
    }else{
      Io.heating_time=Io.now_time-Io.heatstart_time;
    }
    Gps.main_GPS(Io,Bno);
    if(Io.SIV!=0){
    Io.run_GPS_time=Io.now_time-Io.run_start_time;
      Motor.raspisend("0,1,1,0,0");
      // if(Io.run_GPS_time>1200000){
      //     Io.status=Checkmate;
      // }
    }else{
    Io.running_time=Io.now_time-Io.run_start_time;
      Motor.raspisend("0,1,1,0,1");
      // if(Io.running_time>6000000){
      //     Io.status=Checkmate;
      // }
    }
    if(Io.distance<10){
      n++;
    }else{
      n=0;
      Motor.moving(Io);
    }

    if(n>5){
      Io.status=Check;
      Motor.stop();
      // Io.status=Checkmate;  //raspiダメな時      
    }

    // if(Io.running_time>600000){
    //   Io.status=Checkmate;
    // }
    break;

  case Check:
    Motor.raspisend("0,0,0,1,0");
    Gps.main_GPS(Io,Bno);
    if(Io.distance>20){
      Io.status=Start;
    }
    Motor.moveraspi();
    break;

  case Checkmate:
    Motor.raspisend("1,1,1,1,1");
    Motor.stop();
    break;


  default:
    break;
  }
}
