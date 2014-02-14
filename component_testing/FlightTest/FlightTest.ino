/*
*  This code is in the public domain.
*  (Do whatever you want with it.)
*/

// Need the Servo library
#include <Servo.h>

// This is our motor.
Servo Motor_1, Motor_2, Motor_3, Motor_4;

// This is the final output
// written to the motor.
String incomingString;

int ch;
int i;
int Motor_max;
int Motor_min;


// Set everything up
void setup()
{
  // Put the motor to Arduino pin #9
  Motor_1.attach(2);
  Motor_2.attach(3);
  Motor_3.attach(4);
  Motor_4.attach(5);
  
  Motor_min = 55;
  Motor_max = 85;
  
  i = 55;
  
  // Arm the motors with weapons
  // Note, they arm at 55 and start
  // spinning at 60
  Motor_1.write(55);
  Motor_2.write(55);
  Motor_3.write(55);
  Motor_4.write(55);

  // Required for I/O from Serial monitor
  Serial.begin(9600);
  // Print a startup message
  Serial.println("initializing");
}


void loop()
{
  
      for (i = 55; i < Motor_max; i++) {
          delay(500);
          Serial.print("i = ");
          Serial.println(i, DEC);
          Motor_1.write(i);
          Motor_2.write(i);
          Motor_3.write(i);
          Motor_4.write(i);
      }
      for (i = Motor_max; i > Motor_min; i--) {
          delay(100);
          Serial.print("i = ");
          Serial.println(i, DEC);
          Motor_1.write(i);
          Motor_2.write(i);
          Motor_3.write(i);
          Motor_4.write(i);
      }
      delay(10000);
//    if (Serial.available() > 0) {
//      ch = Serial.parseInt();
//      
//      Serial.print("I recieved: ");
//      Serial.println(ch, DEC);
//      
//            /*
//      *  We only want to write an integer between
//      *  0 and 180 to the motor.
//      */
//      if (ch > -1 && ch < 181)
//     {
//       // Print confirmation that the
//       // value is between 0 and 180
//       Serial.println("Value is between 0 and 180");
//       // Write to Servo
//       Motor_1.write(ch);
//       Motor_2.write(ch);
//       Motor_3.write(ch);
//       Motor_4.write(ch);
//     }
//     // The value is not between 0 and 180.
//     // We do not want write this value to
//     // the motor.
//     else
//     {
//       Serial.println("Value is NOT between 0 and 180");
//     
//       // IT'S a TRAP!
//       Serial.println("Error with the input");
//     }
//        
//    }
}
