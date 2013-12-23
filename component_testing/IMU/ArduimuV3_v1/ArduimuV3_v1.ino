//===================================================================================================
//=================------================== ONLY FOR ARDUIMU V3!!===================================
//===================================================================================================
//This code will perform:
//   Accelerometer/Gyro Calibration
//   Magnetometer Calibration
//   And store calibration values to EEPROM

//And when compiled in run mode will:  
//  Retrieve calibration values from EEPROM and provide following:
//  Roll, Pitch, Yaw value
//  GPS value (if enabled)
//Good Luck! - Al Toma
//==================================================================================================
//===================================================================================================
//ArduImu V3 Board - In Arduino 1.0.1 compile as Duemilanove ATMEGA328 Board
//Best if you review below!
//See Read_Me_1st tab      - General Description
//See Board_Layout tab     - Hardware Description
//See How_To_Calibrate tab - Calibration Procedure
//See Board_Layout tab     - ArduImu V3 Hardware PinOuts
//See Attribution tab      - All those who made this possible!
//==================================================================================================


//===================================================================================================
//========================= Software Mode - Uncomment below and compile =============================
//===================================================================================================
//                        ****** MUST NOT ENABLE USE_GPS WHEN CALIBRATING!!! ******
// When Roll,Pitch & Yaw values look OK, then Re-Comment and Recompile - Calibration will be read from EEPROM
#define RUN_GYRO_ACCEL_CAL        //Run Accel-Gyro Calibration and save to EEPROM
#define RUN_MAGNETOMETER_CAL      //Run Magnetometer Calibration and save to EEPROM
//===================================================================================================
//#define USE_GPS              //Uncomment if using GPS Connected to Serial Port & Set Protocol Number
//#define GPS_PROTOCOL 5       //1 = NMEA  2 = EM406  3 = UBlox  4 = MediaTek  5 = MediaTek16  
//===================================================================================================

//============================= Yaw Correction - Comment if using GPS ===============================
#define USE_MAGNETOMETER_YAW_CORRECTION  //Use magnetometer to correct Yaw drift, otherwise GPS if available
//===================================================================================================
//=================================== Comma Delimited Output Format =================================
#define COMMA_DELIMITED_OUTPUT   //Output Comma Delimited Data, otherwise HappyKillMore Demo Format
//===================================================================================================


//===================================================================================================
//===================================================================================================
#include <avr/eeprom.h>      //Use ATMEGA328 EEPROM to Save/Read Calibrations
#include <AP_GPS.h>	     //Load this library from DIY Drones (ArduIMU 1.9.6)!  http://code.google.com/p/ardu-imu/downloads/list?can=2&q=		 
#include <FastSerial.h>	            
#include <Wire.h>

FastSerialPort0(Serial);     //Serial Port 

#ifdef USE_GPS               //If you have a GPS, Uncomment USE_GPS & Set GPS_PROTOCOL number above (NOT DURING CALIBRATION!!)
  #if   GPS_PROTOCOL == 1
    AP_GPS_NMEA    GPS(&Serial);
  #elif GPS_PROTOCOL == 2
    AP_GPS_406     GPS(&Serial);
  #elif GPS_PROTOCOL == 3
    AP_GPS_UBLOX   GPS(&Serial);
  #elif GPS_PROTOCOL == 4
    AP_GPS_MTK     GPS(&Serial);
  #elif GPS_PROTOCOL == 5
    AP_GPS_MTK16   GPS(&Serial);       //Tested only on this couldn't afford UBLOX!  ;)
  #endif
#endif
                                       //Pin 13 is Yellow LED, BUT it also the SCK connection to GyroAccel - Do not use!
#define SERIAL_MUX_PIN  7              //Pin 7 controls a MUX which selects Serial Receive from GPS or FTDI USB Chip  
#define RED_LED_PIN     5              //Red LED 
#define BLUE_LED_PIN    6              //Yellow LED
       
                                       //Note: There are 9 available analog/digital pins available!  See Board_Layout
                                       //You could use 3 digital input pins for switches to put into calibration and 
                                       //run modes for a standalone app.  Or use to output to control servos or input
                                       //from a RC receiver.
                                       
