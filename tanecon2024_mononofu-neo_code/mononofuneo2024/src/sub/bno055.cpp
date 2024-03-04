#include "bno055.hpp"

void bno055::init(){
    bno.begin();
    bno.setExtCrystalUse(true);
    // bno.getCalibration(&sys,&gyro,&accel,&mag);
    
  sensor_t sensor;
  bno.getSensor(&sensor);
  //Serial.println("------------------------------------");
  //Serial.print  ("Sensor:       "); Serial.println(sensor.name);
  //Serial.print  ("Driver Ver:   "); Serial.println(sensor.version);
  //Serial.print  ("Unique ID:    "); Serial.println(sensor.sensor_id);
  //Serial.print  ("Max Value:    "); Serial.print(sensor.max_value); Serial.println(" xxx");
  //Serial.print  ("Min Value:    "); Serial.print(sensor.min_value); Serial.println(" xxx");
  //Serial.print  ("Resolution:   "); Serial.print(sensor.resolution); Serial.println(" xxx");
  //Serial.println("------------------------------------");
  //Serial.println("");
  delay(500);
}

void bno055::main(){

  sensors_event_t event, angVelocityData, magnetometerData, accelerometerData;
  bno.getEvent(&event);
  bno.getEvent(&angVelocityData, Adafruit_BNO055::VECTOR_GYROSCOPE);
  bno.getEvent(&magnetometerData, Adafruit_BNO055::VECTOR_MAGNETOMETER);
  bno.getEvent(&accelerometerData, Adafruit_BNO055::VECTOR_ACCELEROMETER);

  printEvent(&angVelocityData);
  printEvent(&magnetometerData);
  printEvent(&accelerometerData);

  imu::Quaternion q = bno.getQuat();
  q.normalize();

  imu::Vector<3> euler = q.toEuler();

  //euler.y() = asin(2 * q.x() * q.z() + 2 * q.y() * q.w());

  /*if (abs(cos(euler.y())) > 0.001) {
    euler.x() = atan2(-(2 * q.y() * q.z() - 2 * q.x() * q.w()) / (2 * pow(q.w(), 2) + 2 * pow(q.z(), 2) - 1));
    euler.z() = atan(-(2 * q.x() * q.y() - 2 * q.z() * q.w()) / (2 * pow(q.w(), 2) + 2 * pow(q.x(), 2) - 1));
    } else {
    euler.x() = atan((2 * q.y() * q.z() + 2 * q.x() * q.w()) / (2 * pow(q.w(), 2) + 2 * pow(q.y(), 2) - 1));
    euler.z() = 0;
    }*/

  ROLL = -180 / pi * euler.y();
  PITCH = -180 / pi * euler.z();
  YAW = -180 / pi * euler.x();

  // Serial.print(euler.x());
  // Serial.print(",");

  YAW_0 = YAW - YAW_0_offset;

  if (YAW_0 > 180) {
    YAW_0 = YAW_0 - 360;
  } else if (YAW_0 < -180) {
    YAW_0 = YAW_0 + 360;
  }

  //Serial.print(F("Orientation: "));
  //Serial.print(ROLL);
  //Serial.print(F(" "));
  //Serial.print(PITCH);
  //Serial.print(F(" "));
  //Serial.print(YAW);
  //Serial.println(F(""));

  uint8_t sys, gyro, accel, mag = 0;
  bno.getCalibration(&sys, &gyro, &accel, &mag);

  // Status_sys = sys;
  // Status_gyro = gyro;
  // Status_acc = accel;
  // Status_mag = mag;

  //Serial.print(F("Calibration: "));
  //Serial.print(Status_sys, DEC);
  //Serial.print(F(", "));
  //Serial.print(Status_gyro, DEC);
  //Serial.print(F(", "));
  //Serial.print(Status_acc, DEC);
  //Serial.print(F(", "));
  //Serial.print(Status_mag, DEC);
  //Serial.println(F(""));

  if (bno.isFullyCalibrated()) {
    Io.accuracy_BNO_ = 3;
  } else if (sys * gyro * accel * mag == 0) {
    Io.accuracy_BNO_ = 0;
  } else if (sys == 3 && gyro == 3 && mag == 3) {
    Io.accuracy_BNO_ = 2;
  } else {
    Io.accuracy_BNO_ = 1;
  }
}


void bno055::printEvent(sensors_event_t* event) {
  //double x = -1000000, y = -1000000 , z = -1000000; //dumb values, easy to spot problem
  if (event->type == SENSOR_TYPE_ACCELEROMETER) {
    //Serial.print("Accl:");
    accX = event->acceleration.x;
    accY = event->acceleration.y;
    accZ = event->acceleration.z;
  }
  else if (event->type == SENSOR_TYPE_MAGNETIC_FIELD) {
    //Serial.print("Mag:");
    magX = event->magnetic.x;
    magY = event->magnetic.y;
    magZ = event->magnetic.z;
  }
  else if (event->type == SENSOR_TYPE_GYROSCOPE) {
    //Serial.print("Gyro:");
    gyroX = event->gyro.x;
    gyroY = event->gyro.y;
    gyroZ = event->gyro.z;
  }
}