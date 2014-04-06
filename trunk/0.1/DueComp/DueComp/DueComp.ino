/* ==================================================================================
 * File: DueComp.ini
 * System: Computation DUE
 * Team: MUSCA
 * Course Info: CSE 423 Fall 2013
 * 
 * Author(s): Taylor Wood
 * Email: Taylorwood67@gmail.com
 * ==================================================================================
 * Description: This is the ini file to be uploaded to the Computation DUE board.
 * This board will handle all computations and write to registers for the UNO to 
 * receive. It will also read registers for IMU sensor data and UDP packets
 * ==================================================================================
 * Change History:
 *		________________________________________________________________
 * 		|| Author	|| Date		|| Description		||
 *		----------------------------------------------------------------
 * 		|| 		|| 			|| 				||
 *		----------------------------------------------------------------
 *
 * ==================================================================================*/
 
 /*
  * Libraries to include
  */
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
   
   Wire.begin();
   
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
  int i;
  for (i = 35; i < 90; i++) {
     starboardVal = i;
     //digitalWrite(starboardPin, starboardVal); 
     Wire.beginTransmission(4);
     Wire.write(starboardVal);
     Wire.endTransmission();
     delay(500);
   }
}
