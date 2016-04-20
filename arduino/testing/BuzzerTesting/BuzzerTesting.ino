/*************************************************************************
* File Name          : BuzzerTesting.ino
* Author             : Jeremy Jamar (Devnco)
* Date               : 20/04/2016
* Description        : Buzzer Testing
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

MeBuzzer buzzer;

void setup() {
  Serial.begin(9600);
}

void loop() {
  buzzerOn();
  delay(50);
  buzzerOff();
  delay(200);
}

void buzzerOn(){
  buzzer.tone(500,1000); 
}
void buzzerOff(){
  buzzer.noTone(); 
}
