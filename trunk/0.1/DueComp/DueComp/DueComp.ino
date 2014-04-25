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
int myArray[8];
int * arrayptr;
int i = 0;
         byte roll;
         byte pitch;
         byte yaw;
         byte sign;

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
   arrayptr = myArray;
   
   Wire1.begin();
   //Wire1.begin(6);
   //Wire.onReceive(receiveEvent);
   Serial.begin(9600);
   Serial1.begin(9600);
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
     //Wire.beginTransmission(4);
     //Wire.write(99);
     //Wire.endTransmission();
     //delay(50);
   //}
     //Wire1.beginTransmission(4);
     //Wire1.write(99);
     //Wire1.endTransmission();
     //delay(50);
     Serial.println("IN LOOP ");
     //Serial.flush();
   //if (Serial1.available())
   //{
     
     //for(int i = 0; i < 5; i++){ //roll, pitch, yaw, sign
     //while(Serial1.read() != '!'){ 
      //Serial1.readBytesUntil('!',myArray,5);
      //Serial.print("MyArray: ");
      //Serial.println(myArray);
    /*  byte roll = Serial1.read();
      delay(10);
      byte pitch = Serial1.read();
      delay(10);
      byte yaw = Serial1.read();*/
      
     // byte sign = Serial1.read();
      while(Serial1.available() == 0 );
       /* if(Serial1.read() == '255')
        {
          myArray[0] = Serial1.read();
          Serial.print("Roll: ");
          Serial.println(myArray[0]);
        }
        else if (Serial1.read() == 254)
        {
          myArray[1] = Serial1.read();
          Serial.print("Pitch: ");
          Serial.println(myArray[1]);
        }
        else if (Serial1.read() == 253)
        {
          myArray[2] = Serial1.read();
          Serial.print("Yaw: ");
          Serial.println(myArray[2]);
        }
        else if (Serial1.read() == 252)
        {
          myArray[3] = Serial1.read();
          Serial.print("Sign: ");
          Serial.println(myArray[3]);
        }
        else
          Serial.println("Doesnt Work ");
         */ 
         int unread = Serial1.available();
         Serial.print("Unread ");
         Serial.println(unread);
         //Serial1.flush();
        while(unread == 4)
        {
          
         roll = Serial1.read();
         if(roll == 255)
         {
         Serial1.flush();
         break;
         }
   
   Serial.print("Roll: ");
   Serial.println(roll);
   
   pitch = Serial1.read();
   if(pitch == 255)
   {
         Serial1.flush();
         break;
   }
   Serial.print("Pitch: ");
   Serial.println(pitch);
   
   yaw = Serial1.read();
   if(roll == 255)
   {
         Serial1.flush();
         break;
   }
   Serial.print("Yaw: ");
   Serial.println(yaw);
   if(yaw == 255)
   {
         Serial1.flush();
         break;
   }
         
   sign = Serial1.read();
   if(sign == 255)
   {
         Serial1.flush();
         break;
   }
   Serial.print("Sign: ");
   Serial.println(sign);
   Serial1.flush(); 
        }   
   //Serial.println(myArray[4]);
   
}

//void receiveEvent(int howMany)
//{
  //funct();
  //delay(5000);
  /*int roll = Wire.read();
  int pitch = Wire.read();
  int yaw = Wire.read();
  int sign = Wire.read();
  Serial.println("Roll: ");
  Serial.print(roll);
  Serial.println("Pitch: ");
  Serial.print(pitch);
  Serial.println("Yaw: ");
  Serial.print(yaw);
  Serial.println("Sign: ");
  Serial.print(sign);*/
  
//}

/*void funct()
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
}*/
