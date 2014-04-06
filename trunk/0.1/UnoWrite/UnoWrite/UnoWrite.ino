/* ==================================================================================
 * File: UnoWrite.ini
 * System: Write Uno
 * Team: MUSCA
 * Course Info: CSE 423 Fall 2013
 * 
 * Author(s): Taylor Wood
 * Email: Taylorwood67@gmail.com
 * ==================================================================================
 * Description: This is the ini file to be uploaded to the UNO board. This controls
 * reading from the computation register and writing to the motors. This should handle
 * arming the motor and other various funcitons specific to motors.
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
#include <Servo.h>
#include <Wire.h> 
 
/*
 * Variable Instantiation
 */
// Create Servo objects
Servo Motor_Starboard, Motor_Port, Motor_Stern, Motor_Bow;

// create pin variables to read from
// TODO: Create all other pins for other motors.
int starboardPin;

// motor speeds read from the pins
// TODO: Create the rest of the variables
int starboardVal;
  
//===============================================================================>
// Name: setSpeed
//  
// Input:  starboard <int> = Value to write to Starboard Motor
//         port <int> = Value to write to Port Motor
//         stern <int> = Value to write to Stern Motor
//         bow <int> = Value to write to Bow Motor
//
// Description: This function simply writes values to motors
//===============================================================================>
void setSpeed(int starboard, int port, int stern, int bow) {
   Motor_Starboard.write(starboard);
   Motor_Port.write(port);
   Motor_Stern.write(stern);
   Motor_Bow.write(bow);
 }

//===============================================================================>
// Name: setup
//
// Description: Arms the motors and performs various functions
//===============================================================================>
void setup() {
  
  // Required for I/O from Serial monitor
  Serial.begin(9600);
  // Print a startup message
  Serial.println("initializing");
  
   // give pin values 0
   // TODO: Give remaining pins a value
   starboardVal = 0;
  
   // setup the pins where data will be read
   // TODO: Give other pins a value
   starboardPin = 8;
   
   // create pin modes
   // TODO: Do this for the rest of the pins
   //pinMode(starboardPin, INPUT); 
   // using i2c
   Wire.begin(4);
   Wire.onReceive(receiveEvent);
   
   // TODO: Attach other motors
   Motor_Starboard.attach(starboardPin); 
   
   // ARM the motor
   // TODO: Still need to figure out how to accurately arm the motors
   // with the new firmware
   int i;
   for (i = 0; i < 55; i++) {
      Serial.println(i,DEC);
      setSpeed(i, 0, 0, 0);
      delay(100);
   }
   
}

//===============================================================================>
// Name: loop
//
// Description: The main function which will continuosly write to the motors
//===============================================================================>
void loop() {
  delay(100);
}

//===============================================================================>
// Name: ReceiveEvent
//
// Description: The handler for an i2c Event
//===============================================================================>
void receiveEvent(int howMany)
{
  int x = Wire.read();    // receive byte as an integer
  Serial.println(x);         // print the integer
  Motor_Starboard.write(x);
}
