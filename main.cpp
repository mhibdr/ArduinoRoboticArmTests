// Die liberiry, die wie es benuzen werden

#include <Arduino.h>
#include <Servo.h>
#include <SoftwareSerial.h>
#include <math.h>

// PIN-Definition

#define S1PIN 10
#define S2PIN 11
#define S3PIN 12
#define S4PIN 13
#define Joy_Y A0
#define Joy_X A1
#define Joy_B A2
#define PotM  A3
#define L1    200 // Test
#define W1    150 // Test
#define bthRX 3
#define bthTX 2
/*
#define MAX_SAngle    90
#define MAX_Speed    10
#define MIN_Speed    2000
#define MAX_Distance 350
*/

// Varibalen und device definition

SoftwareSerial bth( bthTX , bthRX ); //  Arduino RX  , TX
Servo S1 , S2 , S3 , S4;
String com;
int S1POS , S2POS , S3POS , S4POS;
int S1PPOS , S2PPOS , S3PPOS , S4PPOS;
float angle1 , angle2 , angle3;
int Joy_X_Val , Joy_Y_Val , Joy_B_Val ;
int delay_val = 20;
float Distance = 0.00;
int joy = 0;

boolean states = false;

// wenn Atduion ist zu erste dingen die gemacht werden

void setup() {
 
  S1.attach(S1PIN);
  S1PPOS = S1.read();
  S2.attach(S2PIN);
  S2PPOS = S2.read();
  S3.attach(S3PIN);
  S3PPOS = S3.read();
  S4.attach(S4PIN);
  S4PPOS = S4.read();

  pinMode (Joy_X, INPUT);
  pinMode (Joy_Y, INPUT);
  pinMode (Joy_B, INPUT);
  pinMode (PotM , INPUT);

  digitalWrite(Joy_B , HIGH);

  bth.begin(38400); 

}

//Unser Robot funktonen

void loop() {

  Joy_X_Val = analogRead(Joy_X);
  Joy_Y_Val = analogRead(Joy_Y);
  Joy_B_Val = analogRead(Joy_B);
  delay_val = analogRead(PotM);
  com = bth.readString();
 
  if(bth.available() >= 0){

   

    if(com.startsWith("s1")){                   // Z servo
      String CMD = com.substring(2 ,com.length());
      S1POS = CMD.toInt();
      if(S1POS > S1PPOS){
        for(int i = S1PPOS ; i < S1POS ; i++){
          S1.write(i);
          delay(delay_val);
        }
      }
      if(S1POS < S1PPOS){
        for(int i = S1PPOS ; i > S1POS ; i--){
          S1.write(i);
          delay(delay_val);
        }
      S1PPOS = S1POS;
    }
  }

    if(com.startsWith("s2")){                   // X servo
      String CMD = com.substring(2 ,com.length());
      S2POS = CMD.toInt();
      if(S2POS > S2PPOS){
        for(int i = S2PPOS ; i < S2POS ; i++){
          S2.write(i);
          delay(delay_val);
        }
      }
      if(S2POS < S2PPOS){
        for(int i = S2PPOS ; i > S2POS ; i--){
          S2.write(i);
          delay(delay_val);
        }
      S2PPOS = S2POS;
    }
  }

    if(com.startsWith("s3")){                     // Rotation Servo , Y servo
      String CMD = com.substring(2 ,com.length());
      S3POS = CMD.toInt();
      if(S3POS > S3PPOS){
        for(int i = S3PPOS ; i < S3POS ; i++){
          S2.write(i);
          delay(delay_val);
        }
      }
      if(S3POS < S3PPOS){
        for(int i = S3PPOS ; i > S3POS ; i--){
          S3.write(i);
          delay(delay_val);
        }
      S3PPOS = S3POS;
    }
  }

    if(com.startsWith("s4")){                         // Gripper Servo
      String CMD = com.substring(2 ,com.length());
      S1POS = CMD.toInt();
      if(S4POS > S4PPOS){
        for(int i = S4PPOS ; i < S4POS ; i++){
          S4.write(i);
          delay(delay_val);
        }
      }
      if(S4POS < S4PPOS){
        for(int i = S4PPOS ; i > S4POS ; i--){
          S2.write(i);
          delay(delay_val);
        }
      S4PPOS = S4POS;
    }
  }

    if(com.startsWith("speed")){                         // Die Geschwindeigkeit des Servo
      delay_val = com.substring(5 , com.length()).toInt();
    }
   
  }
 
  // Control with Joystick KY-04
  if(bth.available() <= 0){
    angle1 = ((90 - S1POS ) * PI) / 180;
    angle2 = ((90 - S2POS ) * PI) / 180;
    Joy_X_Val = map(Joy_X_Val , 0 , 1023 , 180 , 0);
    Joy_Y_Val = map(Joy_Y_Val , 0 , 1023 , 180 , 0);
    Joy_B_Val = map(Joy_B_Val , 0 , 1023 , 0 , 500);
    delay_val = map(delay_val, 0 , 1023 , 20 , 70);

    if(Joy_X_Val > 95  ){

        delay(delay_val);
    }

    if(Joy_Y_Val > 95 && S3PPOS < 180){
        S3PPOS++;
        S3.write(S3POS);
        delay(delay_val);
    }

    if(Joy_X_Val < 95){
     
      delay(delay_val);
    }

    if(Joy_Y_Val < 95 && S3PPOS > 0 ) {
      S3PPOS--;
      S3.write(S3POS);
      delay(delay_val);
    }

  if(Joy_B_Val < 10 && S4PPOS > 90){
    S4PPOS--;
    S4.write(S4PPOS);
    delay(20);
   }else if(S4PPOS < 90) {
     S4PPOS++;
     S4.write(S4PPOS);
     delay(20);
   }

  }

}
