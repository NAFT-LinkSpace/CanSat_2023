#include "motor.hpp"

SoftwareSerial raspi(RX,TX);

void motor::init(){
    ledcSetup(0,12800,8);
    ledcSetup(1,12800,8);
    ledcSetup(2,12800,8);
    ledcSetup(3,12800,8);
    ledcSetup(4,12800,8);
    ledcSetup(5,12800,8);
    ledcAttachPin(led_R_1,0);
    ledcAttachPin(led_R_2,1);
    ledcAttachPin(led_L_1,2);
    ledcAttachPin(led_L_2,3);
    ledcAttachPin(led_heat_1,4);
    ledcAttachPin(led_heat_2,5);
    raspi.begin(9600);
}

void motor::moveraspi(){
    if(raspi.available()){
       raspiserial=raspi.read();

        if (raspiserial.endsWith("\r\n") && raspiserial.length() > 3)
        {
            if (raspiserial.indexOf("forward") != -1)
            {
                forward(256);
            }
            else if (raspiserial.indexOf("right") != -1)
            {
                turnright(180);
            }
            else if (raspiserial.indexOf("left") != -1)
            {
                turnleft(180);
            }
            else if(raspiserial.indexOf("stop") != -1){
                stop();
            }
        }

    }else{
        stop();
    }

}

void motor::moving(io& Io){
    
  if(abs(Io.deltatheta)<20){
    forward(256);
  }else if(sin(Io.deltatheta*pi/180)>0){
    turnleft(256);
    delay(500);
    coast();
  }else if(sin(Io.deltatheta*pi/180)<0){
    turnright(256);
    delay(500);
    coast();
  }
}

void motor::forward(int speed){
    int R1,R2,L1,L2;
    R1=0;   L1=speed;
    R2=speed;   L2=0;

    ledcWrite(0,R1);
    ledcWrite(1,R2);
    ledcWrite(2,L1);
    ledcWrite(3,L2);
}

void motor::backward(int speed){
    int R1,R2,L1,L2;
    R1=speed;   L1=speed/2;
    R2=speed/2;   L2=speed;

    ledcWrite(0,R1);
    ledcWrite(1,R2);
    ledcWrite(2,L1);
    ledcWrite(3,L2);
}

void motor::forwardlow(int speed){
    int R1,R2,L1,L2;
    R1=0;   L1=speed/2;
    R2=speed/2;   L2=0;

    ledcWrite(0,R1);
    ledcWrite(1,R2);
    ledcWrite(2,L1);
    ledcWrite(3,L2);
}

void motor::stop(){
    int R1,R2,L1,L2;
    R1=256;   L1=256;
    R2=256;   L2=256;

    ledcWrite(0,R1);
    ledcWrite(1,R2);
    ledcWrite(2,L1);
    ledcWrite(3,L2);
}

void motor::coast(){
    int R1,R2,L1,L2;
    R1=0;   L1=0;
    R2=0;   L2=0;

    ledcWrite(0,R1);
    ledcWrite(1,R2);
    ledcWrite(2,L1);
    ledcWrite(3,L2);
}

void motor::turnright(int speed){
    int R1,R2,L1,L2;
    R1=speed*2/3;   L1=speed;
    R2=speed;   L2=0;

    ledcWrite(0,R1);
    ledcWrite(1,R2);
    ledcWrite(2,L1);
    ledcWrite(3,L2);
    // analogWrite(motor_R_1,R1);
    // analogWrite(motor_R_2,R2);
    // analogWrite(motor_L_1,L1);
    // analogWrite(motor_L_2,L2);
}

void motor::turnleft(int speed){
    int R1,R2,L1,L2;
    R1=0;   L1=speed;
    R2=speed;   L2=speed*2/3;
    
    ledcWrite(0,R1);
    ledcWrite(1,R2);
    ledcWrite(2,L1);
    ledcWrite(3,L2);
    // analogWrite(motor_R_1,R1);
    // analogWrite(motor_R_2,R2);
    // analogWrite(motor_L_1,L1);
    // analogWrite(motor_L_2,L2);
}

void motor::heating(){
    ledcWrite(4,10);
    ledcWrite(5,128);
}

void motor::cooling(){
    ledcWrite(4,128);
    ledcWrite(5,128);
}

void motor::raspisend(String mess){
    raspi.println(mess);
}

void motor::raspirecive(io& Io){
    Io.message=raspi.readString();
}