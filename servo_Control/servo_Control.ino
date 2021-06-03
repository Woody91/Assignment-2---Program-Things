#include <Servo.h>
Servo middle, left, right, claw ; // creates 4 "servo objects"
void setup()
{
Serial.begin(9600);
middle.attach(11); // attaches the servo on pin 11 to the middle object
left.attach(10); // attaches the servo on pin 10 to the left object
right.attach(9); // attaches the servo on pin 9 to the right object
claw.attach(6); // attaches the servo on pin 6 to the claw object
}

int byteInc;

void loop()
{

  switch(byteInc) //These are switch case statements for the keyboard controls of the GUI
  {
  case 'w':
    left.write(45);
    right.write(45);
    break;

  case 's':
    left.write(-45);
    right.write(-45);
    break;

  case 'a':
    middle.write(-45);
    break;

  case 'd':
    middle.write(45);
    break;

  case 'z':
    claw.write(-25);
    break;

  case 'x':
    claw.write(25);
    break;

default:
  break;
  }
}
