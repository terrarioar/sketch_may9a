#include <Arduino.h>
#include <SCoop.h>
#include "motor.h"
//Motor 1
#define AIN1 3 //Speed control 
#define AIN2 5 //Direction

 //Motor 2
#define BIN1 6 //Speed control 
#define BIN2 9 //Direction

 //Motor 3
#define CIN1 10 //Speed control 
#define CIN2 11 //Direction

Motor motorA(AIN1,AIN2),motorB(BIN1,BIN2),motorC(CIN1,CIN2);
bool AEN = 0,BEN = 0,CEN = 0;

void setMotorsStatus(bool dirA,bool dirB,bool dirC,int timeA,int timeB,int timeC){
  motorA.setStatus(dirA,timeA);
  motorB.setStatus(dirB,timeB);
  motorC.setStatus(dirC,timeC);
}

void setEN(bool a,bool b,bool c){
  AEN = a;
  BEN = b;
  CEN = c;
}

void Motor::move(){
    digitalWrite(inpin, LOW); 
    digitalWrite(outpin, LOW);    
    unsigned long start =  millis();   
    for (int a1=0;a1<=255;a1+=4){
      if ( millis() - start >= times){break;}
      analogWrite(inpin,a1);
      digitalWrite(outpin,dir);
      sleep(2);
    }
    while(millis() - start <= times)
    digitalWrite(inpin, LOW); 
    digitalWrite(outpin, LOW); 
}

defineTaskLoop(TaskOne){
  if (AEN == 1){
    motorA.move();
    AEN = 0;
    Serial.println('A');
  }
}

defineTaskLoop(TaskTwo){
  if (BEN == 1){
    motorB.move();
    BEN = 0;
    Serial.println('B');
  }
}

defineTaskLoop(TaskThree){
  if (CEN == 1){
    motorC.move();
    CEN = 0;
    Serial.println('C');
  }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(AIN1, OUTPUT); //电机1
  pinMode(AIN2, OUTPUT);
  pinMode(BIN1, OUTPUT); //电机2  
  pinMode(BIN2, OUTPUT); 
  pinMode(CIN1, OUTPUT); //电机3  
  pinMode(CIN2, OUTPUT);
  digitalWrite(AIN1, LOW); 
  digitalWrite(AIN2, LOW); 
  digitalWrite(BIN1, LOW);
  digitalWrite(BIN2, LOW);
  digitalWrite(CIN1, LOW);
  digitalWrite(CIN2, LOW);
  mySCoop.start();
}

void loop() {
  // put your main code here, to run repeatedly:
  int ti = 0;
  if (Serial.available() > 0) { //检查串口缓存是否有数据
    char cmd = Serial.read();  //获取串口缓存中的数据
    //A、B、C是三种步态,大写前进、小写后退
    switch (cmd) {             //对cmd的数据与控制的方式进行匹配
      case'A': 
       ti = Serial.parseInt();
       setMotorsStatus(0,0,0,ti,ti,ti);
       setEN(1,1,1);//电机使能
       while (AEN == 1 || BEN == 1 || CEN == 1){
        yield();
       }
       break;
      case'a': 
       ti = Serial.parseInt();
       setMotorsStatus(1,1,1,ti,ti,ti);
       setEN(1,1,1);
       while (AEN == 1 || BEN == 1 || CEN == 1){
        yield();
       }
       break;
      case'B': 
       ti = Serial.parseInt();
       setMotorsStatus(0,0,0,ti,ti,ti);
       setEN(1,1,1);
       while (AEN == 1 || BEN == 1 || CEN == 1){
        yield();
       }
       break;
      case'b': 
       ti = Serial.parseInt();
       setMotorsStatus(1,1,1,ti,ti,ti);
       setEN(1,1,1);
       while (AEN == 1 || BEN == 1 || CEN == 1){
        yield();
       }
       break;
      case'C': 
       ti = Serial.parseInt();
       setMotorsStatus(0,0,0,ti,ti,ti);
       setEN(1,1,1);
       while (AEN == 1 || BEN == 1 || CEN == 1){
        yield();
       }
       break;
      case'c': 
       ti = Serial.parseInt();
       setMotorsStatus(1,1,1,ti,ti,ti);
       setEN(1,1,1);
       while (AEN == 1 || BEN == 1 || CEN == 1){
        yield();
       }
       break;    
    }
  }
}


