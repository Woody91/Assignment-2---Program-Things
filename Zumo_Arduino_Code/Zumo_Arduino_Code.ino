#include <Zumo32U4.h>

#include <Wire.h>

Zumo32U4Motors motors;

// States
enum State {
  pause_state, //state for when autonmous code is paused
  run_state   //state for when autonomous code is running
};

// What speed to run the motor
const int motorSpeed = 150;

// The value determined best for black through trial and error
const int blackColor = 250;


Zumo32U4LineSensors lineSensors;
unsigned int lineSensorValues[3]; //Three line sensors on the Zumo

int byteInc; //reads incoming serial data

State state = pause_state; //pauses autonmous behaviour as soon as program starts

void setup() {
  // put your setup code here, to run once:

  // Initialize the line sensors, and turn on the LEDs for them.
  lineSensors.initThreeSensors();
  lineSensors.emittersOn();
  
  Serial1.begin(9600);   //begins the serial communication link                   
  Serial.begin(9600);   //begins the serial communication link
}

void loop() {
  // put your main code here, to run repeatedly:

    //Reads the incoming data over the XBee modules
    if (Serial1.available()) {
      byteInc = Serial1.read();
      }

    //Read in the values
    lineSensors.read(lineSensorValues);

   //Change states
  if(byteInc == 'z') {
    state = run_state;
  }

  else if(byteInc == 'x') {
    state = pause_state;
  }
  if(state == run_state) {
    if(lineSensorValues[0] > blackColor && lineSensorValues[2] < blackColor) {
      // There's a line to the left. Veer right.
      motors.setSpeeds(motorSpeed, -motorSpeed);
    }
    else if(lineSensorValues[0] < blackColor && lineSensorValues[2] > blackColor) {
      // There's  line to the right. Veer left.
      motors.setSpeeds(-motorSpeed, motorSpeed);
    } else if(lineSensorValues[0] > blackColor && lineSensorValues[2] > blackColor) {
      //This stops the autonmous behaviour of the Zumo
      motors.setSpeeds(0, 0);

      int bytesSent = Serial.write("Reached A Corner");

      //This would normally turn the Zumo at a dead end and carry on autonomously
      /*delay(400);
      motors.setSpeeds(motorSpeed, -motorSpeed);
      delay(450);*/
      
    } else {
      // No lines. Go forward.
      motors.setSpeeds(motorSpeed, motorSpeed);
    }
 }
  else if(state == pause_state) {
    motors.setSpeeds(0, 0);
  }
  
switch(byteInc) //These are switch case statements for the keyboard controls of the GUI
  {
  case 'w':
    motors.setSpeeds(motorSpeed, motorSpeed);
    break;

  case 's':
    motors.setSpeeds(-motorSpeed, -motorSpeed);
    break;

  case 'a':
    motors.setSpeeds(-motorSpeed, motorSpeed);
    break;

  case 'd':
    motors.setSpeeds(motorSpeed, -motorSpeed);
    break;

  case 'q':
    motors.setSpeeds(0, 0);
    break;

  //90 degree turn left
  case 'c':
      delay(500);
      motors.setSpeeds(-motorSpeed, motorSpeed);
      delay(500);
      void stopCurrentCommand();
    break;
    
  //90 degree turn right
  case 'v':
      delay(500);    
      motors.setSpeeds(motorSpeed, -motorSpeed);
      delay(500);
      void stopCurrentCommand();
    break;

  default:
  break;
  }
}
