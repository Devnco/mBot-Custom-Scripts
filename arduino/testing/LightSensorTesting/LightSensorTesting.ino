/*************************************************************************
* File Name          : LightSensorTesting.ino
* Author             : Jeremy Jamar (Devnco)
* Date               : 20/04/2016
* Description        : Test Light Sensor
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

MeLightSensor lightSensor(PORT_8);

void setup() {
  Serial.begin(9600);
  Serial.println("Light Sensor Testing");
  lightSensor.lightOn();
}

void loop() {
  int value = lightSensor.read();
  Serial.print("value = ");
  Serial.println(value);
  delay(1000);
}
