#include <Wire.h>


/*
* Variable Instantiation
*/
// Create motor variables to hold the speed value
// TODO: Create variables for all motors
int starboardVal;

// Assign pin values for each motor value to be
// written to.
// TODO: Create these pins for all values
int starboardPin;

//===============================================================================>
// Name: setup
//
// Description: Arms the motors and performs various functions
//===============================================================================>
void setup() {
  
   // assign a base value
   // TODO: Do this for other values
   starboardVal = 0;
 
   // assign pin to variables
   // TODO: Do this for all pins
   starboardPin = 53;
   
   Wire.begin(6);
   Wire1.begin(6);
   Wire.onReceive(receiveEvent);
   
   // set the pin mode
   // TODO: Do this for all pins
   // pinMode(starboardPin, OUTPUT);
}

//===============================================================================>
// Name: loop
//
// Description: The main loop controlling all of the functionality
//===============================================================================>
void loop() {
  //int i;
  //for (i = 35; i < 90; i++) {
     //starboardVal = i;
     //digitalWrite(starboardPin, starboardVal);
     Wire.beginTransmission(4);
     Wire.write(99);
     Wire.endTransmission();
     delay(50);
   //}
}

void receiveEvent(int howMany)
{
  //funct();
  //delay(5000);
}

void funct()
{
  int i;
  for (i = 35; i < 90; i++) {
     starboardVal = i;
     //digitalWrite(starboardPin, starboardVal);
     Wire1.beginTransmission(4);
     Wire1.write(starboardVal);
     Wire1.endTransmission();
     Serial.println(i);
     delay(500);
   }
}
