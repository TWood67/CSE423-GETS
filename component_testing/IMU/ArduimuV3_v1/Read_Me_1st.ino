/*
Requires that you compile/load this application two times.  The first time you will comment
& uncomment defines to put you in the calibration mode.  You will perform the calibration and 
then switch the defines for running mode and recompile/load again.  Then the IMU will spew out
data.

This application implements the Direction Cosine Matrix - DCM in order to provide a stable
Roll, Pitch & Yaw orientation using the following tri-axis sensors: Accelerometer, Angular
Gyro and Magnetometer.  The first thing that MUST be done is going through the 3 calibration
procedures.  The 1st calibrates the angular rate gyro and requires that you just hold the
board steady on a flat surface.  The 2nd & 3rd are for calibrating the magnetometers.  In
the 1st it requires you to rotate the board on a flat surface at about a 90 degrees per second
rate for about 720 degrees. The 3rd requires you to put the board on edge and perform the same
rotation again.  As each calibration is completed, the values are stored to the EEPROM on the
ATMEGA328.  Note: You CANNOT calibrate with the GPS_USE uncommented!  After you recompile the 
program with the calibration defines commented out it will read and apply the calibrations.  
See the How_To tab for the detailed calibration procedures.

After you have completed the above calibration and have good roll, pitch & yaw data, you can
enable the GPS and select the GPS type and recompile.  Note: I have only tested on the MTK16 
GPS unit.  Now you should see GPS data as well as roll, pitch & yaw.
============================================================================================*/
