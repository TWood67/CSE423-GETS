//=======================================================================================
//====================== Read and Write Calibrations to EEPROM ==========================
//=======================================================================================
//If in either Calibration Modes, calibration data will be written to EEPROM on Arduino
//If in Run Mode, calibration data will be read from EEPROM
//
//     EEPROM memory locations for calibration data
// 0-1     Unused
// 2-3     GyroRawOffset[0]    Gyro Offset X
// 4-5     GyroRawOffset[1]    Gyro Offset Y
// 6-7     GyroRawOffset[2]    Gyro Offset Z
// 8-9     AcccelRawOffset[0]  Accel Offset X
// 10-11   AcccelRawOffset[1]  Accel Offset Y
// 12-13   AcccelRawOffset[2]  Accel Offset Z	 
// 14-15   MagOffset[0]        Magnetometer Offset X
// 16-17   MagOffset[1]        Magnetometer Offset Y
// 18-19   MagOffset[2]        Magnetometer Offset Z
// 20-21   MagSpanEq[0]        Magnetometer Span Equalizaion X
// 22-23   MagSpanEq[1]        Magnetometer Span Equalizaion Y
// 24-25   MagSpanEq[2]        Magnetometer Span Equalizaion Z
//=======================================================================================
#define GYRO_EEPROM         0          //Offsets in bytes into EEPROM Memory to Save/Load Calibration Values
#define ACCEL_EEPROM        6
#define MAG_OFFSET_EEPROM  12
#define MAG_SPAN_EEPROM    18
#define MAG_RAW_EEPROM     24
                                  
int   Mag_X, Mag_Y, Mag_Z;             //Magnetometer Raw Values read from Magnetometer

int   MagOffset[3];                    //Magnetometer Calibration Offsets
float MagSpanEq[3];                    //Magnetometer Calibration Equalization
                                       
int   Mag_X_Min, Mag_X_Max;            //Magnetometer Values used during Calibration
int   Mag_Y_Min, Mag_Y_Max;            //Min-Max Values for 3 Axis
int   Mag_Z_Min, Mag_Z_Max;

