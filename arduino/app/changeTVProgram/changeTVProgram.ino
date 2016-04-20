/*************************************************************************
* File Name          : changeTVProgram.ino
* Author             : Jeremy Jamar (Devnco)
* Date               : 20/04/2016
* Description        : Change TV Program designed for mBot robot
**************************************************************************/

/*
 * Mapping
 * 
 * PORT_3 : UltraSensor
 * PORT_4 : LineFinder
 * PORT_7 : Led
 * PORT_8 : LightSensor
 * PORT_9 : IRReceiver
 */

#include "MeMCore.h"


MeUltrasonicSensor ultraSensor(PORT_3);
MeLineFollower lineFinder(PORT_4);
MeRGBLed led(PORT_7);
MeLightSensor lightSensor(PORT_8);
MeBuzzer buzzer;

bool startProgram = false;

void setup() {
  pinMode(A7,INPUT);
  Serial.begin(9600);
  Serial.println("Change TV Program Starting …");
  lightSensor.lightOn();
}

void loop() {
  if( analogRead(A7) == 0 ){
    delay(200);
    buzzer.tone(700, 300);
    delay(30);
    buzzer.tone(700, 300);
    delay(10);
    startProgram = !startProgram;

  }
  if( startProgram ){
    // TODO
  }
  else {
  }
}

void changeLedColor(int id, String color, int power){
  int r = 0;
  int g = 0;
  int b = 0;

  if( color == "red" ){
    r = power;
  }
  if( color == "green" ){
    g = power;
  }
  if( color == "blue" ){
    b = power;
  }
  if( color == "yellow" ){
    r = power;
    g = power;
  }
  if( color == "cyan" ){
    g = power;
    b = power;
  }
  if( color == "magenta" ){
    b = power;
    r = power;
  }
  if( id == 2 ){
    led.setColorAt(0, r, g, b);
    led.setColorAt(1, r, g, b);
  }
  else {
    led.setColorAt(id, r, g, b);
  }
  led.show();
}

