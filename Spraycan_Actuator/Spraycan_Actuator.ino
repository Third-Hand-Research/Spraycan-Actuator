// Spraycan Actuator
//
// Turn Stepper motor to drive spray can when input pullup is active
//

#include <AccelStepper.h>

// Define stepper motor connections and motor interface type. Motor interface type must be set to 1 when using a driver:
#define dirPin 2
#define stepPin 3
#define motorInterfaceType 1

boolean isDown = false;

int upPos = 0;
int downPos = 50;

int nextPos = upPos;

// Create a new instance of the AccelStepper class:
AccelStepper stepper = AccelStepper(motorInterfaceType, stepPin, dirPin);

void setup()
{  
  pinMode(12, INPUT_PULLUP);
  pinMode(13, OUTPUT);
	stepper.setMaxSpeed(1000);
	stepper.setAcceleration(800);
}

void loop()
{

   //read the pushbutton value into a variable
  int sensorVal = digitalRead(12);
  
  // Keep in mind the pull-up means the pushbutton's logic is inverted. It goes
  // HIGH when it's open, and LOW when it's pressed. Turn on pin 13 when the
  // button's pressed, and off when it's not:
  if (sensorVal == HIGH) {
    digitalWrite(13, LOW);
  } else {
    digitalWrite(13, HIGH);
  }

  // Turn can on or off depending on input pullup value
  if (stepper.distanceToGo() == 0)
  {
    if (sensorVal == HIGH) {
      stepper.moveTo(upPos);
      isDown = false;
    } else {
      stepper.moveTo(downPos);
      isDown = true;
    }
  }
  stepper.run();
  delay(1);
}
