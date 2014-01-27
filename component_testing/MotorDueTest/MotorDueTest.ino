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


// Set everything up
void setup()
{
  // Put the motor to Arduino pin #9
  Motor_1.attach(9);
  Motor_2.attach(8);
  Motor_3.attach(7);
  Motor_4.attach(6);
  
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

// This code serves two purposes. The uncommented code
// speeds and slows down the motors in a continuos loop.
// The commented code allows you to supply input. Feel
// free to use whichever.
void loop()
{
  
      int i = 55;
      for (i = 55; i < 255; i++) {
          if (i == 254) i = 55; 
          Motor_1.write(i);
          Motor_2.write(i);
          Motor_3.write(i);
          Motor_4.write(i);
          delay(10);
      }
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
