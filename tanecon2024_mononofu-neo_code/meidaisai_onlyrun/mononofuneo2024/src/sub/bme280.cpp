#include "bme280.hpp"

Adafruit_BME280 bme280;
// sensors SenSors;

void bme::init(){
    bmestatus=bme280.begin(0x76);
    Serial.print(bmestatus);
    while(!bmestatus){
        bmestatus=bme280.begin(0x76);
        Serial.print(bmestatus);
        Serial.println("errorbme!!");
        delay(100);
    }
    // if(!bmestatus){
    // bmestatus=bme280.begin();
    // Serial.print(bmestatus);
    //     Serial.println("errorbme!!");
    //     while(1)delay(10);
    // }
}

void bme::getdata(io& Io){
    getPress(Io);
    getAlt(Io);
    getTemp(Io);
}

void bme::getPress(io& Sensors){
    // Sensors.press_bme=bme280.readPressure();
    float press_temp = bme280.readPressure(); //   /100.0Fするべき？
    if(press_temp<100000){
        press_temp=bme280.readPressure();
    }
    for(int i=0;i<2;i++){
        Sensors.press[i]=Sensors.press[i+1];
    }
    Sensors.press[2]=press_temp;
    float sum=0;
    // sum=Sensors.press[0]+Sensors.press[1]+Sensors.press[2]+Sensors.press[3]+Sensors.press[4];
    for(int j=0;j<3;j++){
        sum+=Sensors.press[j];
    }
    Sensors.press_bme=sum/3.0F;

    if(Sensors.press[0]!=0 && n==0){
        n++;
        Sensors.press_init=sum/3.0F;
    }
    // Serial.println(Sensors.press_bme);
}

void bme::getAlt(io& Sensors){
    Sensors.alt_bme=bme280.readAltitude(SEALEVELPRESSURE_HPA);
}

void bme::getTemp(io& Sensors){
    Sensors.tempe_bme=bme280.readTemperature();
}
