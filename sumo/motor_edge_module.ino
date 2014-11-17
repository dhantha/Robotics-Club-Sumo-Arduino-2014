#include <ZumoBuzzer.h>
#include <ZumoMotors.h>
#include <Pushbutton.h>
#include <QTRSensors.h>
#include <ZumoReflectanceSensorArray.h>
#include <avr/pgmspace.h>
#include <Wire.h>
#include <LSM303.h>

//Motor Module and edge detection module 
/*
Motor module will perform motions depending on the state of the robot 
Locating mode -> Arching
Attacking mode -> Line following
Edge detection -> detect the edge of the arena
*/

#define LED 13
Pushbutton button(ZUMO_BUTTON); // push button on pin 12

// Accelerometer Settings
#define RA_SIZE 3
#define XY_ACCELERATION_THRESHOLD 2400

//Reflectance Settings
#define NUM_SENSORS 6
unsigned int sensor_values[NUM_SENSORS];

#define QTR_THRESHOLD 1500 // need to be change depending on the lighting conditions
ZumoReflectanceSensorArray sensors(QTR_NO_EMITTER_PIN);

ZumoMotors motors;

#define REVERSE_SPEED 200
#define TURN_SPEED 200
#define SEARCH_SPEED 200
#define SUSTAINED_SPEED 400
#define FULL_SPEED 400
#define ARCHING_RIGHT 200
#define ARCHING_LEFT 180

#define STOP_DURATION 100 //ms
#define REVERSE_DURATION 200
#define TURN_DURATION 400

#define RIGHT 1
#define LEFT -1

enum ForwardSpeed{
  SearchSpeed,
  SustainedSpeed,
  FullSpeed
};
ForwardSpeed _forwardSpeed;

void setup(){

}

void loop(){
/*
call need to be made depending on each state
state1 :  arching state -> arching()
state2 : atacking state -> line following 


edge detection 

if (sensor_values[0] < QTR_THRESHOLD){
  turn(RIGHT,true);
}
else if(sensor_values[5] < QTR_THRESHOLD){
  turn(LEFT,true);
}


*/
}

//arching 
void arching(){
  //motors.setSpeeds(left speed, right speed);
  motors.setSpeeds(ARCHING_LEFT,ARCHING_RIGHT); //infinite, keep on arching
}
//attacking - collision full power
void attacking(){
  motors.setSpeeds(FULL_SPEED,FULL_SPEED);
}
//defence

//edge detection
void turn(char direction, bool randomize){
  
  //on contact lost
  
  static unsigned int duration_increment = TURN_DURATION/4;
  
  motors.setSpeeds(0,0); // stop
  motors.setSpeeds(-REVERSE_SPEED,REVERSE_SPEED); //reverse
  delay(REVERSE_DURATION); // reverse untill
  motors.setSpeeds(TURN_SPEED * direction , -TURN_SPEED * direction); // rotate
  delay(randomize? TURN_DURATION + random(3,6)*duration_increment : TURN_DURATION );
  int speed = getForwardSpeed();
  motors.setSpeeds(speed,speed);
  //last_run_time = millis();
}


//return the curren speed
int getForwardSpeed(){
  int speed;
  switch(_forwardSpeed){
    case FullSpeed:
      speed = FULL_SPEED; // attacking mode speed settings 
      break;
    case SustainedSpeed:
      speed = SUSTAINED_SPEED;
      break;
    default:
      speed = SEARCH_SPEED; // arching mode
      break;
  }
  return speed;
}


