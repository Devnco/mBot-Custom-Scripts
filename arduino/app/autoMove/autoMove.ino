/*************************************************************************
* File Name          : autoMove.ino
* Author             : Jeremy Jamar (Devnco)
* Date               : 20/04/2016
* Description        : Automove Program designed for mBot robot
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

MeDCMotor motor1(M1);
MeDCMotor motor2(M2);
MeUltrasonicSensor ultraSensor(PORT_3);
MeLineFollower lineFinder(PORT_4);
MeRGBLed led(PORT_7);
MeLightSensor lightSensor(PORT_8);
MeBuzzer buzzer;
MeRGBLed led0(PORT_1);
MeRGBLed led1(PORT_1, SLOT1, 15);
MeRGBLed led2(PORT_1, SLOT2, 15);   /* parameter description: port, slot, led number */

float j, f, k;
int16_t bri = 0, st = 0;


uint8_t motorSpeed = 200;
uint8_t turnSpeed = 100;
uint8_t goBackSpeed = 150;

bool isMoving = false;
bool startProgram = false;

void setup() {
  pinMode(A7,INPUT);
  Serial.begin(9600);
  Serial.println("AutoMove Starting …");
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
    autoMove("turnRight");
    avoidTheVoid();
    color_loop();
  }
  else {
    stopMotors();
    white_breath();
  }
  //testLightSensor();
}

void color_loop()
{
  for(uint8_t t = 1; t < 15; t++)
  {
    uint8_t red  = 64 * (1 + sin(t / 2.0 + j / 4.0) );
    uint8_t green = 64 * (1 + sin(t / 1.0 + f / 9.0 + 2.1) );
    uint8_t blue = 64 * (1 + sin(t / 3.0 + k / 14.0 + 4.2) );
    led0.setColorAt(t, red, green, blue);
  }
  led0.show();
  j += random(1, 6) / 6.0;
  f += random(1, 6) / 6.0;
  k += random(1, 6) / 6.0;
}

void white_breath(){
  if(bri >= 100)
  {
    st = 1;
  }
  if(bri <= 0)
  {
    st = 0;
  }

  if(st)
  {
    bri--;
  }
  else
  {
    bri++;
  }
  for(int16_t t = 0; t < 15; t++)
  {
    led1.setColorAt(t, bri, bri, bri); /* parameter description: led number, red, green, blue, flash mode */
    led2.setColorAt(t, bri, bri, bri);
  }
  led1.show();
  led2.show();
  delay(20);
}
void avoidTheVoid(){
   int sensorState = lineFinder.readSensors();
   switch( sensorState ){
      case 0:
        moveMbot("stepBack");
        moveMbot("goBack");
        runMotors(motorSpeed);
        break;
      case 1:
        moveMbot("stepBack");
        moveMbot("turnRight");
        runMotors(motorSpeed);
        break;
      case 2:
        moveMbot("stepBack");
        moveMbot("turnLeft");
        runMotors(motorSpeed);
        break;
      case 3:

        break;
      default: break;
   }
}

int randomBetween(int a, int b){
    return rand()%(b+1-a) +a;
}

void autoMove(String instruction){
  
  if( checkProximity() ){

      if( instruction == "random" ){
        int r = randomBetween(1, 3);
        switch( r ){
          case 1: 
            moveMbot("turnRight");
            break;
          case 2:
            moveMbot("turnLeft");
            break;
          case 3:
            moveMbot("goBack");
            break;
        }
      }
      else if( instruction == "turnRight" ) {
        moveMbot("turnRight");
      }
      else if( instruction == "turnLeft" ) {
        moveMbot("turnLeft");
      }
      else if( instruction == "goBack" ) {
        moveMbot("goBack");
      }
      runMotors(motorSpeed);
  }
}

void moveMbot( String action ){
  isMoving = true;
  Serial.print("moveMbot() : ");
  Serial.println(action);
  if( action == "turnLeft" ){
    changeLedColor(1,"blue", 255);
    motor1.run(turnSpeed);
    motor2.run(turnSpeed);
    delay(750);
  }else if ( action == "turnRight" ) {
    changeLedColor(0,"blue", 255);
    motor1.run(-turnSpeed);
    motor2.run(-turnSpeed);
    delay(750);
    led.setColorAt(0, 0, 0, 255);
  }else if ( action == "goBack" ){
    changeLedColor(2,"red", 255);
    motor1.run(turnSpeed);
    motor2.run(turnSpeed);
    delay(1500);
  }else if ( action == "stepBack" ){
    changeLedColor(2,"green", 100);
    motor1.run(goBackSpeed);
    motor2.run(-goBackSpeed);
    delay(500);
  };
  motor1.stop();
  motor2.stop();
  delay(0);
  changeLedColor(2,"red", 0);
  isMoving = false;
}

bool checkProximity(){
  int distanceCM = ultraSensor.distanceCm();
  if( distanceCM <= 5){
    Serial.println("Proximity sensor is less thant 5cm");
    return true;
  }
  else {
    return false;
  }
}

void runMotors(int speed){
  motor1.run(-speed);
  motor2.run(speed);
}

void stopMotors(){
  motor1.stop();
  motor2.stop();
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