//================================================================================================
// Load Calibrations
//================================================================================================
//================================================================================================
//Load Accel & Gyro Offset Calibrations from EEPROM 
//================================================================================================
void LoadGyroAccelCalibration()
{
  int16_t store;

  if (PRINT_CALIBRATION) Serial.print("\nLoad Gyro Offsets:\t\t\t");

  for(int i=0; i<3; i++)     
  {      
    eeprom_busy_wait();        
    store = eeprom_read_word((uint16_t *) (GYRO_EEPROM + i * 2));
    GyroRawOffset[i] = store;
    if (PRINT_CALIBRATION)
    {
      Serial.print("GyroRawOffset[");
      Serial.print(i);
      Serial.print("] = ");
      Serial.print(store);
      Serial.print("\t");
    }   
  }
  
  if (PRINT_CALIBRATION) Serial.print("\nLoad Accel Offsets:\t\t\t");

  for(int i=0; i<3; i++)     
  {      
    eeprom_busy_wait();        
    store = eeprom_read_word((uint16_t *) (ACCEL_EEPROM + i * 2));
    AccelRawOffset[i] = store;
    
    if (PRINT_CALIBRATION)
    {
      Serial.print("AccelRawOffset[");
      Serial.print(i);
      Serial.print("] = ");
      Serial.print(store);
      Serial.print("\t");
    }
  }
}
//================================================================================================
// Load Magnetometer Offset Calibration
//================================================================================================
void LoadMagnetometer_XY_Cal()
{
  if (PRINT_CALIBRATION) Serial.print("\nLoad Magnetometer Offsets:\t\t");
  
  for(int i=0; i<3; i++)     
  {      
    eeprom_busy_wait();        
    MagOffset[i] = eeprom_read_word((uint16_t *) (MAG_OFFSET_EEPROM + i * 2));

    if (PRINT_CALIBRATION)
    {
      Serial.print("MagOffset[");
      Serial.print(i);
      Serial.print("] = ");
      Serial.print(MagOffset[i]);
      Serial.print("\t");
    }
  }
}
//================================================================================================
// Load Magnetometer Span Equalization Calibration
//================================================================================================
void LoadMagnetometer_Z_Cal()
{
  if (PRINT_CALIBRATION) Serial.print("\nLoad Magnetometer Equalizations:\t");

  for(int i=0; i<3; i++)             //Get magnetometer scale equalization 
  {
    eeprom_busy_wait();
    MagSpanEq[i] = float(eeprom_read_word((uint16_t *) (MAG_SPAN_EEPROM + i * 2))) / 10000.f;
    
    if (PRINT_CALIBRATION)
    {
      Serial.print("MagSpanEq[");
      Serial.print(i);
      Serial.print("] = ");
      Serial.print(MagSpanEq[i]);
      Serial.print("\t");
    }
  }
}
//================================================================================================
// Load Magnetometer Raw Calibration
//================================================================================================
void LoadMagnetometerRawCal()
{
  if (PRINT_CALIBRATION) Serial.print("\nLoad Magnetometer Raw Calibration:\n");
  
  eeprom_busy_wait();        
  Mag_X_Min = eeprom_read_word((uint16_t *) (MAG_RAW_EEPROM + 0 * 2));
  eeprom_busy_wait();        
  Mag_X_Max = eeprom_read_word((uint16_t *) (MAG_RAW_EEPROM + 1 * 2));
  eeprom_busy_wait();        
  Mag_Y_Min = eeprom_read_word((uint16_t *) (MAG_RAW_EEPROM + 2 * 2));
  eeprom_busy_wait();        
  Mag_Y_Max = eeprom_read_word((uint16_t *) (MAG_RAW_EEPROM + 3 * 2));
  eeprom_busy_wait();        
  Mag_Z_Min = eeprom_read_word((uint16_t *) (MAG_RAW_EEPROM + 4 * 2));
  eeprom_busy_wait();        
  Mag_Z_Max = eeprom_read_word((uint16_t *) (MAG_RAW_EEPROM + 5 * 2));

  if (PRINT_CALIBRATION)
  {
    Serial.print("\t\t\t\t\t");
    Serial.print("Mag_X_Min = "); Serial.print(Mag_X_Min); Serial.print("\t");
    Serial.print("Mag_X_Max = "); Serial.print(Mag_X_Max); Serial.print("\n");
    Serial.print("\t\t\t\t\t"); 
    Serial.print("Mag_Y_Min = "); Serial.print(Mag_Y_Min); Serial.print("\t"); 
    Serial.print("Mag_Y_Max = "); Serial.print(Mag_Y_Max); Serial.print("\n");
    Serial.print("\t\t\t\t\t"); 
    Serial.print("Mag_Z_Min = "); Serial.print(Mag_Z_Min); Serial.print("\t");
    Serial.print("Mag_Z_Max = "); Serial.print(Mag_Z_Max); Serial.print("\n");
  }
}
//================================================================================================
// Perform Calibrations
//================================================================================================
//================================================================================================
//Calibrate Gyro & Accelerometer
//================================================================================================
void CalibrateGyroAccel(void)          //MPU6000 Calibration - just getting Accel & Gyro Offsets
{
  ReadGyroRaw();                       //Read one Accel & Gyro Raw Data
  ReadAccelRaw();

  for(int i=0; i<3; i++)
  {
    GyroRawOffset[i]  = GyroRaw[i];   //Store reading into Offset array
    AccelRawOffset[i] = AccelRaw[i];
  }
  
  for (int i=0; i<400; i++)           //Read it many times to get an averaged RawOffset[] values
  {
    digitalWrite(BLUE_LED_PIN, HIGH); delay(30);
    
    ReadGyroRaw();
    ReadAccelRaw();
    
    for(int i=0; i<3; i++)            //Average each reading into accumulated RawOffset[] values
    {
      GyroRawOffset[i]  = GyroRawOffset[i]  * 0.8 + GyroRaw[i]  * 0.2;
      AccelRawOffset[i] = AccelRawOffset[i] * 0.8 + AccelRaw[i] * 0.2;
    }
    digitalWrite(BLUE_LED_PIN, LOW); delay(30);
  }
  
  AccelRawOffset[2] = AccelRawOffset[2] - GRAVITY;  //Z Accel orientation is reversed - flip it
  
}
//================================================================================================
//Save the Largest Magnetometer Z Value as it is Held on EDGE & Rotated Horizontally
//Must Rotate SLOWLY 720 degrees.  When no more values print out, its done.
//================================================================================================
void CalibrateMagnetometer_Z()
{
  int i = 0;
  
  ClearMag_Z();
    
  Serial.flush();
  while(1)
  {
    MagnetometerReadRaw();                     //Read magnetometer raw data
      
    if (Mag_Z > Mag_Z_Max || Mag_Z < Mag_Z_Min)
    {
      digitalWrite(BLUE_LED_PIN, HIGH);  //Show its running
      delay(25);
      digitalWrite(BLUE_LED_PIN, LOW);
      i++;
    }
  
    if (Mag_Z > Mag_Z_Max) {Mag_Z_Max = Mag_Z; PrintMag_Z_MinMax(i);}  
    if (Mag_Z < Mag_Z_Min) {Mag_Z_Min = Mag_Z; PrintMag_Z_MinMax(i);}
      
    if (Serial.available()) break;             //Exit on ENTER keypress 
  }
}
//================================================================================================
//Save the Min/Max Magnetometer XY Value as it is Held Flat & Rotated Horizontally
//Must Rotate SLOWLY 720 degrees.  When no more values print out, its done.
//================================================================================================
void CalibrateMagnetometer_XY()
{
  int i;
  
  ClearMag_XY();
    
  Serial.flush();
  while(1)
  {
    MagnetometerReadRaw();                     //Read magnetometer raw data
    if (Mag_X > Mag_X_Max || Mag_X < Mag_X_Min || Mag_Y > Mag_Y_Max || Mag_Y < Mag_Y_Min)
    {
      digitalWrite(BLUE_LED_PIN, HIGH);  //Show its running
      delay(25);
      digitalWrite(BLUE_LED_PIN, LOW);
      i++;
    }

    if (Mag_X > Mag_X_Max) {Mag_X_Max = Mag_X; PrintMag_X_MinMax(i);}
    if (Mag_X < Mag_X_Min) {Mag_X_Min = Mag_X; PrintMag_X_MinMax(i);}
    if (Mag_Y > Mag_Y_Max) {Mag_Y_Max = Mag_Y; PrintMag_Y_MinMax(i);}
    if (Mag_Y < Mag_Y_Min) {Mag_Y_Min = Mag_Y; PrintMag_Y_MinMax(i);}
    if (Serial.available()) break;             //Exit on any keypress 
  }
}
//================================================================================================
//Print out Magnetometer Min/Max X Values
//================================================================================================
void PrintMag_X_MinMax(int i)
{
  if (PRINT_CALIBRATION)
  {
    Serial.print(i); 
    Serial.print(": X (min:max): ");
    Serial.print(Mag_X_Min); 
    Serial.print(" : "); 
    Serial.print(Mag_X_Max);
    Serial.println("  Press ENTER key when No Change");
  }
}
//================================================================================================
//Print out Magnetometer Min/Max Y Values
//================================================================================================
void PrintMag_Y_MinMax(int i)
{
  if (PRINT_CALIBRATION)
  {
    Serial.print(i); 
    Serial.print(": Y (min:max): ");
    Serial.print(Mag_Y_Min); 
    Serial.print(" : "); 
    Serial.print(Mag_Y_Max);
    Serial.println("  Press ENTER key when No Change");
  }
}
//================================================================================================
//Print out Magnetomer Min/Max Z Values
//================================================================================================
void PrintMag_Z_MinMax(int i)
{
  if (PRINT_CALIBRATION)
  {
    Serial.print(i); 
    Serial.print(": Z (min:max): ");
    Serial.print(Mag_Z_Min); 
    Serial.print(" : "); 
    Serial.print(Mag_Z_Max);
    Serial.println("  Press ENTER key when No Change");
  }
}
//================================================================================================
//Save Values after Calibrations
//================================================================================================
//================================================================================================
//Save Accel & Gyro Offset Calibrations GyroRawOffset[] & AccelRawOffset[] to EEPROM
//================================================================================================
void SaveGyroAccelCalibration()
{
  int16_t store;

  for(int i=0; i<3; i++)
  {
    store = round(GyroRawOffset[i]);
    eeprom_busy_wait();
    eeprom_write_word((uint16_t *) (GYRO_EEPROM + i * 2), store);	
  
    store = round(AccelRawOffset[i]);
    eeprom_busy_wait();
    eeprom_write_word((uint16_t *) (ACCEL_EEPROM + i * 2), store);	
  }
}
//================================================================================================
//Save Magnetometer Calibration to EEPROM
//================================================================================================
void SaveMagnetometerCal()
{
  for(int i=0; i<3; i++)
  {    
    eeprom_busy_wait();
    eeprom_write_word((uint16_t *) (MAG_OFFSET_EEPROM + i * 2), MagOffset[i]);

    eeprom_busy_wait();
    eeprom_write_word((uint16_t *) (MAG_SPAN_EEPROM + i * 2), MagSpanEq[i] * 10000);
  }
}
//================================================================================================
//Save Magnetometer Raw Calibration to EEPROM
//================================================================================================
void SaveMagnetometerRawCal()
{
  eeprom_busy_wait();
  eeprom_write_word((uint16_t *) (MAG_RAW_EEPROM + 0), Mag_X_Min);
  eeprom_busy_wait();
  eeprom_write_word((uint16_t *) (MAG_RAW_EEPROM + 2), Mag_X_Max);
  eeprom_busy_wait();
  eeprom_write_word((uint16_t *) (MAG_RAW_EEPROM + 4), Mag_Y_Min);
  eeprom_busy_wait();
  eeprom_write_word((uint16_t *) (MAG_RAW_EEPROM + 6), Mag_Y_Max);
  eeprom_busy_wait();
  eeprom_write_word((uint16_t *) (MAG_RAW_EEPROM + 8), Mag_Z_Min);
  eeprom_busy_wait();
  eeprom_write_word((uint16_t *) (MAG_RAW_EEPROM + 10), Mag_Z_Max);

}
//================================================================================================
//Set MagOffset[0] & MagOffset[1] 
//================================================================================================
void SetMag_XY()
{
  MagOffset[0] = (Mag_X_Min + Mag_X_Max) / 2;
  MagOffset[1] = (Mag_Y_Min + Mag_Y_Max) / 2;
}
//================================================================================================
//Set MagSpanEq[] Array and MagOffset[2]
//================================================================================================
void SetMag_Z()
{
  MagSpanEq[0] = 1;
  MagSpanEq[1] = float(Mag_X_Max - Mag_X_Min) / float(Mag_Y_Max - Mag_Y_Min);
  MagSpanEq[2] = float(Mag_X_Max - Mag_X_Min) / float(Mag_Z_Max - Mag_Z_Min);  
  
  MagOffset[2] = (Mag_Z_Max + Mag_Z_Min) / 2;
}
//================================================================================================
//Clear Mag_XY Min/Max Temp Calibration Values
//================================================================================================
void ClearMag_XY()
{
  Mag_X_Max = Mag_X_Min = Mag_Y_Max = Mag_Y_Min = 0;
}
//================================================================================================
//Clear Mag_Z Min/Max Temp Calibration Values
//================================================================================================
void ClearMag_Z()
{
  Mag_Z_Max = Mag_Z_Min = 0;
}
