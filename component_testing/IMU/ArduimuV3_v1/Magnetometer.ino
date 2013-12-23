/*
HMC5883L 3-Axis Magnetometer

http://dlnmh9ip6v2uc.cloudfront.net/datasheets/Sensors/Magneto/HMC5883L-FDS.pdf

I2C 1 Wire Interface
On-board processor to read all 3 magnetometer axis continuously
Reading data at 75hz, averaging 8 samples
Reads 6 bytes - 2 bytes for each axis

CHip has 4.7 kΩ pull-up resistors on the SDA line 
and 2.2K resistor on the SCL line

Arduino Pin    HMC5883L Pin
D3 (INT1)      DRDY   Not Used???
A4 SDA         SDA
A5 SCL         SCL
*/

#define MAGNETIC_DECLINATION 0        //Corrects magnetic bearing to true north
#include <math.h>
#include <Wire.h>

//======================== HMC5883L Registers ===========================
#define COMPASS_ADDRESS        0x1E   //HMC5883L Device Address
#define CONFIGREGA             0x00  
#define MODEREGISTER           0x02
#define CONTINUOUSCONVERSION   0x00   //Mode Register valid modes
#define SAMPLEAVERAGING_8      0x03
#define DATAOUTPUTRATE_75HZ    0x06
#define NORMALOPERATION        0x10  //ConfigRegA valid measurement configuration bits

//#define ConfigRegB           0x01
//#define DataOutputXMSB       0x03
//#define DataOutputXLSB       0x04
//#define DataOutputZMSB       0x05
//#define DataOutputZLSB       0x06
//#define DataOutputYMSB       0x07
//#define DataOutputYLSB       0x08
//#define StatusRegister       0x09
//#define IDRegisterA          0x0A
//#define IDRegisterB          0x0B
//#define IDRegisterC          0x0C
//#define magGain              0x20   //Default gain value
//#define SingleConversion     0x01
//#define SampleAveraging_1    0x00   //ConfigRegA valid sample averaging
//#define SampleAveraging_2    0x01
//#define SampleAveraging_4    0x02
//#define DataOutputRate_0_75HZ 0x00  //ConfigRegA valid data output rates
//#define DataOutputRate_1_5HZ  0x01
//#define DataOutputRate_3HZ    0x02
//#define DataOutputRate_7_5HZ  0x03
//#define DataOutputRate_15HZ   0x04
//#define DataOutputRate_30HZ   0x05
//#define PositiveBiasConfig    0x11
//#define NegativeBiasConfig    0x12
//========================================================================
//Magnetometer Initialiazation
//========================================================================
bool MagnetometerInit()
{
  uint8_t aux_byte;

  Wire.begin(); delay(10);

  Wire.beginTransmission(COMPASS_ADDRESS);
  Wire.write((uint8_t)CONFIGREGA);
  
  aux_byte = (SAMPLEAVERAGING_8 << 5 | DATAOUTPUTRATE_75HZ << 2 | NORMALOPERATION);
  Wire.write(aux_byte);
  
  Wire.endTransmission(); delay(50);

  Wire.beginTransmission(COMPASS_ADDRESS);
  
  Wire.write((uint8_t) MODEREGISTER);
  Wire.write((uint8_t) CONTINUOUSCONVERSION);     //Set continuous mode (default to 10Hz)
  
  Wire.endTransmission(); delay(50);
  
  return(1);
}
//========================================================================
//Read Magnetometer Mag_X, Mag_Y & Mag_Z
//========================================================================
void MagnetometerReadRaw()                               //Read Sensor data in chip axis
{
  int i = 0;
  byte buff[6];

  Wire.beginTransmission(COMPASS_ADDRESS);
  Wire.write(0x03);                                   //Sends address to read from
  Wire.endTransmission();                             //End transmission
                                                      //Wire.beginTransmission(COMPASS_ADDRESS);
  Wire.requestFrom(COMPASS_ADDRESS, 6);               //Request 6 bytes from device
  while(Wire.available())
  {
    buff[i] = Wire.read();                            //Read byte
    i++;
  }
  Wire.endTransmission();                             //End transmission

  if (i == 6)                                         //All bytes received?
  {                                                   //MSB byte first, then LSB
    Mag_X = ((((int)buff[0]) << 8) | buff[1]) * -1;   //X axis
    Mag_Y = ((((int)buff[4]) << 8) | buff[5]) *  1;   //Y axis
    Mag_Z = ((((int)buff[2]) << 8) | buff[3]) * -1;   //Z axis
  }
}
//========================================================================
//Correct Raw Data with Calibration Data
//========================================================================
void ApplyMagnetometerCalibration()
{
  Mag_X = Mag_X - MagOffset[0];
  Mag_Y = MagSpanEq[1] * (Mag_Y - MagOffset[1]);
  Mag_Z = MagSpanEq[2] * (Mag_Z - MagOffset[2]);
}
//========================================================================
//Get Heading Magnetometer Heading Data
//========================================================================
void MagnetometerHeading(float roll, float pitch)
{
  float head_X;
  float head_Y;
  float cos_roll;
  float sin_roll;
  float cos_pitch;
  float sin_pitch;
  
  cos_roll  = cos(roll);
  sin_roll  = sin(roll);
  cos_pitch = cos(pitch);
  sin_pitch = sin(pitch);
                                                //Tilt compensated Magnetic field X component:
  head_X = (Mag_X * cos_pitch) + (Mag_Y * sin_roll * sin_pitch) + (Mag_Z * cos_roll * sin_pitch);
                                                //Tilt compensated Magnetic field Y component:
  head_Y = (Mag_Y * cos_roll) - (Mag_Z * sin_roll);
                                                //Magnetic Heading
  MagHeading = atan2(-head_Y, head_X);
                                                //Declination correction 
  if( MAGNETIC_DECLINATION != 0 ) 
  {
     MagHeading = MagHeading + ToRad(MAGNETIC_DECLINATION);
     if      (MagHeading >  M_PI) MagHeading -= (2.0 * M_PI);  //Angle normalization (-180 deg, 180 deg)
     else if (MagHeading < -M_PI) MagHeading += (2.0 * M_PI);  //M_PI from math.h
  }
  
  MagHeading_X = cos(MagHeading);                             //Used in DCM!
  MagHeading_Y = sin(MagHeading);
}

