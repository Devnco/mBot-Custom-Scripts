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
MeLightSensor lightSensor(PORT_8);
MeBuzzer buzzer;
MeRGBLed ledOnboard(PORT_7);
MeRGBLed ledExtra(PORT_1);

float j, f, k;
int16_t bri = 0, st = 0;


uint8_t motorSpeed = 200;
uint8_t turnSpeed = 100;
uint8_t goBackSpeed = 150;

bool isMoving = false;
bool startProgram = false;
int activeMod = 0;

void setup() {
  pinMode(A7,INPUT);
  Serial.begin(9600);
  Serial.println("Mutlimods Starting …");
  lightSensor.lightOn();
}

void loop() {
  listendButton();

  if( startProgram ){
    switch( activeMod ){
      case 0:
          extraLedColorLoop();
          autoMove("turnRight");
          avoidTheVoid();
        break;
      case 1:
          stopMotors();
          changeLedColor(2, "red", 255);
          ledExtra.setColorAt(0, 255, 0, 0);
          ledExtra.setColorAt(1, 255, 0, 0);
          ledExtra.setColorAt(2, 255, 0, 0);
          ledExtra.setColorAt(3, 255, 0, 0);
          ledExtra.show();
          //changeLedColorX(0, "blue", 255, "board");
          //buzzer.tone(300, 300);
          delay(10);
        break;
      case 2:
          stopMotors();
          changeLedColor(2, "green", 255);
          ledExtra.setColorAt(0, 0, 255, 0);
          ledExtra.setColorAt(1, 0, 255, 0);
          ledExtra.setColorAt(2, 0, 255, 0);
          ledExtra.setColorAt(3, 0, 255, 0);
          ledExtra.show();

          //extraLedWhiteBreath();
          //buzzer.tone(500, 300);
          delay(10);
        break;
    }
  }
  else {
    changeLedColor(2, "green", 0);
    extraLedWhiteBreath();
  }
}

void listendButton() {
  if( analogRead(A7) == 0 ){
    if( startProgram ){
      buzzer.tone(900, 300);
      activeMod++;
      if( activeMod >= 3){
        activeMod = 0;
      }
    }
    delay(200);
    if( analogRead(A7) == 0 ){
      buzzer.tone(700, 300);
      delay(30);
      buzzer.tone(700, 300);
      delay(10);
      startProgram = !startProgram;
    }
  }
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
  }else if ( action == "goBack" ){
    changeLedColor(2,"red", 255);
    motor1.run(turnSpeed);
    motor2.run(turnSpeed);
    delay(1500);
  }else if ( action == "stepBack" ){
    changeLedColor(2,"yellow", 100);
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
    ledOnboard.setColorAt(0, r, g, b);
    ledOnboard.setColorAt(1, r, g, b);
    ledExtra.setColorAt(0, r, g, b);
    ledExtra.setColorAt(1, r, g, b);
    ledExtra.setColorAt(2, r, g, b);
    ledExtra.setColorAt(3, r, g, b);
    ledExtra.show();
  }
  else {
    ledOnboard.setColorAt(id, r, g, b);
  }
  ledOnboard.show();
}

void extraLedColorLoop() {
  for(uint8_t t = 0; t < 15; t++)
  {
    uint8_t red  = 64 * (1 + sin(t / 2.0 + j / 4.0) );
    uint8_t green = 64 * (1 + sin(t / 1.0 + f / 9.0 + 2.1) );
    uint8_t blue = 64 * (1 + sin(t / 3.0 + k / 14.0 + 4.2) );
    ledExtra.setColorAt(t, red, green, blue);
  }
  ledExtra.show();
  j += random(1, 6) / 6.0;
  f += random(1, 6) / 6.0;
  k += random(1, 6) / 6.0;
}

void extraLedWhiteBreath() {
  if(bri >= 100){
    st = 1;
  }
  if(bri <= 0){
    st = 0;
  }

  if(st){
    bri--;
  }
  else{
    bri++;
  }
  for(int16_t t = 0; t < 15; t++){
    ledExtra.setColorAt(t, bri, bri, bri);
  }
  ledExtra.show();
  delay(20);
}
