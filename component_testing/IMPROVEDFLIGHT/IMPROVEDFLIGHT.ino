/*
*  This code is in the public domain.
*  (Do whatever you want with it.)
*/

// Need the Servo library
#include <Servo.h>
#include <Wire.h>
// This is our motor.
Servo Motor_1, Motor_2, Motor_3, Motor_4;

// This is the final output
// written to the motor.
String incomingString;
int Motor_rot = 88;
int Motor_Const_Speed = 45;

int ch;
int i;
int Motor_max;
int Motor_min;
int timess = 0;
// 1                4             2              3
int Motor_Bow_Speed = 40, Motor_Port_Speed = 40, Motor_Starboard_Speed = 40, Motor_Stern_Speed = 40;
// learn your boat terminology

int distance;
byte thisis[5];

  // Need a value to determine if the motor speed was recently incremented 
  int recentIncr;

void setSpeed(int speed_port, int speed_starboard) {
    int ms1 = map(speed_port, 0, 100, 0, 180);
    int ms2 = map(speed_starboard, 0, 100, 0, 180);
    Motor_1.write(ms1);
    Motor_4.write(ms2);
}


// Set everything up
void setup()
{  
  Wire.begin(4);
  
  recentIncr = 0;
  
  // Put the motor to Arduino pin #4
  Motor_1.attach(2);
  Motor_2.attach(3);
  Motor_3.attach(5);
  Motor_4.attach(4);
  
  Motor_min = 35;
  Motor_max = 60;
  
  i = 55;
  distance=0;
 
  int p;
  for (p = 5; p <= 40; p = p + 5) {
   setSpeed(p,p);
   delay(1000); 
  }

  // Required for I/O from Serial monitor
  Serial.begin(9600);
  // Print a startup message
  Serial.println("initializing");
  
  delay(5000); // allow time for IMU data to stabilize
  Wire.onReceive(receiveEvent); // register event
  Serial.print("ON");
  
}


