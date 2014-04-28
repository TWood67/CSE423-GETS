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
byte error;
byte command;
int east = 0;
int west = 0;
int north = 0;
int south = 0;
int n_base = 70;
int s_base = 70;
int e_base = 70;
int w_base = 70;
int val = 0;

bool isFlying = false;
bool isLanding = false;
bool isDead = false;
bool discard = false;

//===============================================================================>
// Name: setup
//
// Description: Arms the motors and performs various functions
//===============================================================================>
void setup() {
  
  
   // assign a base value
   // TODO: Do this for other values
   starboardVal = 0;
 
   pinMode(22, INPUT);
  pinMode(24, INPUT);


 
   // assign pin to variables
   // TODO: Do this for all pins
   starboardPin = 53;
   arrayptr = myArray;
   
   delay(6000);
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

void set_ns_axis(byte offset, byte sign){

        
        if((sign & 0x02) == 0x02){
                offset = -offset;
        }

        north = n_base + (offset/2);
	south = s_base - (offset/2);
	if((offset % 2) != 0){
		if(offset > 0){
			north++;
		}
		else{
			south++;
		}
	}

    //Serial.print("North:");
    //Serial.println(north);
    //Serial.print("South: ");
    //Serial.println(south);

}


void set_ew_axis(byte offset, byte sign){
  	
        //int intRoll = (int) offset;
        //Serial.print("offset:");
        //Serial.println(offset);
        
	if((sign & 0x01) == 0x01){
                //offset = -offset;
           //Serial.print("Negoffset: ");
           //Serial.println(offset);
                
           east = e_base - (offset/2);
	   west = w_base + (offset/2);
          
            if((offset % 2) != 0){
	      west++;	
	    }
        }
        
        else{
          east = e_base + (offset/2);
	  west = w_base - (offset/2);
	
          if((offset % 2) != 0){
		  east++;
	  }
        }
        

      //Serial.print("East:");
      //Serial.println(east);
      //Serial.print("West: ");
      //Serial.println(west);
}

void loop() {

     
      while(Serial1.available() == 0);
       
      
         
         while(Serial1.available() > 6)
         { 
             if(discard == true)
             {
                 discard = false;
                 command = Serial1.read();
                  while(command != B11111111)
                  {
                    command = Serial1.read();
                  }
             }
             else
             {
              command = Serial1.read();
              while(command == B11111111)
              {
                command = Serial1.read();
              }
             }
   
             //Serial.println(" END TRANSMITTING"); 
               roll = Serial1.read();
               pitch = Serial1.read();
               yaw = Serial1.read();
               sign = Serial1.read();

           //int unread2 = Serial1.available();
           //Serial.print("unread2: ");
            //Serial.println(unread2);
       
         
               if(roll == 255 || pitch == 255 || yaw == 255 || sign >2 || command > 5)
               {
                 
                 Serial1.flush();
                 break;
                 discard = true;
                 //Serial1.flush();
                 //Serial.println("BREAKIN");
                 
               }
               else
               { 
                 Serial.print("Command: ");
                 Serial.println(command);
                 Serial.print("Roll: ");
                 Serial.println(roll);
                 Serial.print("Pitch: ");
                 Serial.println(pitch);
                 Serial.print("Yaw: ");
                 Serial.println(yaw);
                 Serial.print("Sign: ");
                 Serial.println(sign);
               
                 if(command == B00000001)
                 {
                   isDead = false;
                 set_ew_axis(roll, sign);
	         //set_ns_axis(pitch, sign);
                 //Serial.println("TRANSMITTING");
                   Wire1.beginTransmission(4);
                   Wire1.write(east);
                   Wire1.write(west);
                   Wire1.endTransmission();
                  
                 }
                 else if(command == B00000010 && !isDead)
                 {
                   isDead = true;
                   set_ew_axis(roll, sign);
                   Wire1.beginTransmission(4);
                   Wire1.write(east - 20);
                   Wire1.write(west - 20);
                   Wire1.endTransmission();
                   delay(50);
                   set_ew_axis(roll, sign);
                   Wire1.beginTransmission(4);
                   Wire1.write(east - 30);
                   Wire1.write(west - 30);
                   Wire1.endTransmission();
                   delay(50);
                   Wire1.beginTransmission(4);
                   Wire1.write(0);
                   Wire1.write(0);
                   Wire1.endTransmission();
                 }
                 else if(command == B00000000 || command == B00000100 || command == B00000011)
                 {
                   Wire1.beginTransmission(4);
                   Wire1.write(0);
                   Wire1.write(0);
                   Wire1.endTransmission();
                 }
                  delay(50);
	       //setSpeed(east, west, south, north);*/

               /*for(int i = 0; i<=140; i++)
                {
                   Serial.println("TRANSMITTING");
                   Wire1.beginTransmission(4);
                   Wire1.write(i);
                   Wire1.endTransmission();
                   delay(50);
                }
               Serial.println(" END TRANSMITTING");
               */  
   
                             
               }
              
         }
       }



