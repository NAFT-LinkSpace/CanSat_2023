#include "GPS.hpp"

SoftwareSerial ss(34,35);
void GPS::GPS_init(){
//   status_GPS = myGNSS.begin();
    ss.begin(9600);

//   myGNSS.setI2COutput(COM_TYPE_UBX);
//   myGNSS.saveConfigSelective(VAL_CFG_SUBSEC_IOPORT);
}

void GPS::main_GPS(io& Io,bno055& Bno){
    Serial.println("GPSGPSPGPS");
  b = ss.readStringUntil('\n');                                           // シリアルから改行文字までのデータを読み込み
  a = b.c_str();                                                       // 文字列をc言語スタイルの文字列に変換
  while (*a)
    if (gps.encode(*a++))                                                   // GPSオブジェクトに文字を1文字ずつ渡す
    {
      
  if (gps.location.isValid())
  {
    
    double lat=gps.location.lat();
    double lng=gps.location.lng();

    // Serial.print(gps.location.lat(), 6); // 緯度
    // Serial.print(F(","));                // Fは文字リテラルをフラッシュメモリに保存するためのものでメモリ節約できる
    // Serial.print(gps.location.lng(), 6); // 経度    
   

  if(lat!=lat_before&&lng!=lng_before){
    Serial.print(millis()/1000);
    Serial.print(F(","));
  Serial.print(F("LocationLocationLocationLocationLocationLocation: "));
    Serial.print(lat,7);
    Io.lat_ave=lat;
    Serial.print(F(","));
    Serial.print(lng,7);
    Io.lon_ave=lng;
  Serial.println();
  }else{
    Serial.print(F("samesamesame"));
  }

  lat_before=lat;
  lng_before=lng;


  }
  else 
  {
  Serial.print(F("INVALID"));
  }
    }
  /*
    }
    // double lat_temp=myGNSS.getLatitude()*pow(10,-7);
    // double lon_temp=myGNSS.getLongitude()*pow(10,-7);
    // Io.lat=myGNSS.getLatitude()*pow(10,-7);
    // Io.lon=myGNSS.getLongitude()*pow(10,-7);
    Io.lat_ave=lat_temp;
    Io.lon_ave=lon_temp;

    Io.SIV=myGNSS.getSIV();

    if(Io.SIV=0){
        Io.accuracy_GPS_=0;
    }else if(Io.SIV<5){
        Io.accuracy_GPS_=1;
    }else if(Io.SIV>=5){
        Io.accuracy_GPS_=2;
    }
    ///latの5回平均とる
    // if(30<lat_temp<40){
    //     for(int i=0;i<4;i++){
    //         Io.lat__[i]=Io.lat__[i+1];
    //     }
    //     Io.lat__[4]=lat_temp;
    // }
    // double sum_lat=0;
    // // sum=Sensors.press[0]+Sensors.press[1]+Sensors.press[2]+Sensors.press[3]+Sensors.press[4];
    // for(int j=0;j<5;j++){
    //     sum_lat+=Io.lat__[j];
    // }
    // Io.lat_ave=sum_lat/5;

    ///lonの5回平均とる
    // if(125<lon_temp<140){
    //     for(int i=0;i<4;i++){
    //         Io.lon__[i]=Io.lon__[i+1];
    //     }
    //     Io.lon__[4]=lon_temp;
    // }
    // double sum_lon=130;
    // // sum=Sensors.press[0]+Sensors.press[1]+Sensors.press[2]+Sensors.press[3]+Sensors.press[4];
    // for(int j=0;j<5;j++){
    //     sum_lon+=Io.lon__[j];
    // }
    // Io.lon_ave=sum_lon/5;

    if(Io.SIV==0.00){
        //会場スタート
     Io.lat_ave=30.3749361;
     Io.lon_ave=130.9600233;
        //こうわスタート
    //  Io.lat_ave=30.4253549;
    //  Io.lon_ave=130.9000772;
    }
//   Serial.println(",");
//   Serial.println(",");

//   Serial.println(",");
//   Serial.print(Io.lat_ave);
//   Serial.print(",");
//   Serial.print(Io.lon_ave);

*/

    Io.distance=calculateDistance(Io.lat_ave,Io.lon_ave,GOAL_lat,GOAL_lon);    
    // Io.theta=azimuth(GOAL_lon,GOAL_lat,Io.lon_ave,Io.lat_ave);
   
    Io.theta=azimuth(Io.lon_ave,Io.lat_ave,GOAL_lon,GOAL_lat);

    Io.deltatheta=Bno.YAW-Io.theta+6;
    if(Io.deltatheta>=180){
        Io.deltatheta-=-360;
    }else if(-180>Io.deltatheta){
        Io.deltatheta+=360;
    }
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

// Function to convert degrees to radians
float GPS::toRadians(float degree) {
    return degree * M_PI / 180.0;
}

// Function to calculate distance between two points using Haversine formula
float GPS::calculateDistance(float lat1, float lon1, float lat2, float lon2) {
    float dlat = toRadians(lat2 - lat1);
    float dlon = toRadians(lon2 - lon1);

    float a = sin(dlat / 2) * sin(dlat / 2) + cos(toRadians(lat1)) * cos(toRadians(lat2)) * sin(dlon / 2) * sin(dlon / 2);
    float c = 2 * atan2(sqrt(a), sqrt(1 - a));

    return Earth_Radius * c;
}