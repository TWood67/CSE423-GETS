/*=================================== ONLY FOR ARDUIMU V3!!===================================
These libraries are needed:
AP_COMMON
AP_Math
AP_GPS	 	 
FastSerial

Load these libraries into yours from DIY Drones (ArduIMU 1.9.6)!  http://code.google.com/p/ardu-imu/downloads/list?can=2&q=

Use Arduino 1.0.1 Compiler - it probably will work with later versions but not tested!
Select Board Type - Duemilanove ATMEGA328 Board
Select your Port #

Open file ArduimuV3_v10

Under the Magnetometer Tab you will see the following 
which is the Local magnetic declination (in degrees).

#define MAGNETIC_DECLINATION 0        //Corrects magnetic bearing to true north

You can go to this web site to find your local declination and enter the value but this is 
not critical and can leave it at 0 for now.
http://www.ngdc.noaa.gov/geomag-web/

==============================================================================================

ARDUIMU V3 - CALIBRATION PROCEDURE - Select the ArduimuV3_v10 Tab

  Step #1 - Uncomment RUN_GYRO_ACCEL_CAL & RUN_MAGNETOMETER_CAL & USE_MAGNETOMETER_YAW_CORRECTION
            Comment USE_GPS & GPS_PROTOCOL as shown below
-----------------------------------------------------------------------------------------------------------------            
#define RUN_GYRO_ACCEL_CAL               //Run Accel-Gyro Calibration and save to EEPROM
#define RUN_MAGNETOMETER_CAL             //Run Magnetometer Calibration and save to EEPROM
//#define USE_GPS                        //Uncomment if using GPS Connected to Serial Port & Set Protocol Number
//#define GPS_PROTOCOL 5                 //1 = NMEA  2 = EM406  3 = UBlox  4 = MediaTek  5 = MediaTek16  
#define USE_MAGNETOMETER_YAW_CORRECTION  //Use magnetometer to correct Yaw drift
-----------------------------------------------------------------------------------------------------------------            


==============================================================================================
  NOTE: If you are too slow opening up the Serial Monitor and nothing shows, press the RESET button on the IMU!!!
        Serial Monitor should be in NewLine mode and 38400 baud!!!
  
  Step #2 - Compile, Open Tools->Serial Monitor and Press Reset Button on ArduImu V3 and you will see:
             
  Calibrate Gyro/Accel ......Keep IMU Flat & Hold Steady until Blue LED stops blinking!
  Press ENTER key and Blue LED will blink for quite awhile
  
  Next you will see:
  
  Calibrate Magnetometer XY Axis ......Keep IMU Flat & Rotate IMU SLOWLY 720 degrees until Blue LED stops blinking! or Min/Max values do not change!
  
  Press ENTER key and you will see Blue LED blink and Min-Max values fill the screen.  Rotate about 90 degrees per second in one direction and back
  again in the other.  When no more blinking occurs, press Enter key.

  Next you will see:
  
  Calibrate Magnetometer Z Axis......Rotate IMU on EDGE & Rotate SLOWLY 720 degrees until Blue LED stops blinking! or Min/Max values do not change!
  
  Press ENTER key and again you will see Blue LED blink and Min-Max values fill the screen.  Rotate about 90 degrees per second in one direction and back
  again in the other.  When no more blinking occurs, press Enter key.  Note: the IMU should be placed on the edge w/ signals Grd, 3.3V, SDA, SCL, etc.
  
  The calibration will be written to the EEPROM on the ATMEGA328 and will be displayed on the screen for a short while, the comma delimited 
  Roll, Pitch & Yaw data will scroll up on the screen after 10 seconds.
  
  Check the data by grasping the FTDI 6 pin connector and twist (roll) the board left and right.  You should see values from -90 to 90 degrees.
  Tilt the board forward and back and you should see pitch values change -90 to 90 degrees (have to hold real steady and it seems overly senstive 
  in this axis).  Now get a box with 90 degree corners and place one edge of the IMU along side the edge and rotate both until the yaw value reaches
  zero.  Now place the IMU on a side of the box perpendicular to the initial placement.  If calibration went ok, you should see about 90 degrees plus 
  or minus couple degrees.  Place the IMU on the other perpendicular side and you should see about -90 degrees.  It's usually plus or minus 2 degs.
  
  If the readings don't look too good,  retry the calibration procedure.  Good luck!!!
  If they still don't look good, give up and grab yourself a cold one!!  Life's too short!
==============================================================================================
 
  
  Step #2a - If NOT using GPS:
             Comment RUN_GYRO_ACCEL_CAL & RUN_MAGNETOMETER_CAL as shown below
-----------------------------------------------------------------------------------------------------------------            
//#define RUN_GYRO_ACCEL_CAL               //Run Accel-Gyro Calibration and save to EEPROM
//#define RUN_MAGNETOMETER_CAL             //Run Magnetometer Calibration and save to EEPROM
//#define USE_GPS                          //Uncomment if using GPS Connected to Serial Port & Set Protocol Number
//#define GPS_PROTOCOL 5                   //1 = NMEA  2 = EM406  3 = UBlox  4 = MediaTek  5 = MediaTek16  
#define USE_MAGNETOMETER_YAW_CORRECTION    //Use magnetometer to correct Yaw drift
-----------------------------------------------------------------------------------------------------------------            
  
Recompile and upload.  From now, it will load the calibration data from EEPROM and spew out roll, pitch & yaw. 

Blinking Red LED indicates it is outputting data.
  
   
==============================================================================================
  Step #2b - If USING GPS:
             Plug your GPS unit into board 
             Comment RUN_GYRO_ACCEL_CAL & RUN_MAGNETOMETER_CAL 
             Uncomment USE_GPS
             Change the GPS_PROTOCOL to your GPS unit (I have only tested on MediaTek16!)
             You can Comment USE_MAGNETOMETER_YAW_CORRECTION which will then use the GPS for
             Yaw correction, but I have not verified this at this time.
-----------------------------------------------------------------------------------------------------------------            
//#define RUN_GYRO_ACCEL_CAL               //Run Accel-Gyro Calibration and save to EEPROM
//#define RUN_MAGNETOMETER_CAL             //Run Magnetometer Calibration and save to EEPROM
#define USE_GPS                            //Uncomment if using GPS Connected to Serial Port & Set Protocol Number
#define GPS_PROTOCOL 5                     //1 = NMEA  2 = EM406  3 = UBlox  4 = MediaTek  5 = MediaTek16  
#define USE_MAGNETOMETER_YAW_CORRECTION    //Use magnetometer to correct Yaw drift
-----------------------------------------------------------------------------------------------------------------            

Again recompile and upload.  From now, it will load the calibration data from EEPROM and spew out roll, pitch & yaw
as well as the GPS data. 

Blinking Red LED indicates it is outputting data.
Solid Blue LED Indicates you have GPS lock.

That's all folks!  Hope it worked for you!
============================================================================================*/