//========= Print Calibration Data - Set to True if want to see Cal values on StartUp ==============
boolean PRINT_CALIBRATION  = true;     //Print Accel-Gyro calibration on Start Up - Set true when in Calibration
//==================================================================================================

float intDelta;                        //Integration Delta Time for Loop & DCM = .02s
long timeNow;                          //Current Time
long timeLast;                         //Last Time
int loopCount;                         //Determines when GPS & Magnetometer is Read in main loop

float GRAVITY;                         //Set in GyroAccelInit to 4096 or 8192 depending on MPU6000 Version and used in DCM
                                       //It works with 4096!
float AccelRaw[3];                     //Raw Accel Values from Accelerometers
float GyroRaw[3];                      //Raw Gyro Values from Accelerometers
                                       //Accelerometer/Gyro Calibration Data - 6 values saved to EEPROM
float AccelRawOffset[3];               //Accel Calibration Array - Offsets
float GyroRawOffset[3];                //Gyro Calibration Array - Offsets

float MagHeading;                      //Magnetometer Heading
float MagHeading_X, MagHeading_Y;      //Used in DCM
float roll, pitch, yaw;                //Euler angles Roll, Pitch, Yaw

//======================================================================
//Wait for Enter Key to be Pressed for use during Calibrations
//If this does not work, close the compiler and retry!!! Sometimes Serial monitor hangs.
//======================================================================
void WaitForEnterKeyPressed()
{
  delay(100);
  Serial.flush();                      //Flush serial buffer just in case
  while (Serial.available() == 0);     //Wait for ENTER keypress 
}
//======================================================================
//============================ SetUp ===================================
//======================================================================
void setup()
{ 
  Serial.begin(38400, 128, 16);        //Init Serial port at 38400 baud
  digitalWrite(SERIAL_MUX_PIN,LOW);    //Select Mux to Receive Serial from FTDI 
  Serial.flush();
  Serial.print("\n***** ArduImuV3_v1 *****");
  
//======= Pin Definitions - see Board_Layout Tab for Detail =============
  pinMode(SERIAL_MUX_PIN, OUTPUT);        //Serial Mux Pin - SWITCHES SERIAL INPUT FROM GPS OR FTDI CHIP
  pinMode(RED_LED_PIN, OUTPUT);           //Red LED
  pinMode(BLUE_LED_PIN, OUTPUT);          //Blue LED
  
//============================== Initialization =========================
  Serial.print("\nInit Angular Rate Gyro/Acceleromter/Magnetometer");
  GyroAccelInit();                       //Gyro-Accel Init
  MagnetometerInit();                    //Magnetometer Init
  
  #ifdef USE_GPS                         //If you have a GPS, Uncomment USE_GPS 
    Serial.print("\nInit GPS - Configuration Commands:\n");
    delay(500);                          //Allow config commands from library to print
    digitalWrite(SERIAL_MUX_PIN,HIGH);   //Select Mux to Receive Serial from GPS and not FTDI 
    GPS.init();			         //GPS Init 
    delay(3000);                         //Need to Allow print above to complete before GPS init    
  #endif
 
 //==================== Start Gyro/Accel Calibration======================
  #ifdef RUN_GYRO_ACCEL_CAL
    Serial.print("\n\nCalibrate Gyro/Accel ......Keep IMU Flat & Hold Steady until Blue LED stops blinking!\nPress ENTER key to START");
    WaitForEnterKeyPressed();
    Serial.print("\nCalibrating...");
    
    CalibrateGyroAccel();               //Calibrate GyroAccel
    SaveGyroAccelCalibration();         //Save Gyro Accel Offset values
  #endif  
 //====================== End Gyro/Accel Calibration=======================

 //=================== Start Magnetometer XY Calibration ==================
  #ifdef RUN_MAGNETOMETER_CAL
    Serial.print("\n\n\nCalibrate Magnetometer XY Axis ......Keep IMU Flat & Rotate IMU SLOWLY 720 degrees until Blue LED stops blinking! or Min/Max values do not change!\nPress ENTER key to START Calibration");
    WaitForEnterKeyPressed();    
    
    CalibrateMagnetometer_XY();  
    SetMag_XY();
  //======================== End Magnetometer XY Calibration====================
 
 //====================== Start Magnetometer Z Calibration ====================
    Serial.print("\n\n\nCalibrate Magnetometer Z Axis......Rotate IMU on EDGE & Rotate SLOWLY 720 degrees until Blue LED stops blinking! or Min/Max values do not change!\nPress ENTER key to START Calibration");
    WaitForEnterKeyPressed();  
    
    CalibrateMagnetometer_Z();
    SetMag_Z();
    
    SaveMagnetometerCal();               //Save Magnetometer Cal Data
    SaveMagnetometerRawCal();            //Saved Magnetometer Raw Calibration Values
   #endif  
 //========================== End Magnetometer Z Calibration====================
  
 //======================= Load Calibrations from EEPROM =======================
  Serial.print("\n\nLoad Angular Rate Gyros/Accelerometers/Magnetometer Calibrations from EEPROM");
  LoadGyroAccelCalibration();            //Get Last Saved Gyro Accel Offset values
  LoadMagnetometer_XY_Cal();             //Get Last Saved Magnetometer Offset Values
  LoadMagnetometer_Z_Cal();              //Get Last Saved Magnetometer Span Equalization Values
  LoadMagnetometerRawCal();              //Get Last Saved Magnetometer Raw Calibration Values - not really needed!

  //============================= All Done - Ready! =============================
  Serial.println("\n\nReady!\n\n");      
  delay(10000);                          //LadhdiDah.....so can read calibrations values - shorten/delte if you want!    
  
  timeLast = millis();                   //Init last time in ms
}
//========================================================================
//Main Loop - Perform DCM Algorithm every 20ms
//Get GPS (if enabled) & Magnetometer data at lower rate - 100ms
//========================================================================
void loop()                            
{
  long deltaTime;
  
  timeNow = millis();                                       //Get current time in milliseconds
  deltaTime = timeNow - timeLast;                           //Get Elapsed time difference in milliseconds
  
  if ((deltaTime) >= 20)                                    //20ms delta time, Loop Update Rate = 50hz
  {                                                         
    intDelta = (float) deltaTime / 1000.0;                  //Real time of loop run. This should always be 0.02s
    if (intDelta > 1.0) intDelta = 0.0;                     //Error intDelta set to 0 so DCM stills works
    timeLast = timeNow;                                     //Save last time for next iteration
   
    ReadGyroRaw();                                          //Read Gyro Data
    ReadAccelRaw();                                         //Read Accel Data
    
    DCM_MatrixUpdate(intDelta);                             //Perform Direction Cosine Matrix Algorithm - pass integration delta time 
    DCM_Normalize();
    DCM_DriftCorrection();
    DCM_EulerAngles();                                      //Calculate Roll, Pitch, Yaw

    loopCount++;                                            //Increment loop counter for GPS & Magnetometer input 

    switch (loopCount)                                      //Count to determine how often to get GPS & Magnetometer data
    {                   
#ifdef USE_GPS                                              //If you have a GPS, Uncomment USE_GPS 
      case(0):
        GPS.update();                                       //Get GPS Data
        if (GPS.status()) digitalWrite(BLUE_LED_PIN,HIGH);  //Show GPS has Fix with Blue LED
        else              digitalWrite(BLUE_LED_PIN,LOW);   //Not really needed since GPS MTK shows Blue on lock too!
        break;
#endif
      case(3):
        MagnetometerReadRaw();                             //Read magnetometer raw data
        ApplyMagnetometerCalibration();                    //Correct raw magnetometer data
        MagnetometerHeading(roll, pitch);                  //Calculate heading from roll & pitch for DCM
        break;
      case(5):                                             //Reset case counter, will be incremented to zero before switch statement
        loopCount = -1;
                                                           //Print Out data comma delimited
        digitalWrite(RED_LED_PIN, HIGH);                   //Show its running - ON

#ifdef COMMA_DELIMITED_OUTPUT  
        //================================================================================================
        //================================ Comma Delimited Output ========================================
        //You can :
        //  View output on Serial Monitor on Arduino IDE
        //  Run Processing ArduIMU_V3_Cube app by Al Toma and display a 3D rotating cube 
        //  Send data to another Arduino for Auto Pilot or just log to SD card
        //  Connect Serial out to an X-Bee (miles away LOS) for telemetry output/logging
        //================================================================================================
        Serial.print(ToDeg(roll));  Serial.print(",");     //Roll, Pitch, Yaw Angles
        Serial.print(ToDeg(pitch)); Serial.print(",");
        Serial.print(ToDeg(yaw));  
       
  #ifdef USE_GPS                                             //If you have a GPS, Uncomment USE_GPS 
        if(GPS.new_data == 1)
        {
          GPS.new_data = 0;                                //Flag set by GPS
          Serial.print(",");                               //GPS Data
          Serial.print(GPS.time);               Serial.print(",");   
          Serial.print(GPS.latitude);           Serial.print(",");
          Serial.print(GPS.longitude);          Serial.print(",");
          Serial.print(GPS.altitude/100);       Serial.print(",");
          Serial.print(GPS.ground_course/100);  Serial.print(",");
          Serial.print(GPS.ground_speed/100);   Serial.print(",");
          Serial.print((int)GPS.fix);           Serial.print(","); 
          Serial.print((int)GPS.num_sats);     
        }
  #endif
        Serial.println ("");                //Final LineFeed
        //=================================== End Comma Delimited ========================================
#else
        //================================================================================================
        //===== ArduIMU_Test v1.1.19 by HappyKillmore Cube/Plane Demo Output - very slow response! =======
        // Cube works so-so
        // Plane very sluggish
        // Reads GPS.fix (lock) data wrong - forcing to 0 to make work
        //================================================================================================
      
 	Serial.print("!!!VER:");
	Serial.print("1.0");   
	Serial.print(",");
        Serial.print("RLL:");
        Serial.print(ToDeg(roll));
        Serial.print(",PCH:");
        Serial.print(ToDeg(pitch));
        Serial.print(",YAW:");
        Serial.print(ToDeg(yaw));
 	Serial.print(",IMUH:");
	Serial.print(0xff);                                    //dummy IMU Health data
       
  #ifdef USE_GPS                                               //If you have a GPS, Uncomment USE_GPS 
        if(GPS.new_data == 1)
        {
          GPS.new_data=0;
          Serial.print(",LAT:");
          Serial.print(GPS.latitude);
          Serial.print(",LON:");
          Serial.print(GPS.longitude);
          Serial.print(",ALT:");
          Serial.print(GPS.altitude/100);                       
          Serial.print(",COG:");
          Serial.print(GPS.ground_course/100);	   
          Serial.print(",SOG:");
          Serial.print(GPS.ground_speed/100);
          Serial.print(",FIX:");
          Serial.print(0);         //Force to lock - v1.1.19 not reading correctly
        //Serial.print((int)GPS.fix); 
          Serial.print(",SAT:"); 
          Serial.print((int)GPS.num_sats);
 	  Serial.print(",TOW:");
	  Serial.print(GPS.time);
       }
  #endif
	Serial.print("***");    
        Serial.println ("");                //Final LineFeed
#endif
        //============================== End HappyKillmore ========================================

        
        digitalWrite(RED_LED_PIN, LOW);     //Show it's running - OFF
        break;
    }
  }
}