void loop()
{  
  
 

     /* for (i = 55; i < Motor_max; i++) {
          delay(500);
          //Serial.print("i = ");
          //Serial.println(i, DEC);
          Motor_1.write(i);
          Motor_2.write(i);
          Motor_3.write(i);
          Motor_4.write(i);
          
          distance = getDistance();
          Serial.println("Distance is: ");
          Serial.print(distance);
      }
      for (i = Motor_max; i > Motor_min; i--) {
          delay(100);
          //Serial.print("i = ");
          //Serial.println(i, DEC);
 
          
          distance = getDistance();
          Serial.println("Distance is: ");
          Serial.print(distance);
      }*/
      //delay(10000);
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
/******************* COMMENTED OUT FOR AXIS TESTING ************************/
/*
int getDistance()
{
  int x;
  x = analogRead(2); //read value from analog pin 2 (A2)
  return x;
}
  
*/
/**************************************************************************/

void receiveEvent(int howMany)
{

   if (timess >= 400)
   { 
     int j = 100;
     for (j = 100; j >= 55; j--) {
       Motor_1.write(j);
        //Motor_2.write(j);
        //Motor_3.write(j); 
        Motor_4.write(j); 
        delay(100);   
     }
        
   }   
    

  while(Wire.available()!=0) // loop through all but the last
  {
  
    //int broll = Wire.read(); // receive byte as a character
//    Serial.println("***********************");
    Wire.requestFrom(2, 5);
    thisis[0]= Wire.read();
    thisis[1]= Wire.read();
    thisis[2]= Wire.read();
    thisis[3]= Wire.read();
    thisis[4]= Wire.read();


/********************************** COMMENTED OUT FOR AXIS TESTING ************************/
/*
    distance = getDistance();     

   // Too low. MOAR POWA!!!!
    if (distance > 250)
     { 
       Motor_Const_Speed = Motor_Const_Speed + 1;
     }
    // whoa.. slow down 
    else if (distance < 200) 
     {
       Motor_Const_Speed = Motor_Const_Speed - 1;
     }  
  */
 /******************************************************************************************/ 
    // If roll is negative
    if ((thisis[1] & 1) == 1) {
      //Serial.println("Roll is negative degrees");
      //Motor_Starboard_Speed = Motor_Const_Speed + .25 * (thisis[2]);    // Coeff. placed for tested
      //Motor_Port_Speed = (Motor_Const_Speed - .25 * (thisis[2]));
      if (thisis[2] > 10 && !recentIncr) {
        Motor_Starboard_Speed++;
        recentIncr++;
      }
      else if (thisis[2] > 10 && recentIncr) recentIncr++;
    }
    // else positive
    else { 
      // If the difference is 2
      if (thisis[2] > 10 && !recentIncr) {
        Motor_Port_Speed++;
        recentIncr++;
      }
      else if (thisis[2] > 10 && recentIncr) recentIncr++;
      //Motor_Starboard_Speed = Motor_Const_Speed - .25 *(thisis[2]);
      //Motor_Port_Speed = (Motor_Const_Speed + .25 * (thisis[2]));
    }
    
    if (recentIncr > 5)
        recentIncr = 0;
    
    Serial.println(thisis[2]);
    
    // if pitch is negative
    if ((thisis[1] & 2) == 2) {
      // Serial.println("Pitch is negative degrees");
      Motor_Stern_Speed = Motor_Const_Speed + (int)(thisis[3] / 2);
      Motor_Bow_Speed = Motor_Const_Speed - (int)(thisis[3] / 2);
    }
    else {
      Motor_Stern_Speed = Motor_Const_Speed - (int)(thisis[3] / 2);
      Motor_Bow_Speed = Motor_Const_Speed + (int)(thisis[3] / 2);
    }
    

   if (Motor_Starboard_Speed > Motor_max)
         Motor_Starboard_Speed = 40;
    if (Motor_Port_Speed > Motor_max)
         Motor_Port_Speed = 40;
    if (Motor_Stern_Speed > Motor_max)
         Motor_Stern_Speed = 40;
    if (Motor_Bow_Speed > Motor_max)
        Motor_Bow_Speed = 40;
    //Motor_1.write(Motor_Bow_Speed);
     //Serial.print("Starboard Speed: ");
     //Serial.println(Motor_Starboard_Speed, DEC);
     setSpeed(Motor_Port_Speed, Motor_Starboard_Speed);
     /*
    Motor_4.write(Motor_Starboard_Speed);
    Serial.print("Starboard: ");
    Serial.println(Motor_Starboard_Speed, DEC);
   // Motor_3.write(Motor_Stern_Speed); 
    Motor_1.write(Motor_Port_Speed);
    Serial.print("Port: ");
    Serial.println(Motor_Port_Speed);
    */
     //Serial.print("Port Speed: ");
     //Serial.println(Motor_Port_Speed, DEC);
        /*
    Motor_1.write(70);
    Motor_2.write(70);
    Motor_3.write(70); 
    Motor_4.write(70);
    */
    timess++;

    /*Serial.print("Distance: ");
     Serial.print(distance);
      Serial.print("\n");
    */
    /*Serial.print("Bow: ");
     Serial.print(Motor_Bow_Speed);
      Serial.print("\n");
    
    Serial.print("Starboard: ");
     Serial.print(Motor_Starboard_Speed);
      Serial.print("\n");
    //Serial.print(Motor_Starboard_Speed);
    
    Serial.print("Stern: ");
     Serial.print(Motor_Stern_Speed);
      Serial.print("\n");
    //Serial.print(Motor_Stern_Speed);
    
    Serial.println("Port: ");
     Serial.print(Motor_Port_Speed);
      Serial.print("\n");
    //Serial.print(Motor_Port_Speed);
    
    */
//    if ((thisis[1] & 4) == 4)
//    {
//       Serial.println ("Yaw is negative degrees");
//    }
        
   //Serial.print("Check bit: ");
    //Serial.println(thisis[0]); 
    
    //Serial.println("Sign bit: ");
    //Serial.println(thisis[1]);
   
    //Serial.println("Roll: ");
   //Serial.println(thisis[2]); 
    
    //Serial.println("Pitch: ");
    //Serial.println(thisis[3]);
  
    //Serial.println("Yaw: ");  
    //Serial.print(thisis[4]);
    
  }
}

