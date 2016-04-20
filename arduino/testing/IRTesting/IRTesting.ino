/*************************************************************************
* File Name          : IRTesting.ino
* Author             : Jeremy Jamar (Devnco)
* Date               : 20/04/2016
* Description        : Testing IR Receiver
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

MeIR ir;

void setup() {
  Serial.begin(9600);
  buzzerOn();
  delay(50);
  buzzerOff();
}

void loop() {
  Serial.println(ir.value);
}

void buzzerOn(){
  buzzer.tone(500,1000); 
}
void buzzerOff(){
  buzzer.noTone(); 
}
