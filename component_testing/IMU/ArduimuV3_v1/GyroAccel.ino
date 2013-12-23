/*
MPU6000 3-Axis Accelerometer/Gyro - with onboard ADCs and processor

http://dlnmh9ip6v2uc.cloudfront.net/datasheets/Components/General%20IC/PS-MPU-6000A.pdf

Uses SPI Bus Interface
Access to MPU6000 is by reading from and writing to onboard registers.
Has an onboard processor and ADCs that continously reads the 3 axis gyro and accelerometer data
and puts all data in registers. The data read rate is configured using the MPUREG_SMPLRT_DIV 
register set to 50hz ADCC rate. Configured to Interrupt the ATMega328 on Int0 Pin D2 when data is 
ready and increments a byte MPU6000_newdata - not being used in code.

Note: There are 2 revisions of the chip C & D which affects the scale for GRAVITY.  Initialization
selects the correct value.

ATMEGA328       MPU6000
D11 MOSI        MOSI
D12 MISO        MISO
D13 SCK         SCL/SCLK 
D2              INT - Interrupts Arduino on D2 on DataReady - increments MPU6000_newdata location
D4              FSYNC - Device Select for SPI interface
*/
#include <SPI.h>
                                   //MPU6000 registers
#define MPU6000_CHIP_SELECT_PIN 4  //MPU6000 Chip Select
#define MPUREG_WHOAMI 0x75         //Not used
#define	MPUREG_SMPLRT_DIV 0x19 
#define MPUREG_CONFIG 0x1A 
#define MPUREG_GYRO_CONFIG 0x1B
#define MPUREG_ACCEL_CONFIG 0x1C
#define MPUREG_INT_PIN_CFG 0x37
#define	MPUREG_INT_ENABLE 0x38 
#define MPUREG_ACCEL_XOUT_H 0x3B 
#define MPUREG_ACCEL_XOUT_L 0x3C 
#define MPUREG_ACCEL_YOUT_H 0x3D 
#define MPUREG_ACCEL_YOUT_L 0x3E 
#define MPUREG_ACCEL_ZOUT_H 0x3F 
#define MPUREG_ACCEL_ZOUT_L 0x40 
#define MPUREG_TEMP_OUT_H 0x41
#define MPUREG_TEMP_OUT_L 0x42
#define MPUREG_GYRO_XOUT_H 0x43 
#define	MPUREG_GYRO_XOUT_L 0x44 
#define MPUREG_GYRO_YOUT_H 0x45 
#define	MPUREG_GYRO_YOUT_L 0x46 
#define MPUREG_GYRO_ZOUT_H 0x47 
#define	MPUREG_GYRO_ZOUT_L 0x48 
#define MPUREG_USER_CTRL 0x6A 
#define	MPUREG_PWR_MGMT_1 0x6B 
#define	MPUREG_PWR_MGMT_2 0x6C      //Not used
                                    //MPU6000 Configuration bits  
#define BIT_SLEEP                   0x40
#define BIT_H_RESET                 0x80
#define BITS_CLKSEL                 0x07
#define MPU_CLK_SEL_PLLGYROX        0x01
#define MPU_CLK_SEL_PLLGYROZ        0x03
#define MPU_EXT_SYNC_GYROX          0x02
#define BITS_FS_250DPS              0x00
#define BITS_FS_500DPS              0x08
#define BITS_FS_1000DPS             0x10
#define BITS_FS_2000DPS             0x18
#define BITS_FS_MASK                0x18
#define BITS_DLPF_CFG_256HZ_NOLPF2  0x00
#define BITS_DLPF_CFG_188HZ         0x01
#define BITS_DLPF_CFG_98HZ          0x02
#define BITS_DLPF_CFG_42HZ          0x03
#define BITS_DLPF_CFG_20HZ          0x04
#define BITS_DLPF_CFG_10HZ          0x05
#define BITS_DLPF_CFG_5HZ           0x06
#define BITS_DLPF_CFG_2100HZ_NOLPF  0x07
#define BITS_DLPF_CFG_MASK          0x07
#define	BIT_INT_ANYRD_2CLEAR	    0x10
#define	BIT_RAW_RDY_EN		    0x01
#define	BIT_I2C_IF_DIS              0x10
                                        
// Product Name	Product Revision
#define MPU6000ES_REV_C4  0x14 	// 0001		0100
#define MPU6000ES_REV_C5  0x15 	// 0001		0101
#define MPU6000ES_REV_D6  0x16	// 0001		0110
#define MPU6000ES_REV_D7  0x17	// 0001		0111
#define MPU6000ES_REV_D8  0x18	// 0001		1000	
#define MPU6000_REV_C4    0x54  // 0101		0100 
#define MPU6000_REV_C5    0x55	// 0101		0101
#define MPU6000_REV_D6    0x56	// 0101		0110	
#define MPU6000_REV_D7    0x57	// 0101		0111
#define MPU6000_REV_D8    0x58	// 0101		1000
#define MPU6000_REV_D9    0x59	// 0101		1001
#define MPUREG_PRODUCT_ID 0x0C	// Product ID Register

volatile uint8_t MPU6000_newdata;   //Interrupt variable
                                                
//========================================================================
//SPI Read
//========================================================================
byte MPU6000_SPI_read(byte reg)
{
  byte dummy;
  byte reg_value;
  byte reg_addr = reg | 0x80;                   //Set most significant bit of register
  
  digitalWrite(MPU6000_CHIP_SELECT_PIN, LOW);   //Select Device
  dummy = SPI.transfer(reg_addr);               //Send SPI register address
  
  reg_value = SPI.transfer(0);                  //Get data 
  digitalWrite(MPU6000_CHIP_SELECT_PIN, HIGH);  //Deselect device
  return(reg_value);
}
//========================================================================
//SPI Write
//========================================================================
void MPU6000_SPI_write(byte reg_addr, byte reg_data)
{
  byte dummy;
  
  digitalWrite(MPU6000_CHIP_SELECT_PIN, LOW);     //Select Device
  dummy = SPI.transfer(reg_addr);                 //Select register
  dummy = SPI.transfer(reg_data);                 //Send data to register
  digitalWrite(MPU6000_CHIP_SELECT_PIN, HIGH);    //Deselect device
}
//========================================================================
//Interrupt Routine
//========================================================================
void MPU6000_data_int()            //MPU6000 Interrupt into Arduino on D2
{                                  //Initialization below attaches the interrupt routine for Arduino
                                   //attachInterrupt(0,MPU6000_data_int,RISING)
                                   //Parameters:
                                   //   0                = Arduino Interrupt #0 on Pin D2 of ATMega328
                                   //   MPU6000_data_int = Interrupt routine to execute
                                   //   RISING           = Interrupt on Positive Edge 
                                   
   MPU6000_newdata++;              //Increment new data count - not used
}
//========================================================================
//Initialize GyroAccel
//========================================================================
void GyroAccelInit(void)                                                     //MPU6000 Initialization and Configuration
{
    uint8_t product_id;                                                      //MPU6000 Product ID 
    
    pinMode(MPU6000_CHIP_SELECT_PIN, OUTPUT);                                //MPU6000 chip select setup - Pin D4
    digitalWrite(MPU6000_CHIP_SELECT_PIN, HIGH);
   
    SPI.begin();                                                             //SPI Initialization
    
    SPI.setClockDivider(SPI_CLOCK_DIV16);                       delay(10);   //SPI at 1Mhz (on 16Mhz clock)
    MPU6000_SPI_write(MPUREG_PWR_MGMT_1, BIT_H_RESET);          delay(100);  //MPU6000 Reset
    MPU6000_SPI_write(MPUREG_PWR_MGMT_1, MPU_CLK_SEL_PLLGYROZ); delay(1);    //Wake up device and select GyroZ clock
    MPU6000_SPI_write(MPUREG_USER_CTRL, BIT_I2C_IF_DIS);        delay(1);    //Disable I2C bus (recommended)
  //MPU6000_SPI_write(MPUREG_SMPLRT_DIV,0x04);                  delay(1);    //Sample rate = 200Hz   Fsample= 1Khz/(4+1) = 200Hz     
    MPU6000_SPI_write(MPUREG_SMPLRT_DIV,19);                    delay(1);    //Sample rate = 50Hz    Fsample= 1Khz/(19+1) = 50Hz     
    MPU6000_SPI_write(MPUREG_CONFIG, BITS_DLPF_CFG_20HZ);       delay(1);    //FS & DLPF  FS=2000º/s, DLPF = 20Hz (low pass filter)
    MPU6000_SPI_write(MPUREG_GYRO_CONFIG,BITS_FS_2000DPS);      delay(1);    //Gyro scale 2000º/s
    MPU6000_SPI_write(MPUREG_ACCEL_CONFIG,0x08);                delay(1);    //Accel scale 4g (4096LSB/g)
    
    product_id = MPU6000_SPI_read(MPUREG_PRODUCT_ID);
    delay(1);    
    
    if ((product_id == MPU6000ES_REV_C4) || (product_id == MPU6000ES_REV_C5) || //Rev C has different scaling than rev D
	(product_id == MPU6000_REV_C4)   || (product_id == MPU6000_REV_C5))
    {
      MPU6000_SPI_write(MPUREG_ACCEL_CONFIG,1<<3);  //Accel scale 4g (4096 LSB/g)  //I have this one
      GRAVITY = 4096.0;
    }
    else   
    {
      MPU6000_SPI_write(MPUREG_ACCEL_CONFIG,2<<3);  //Accel scale 8g (8192 LSB/g)
      GRAVITY = 8192.0;
    }
    delay(1);
                                                                             //Configure Interrupt
    MPU6000_SPI_write(MPUREG_INT_ENABLE,BIT_RAW_RDY_EN);        delay(1);    //INT: Set Interrupt on data ready
    MPU6000_SPI_write(MPUREG_INT_PIN_CFG,BIT_INT_ANYRD_2CLEAR); delay(1);    //INT: Clear Interrupt on any read
  //MPU6000_SPI_write(MPUREG_PWR_MGMT_1,MPU_CLK_SEL_PLLGYROZ);  delay(1);    //Oscillator set
    attachInterrupt(0,MPU6000_data_int,RISING);                              //Attach Interrupt on INT0 on ATMega328
}
//========================================================================
//Read Accelerometer Register Data in High-Low Bytes and return Integer
//========================================================================
void ReadAccelRaw()                                  //Read Accel XYZ into AccelRaw[] array
{
  int byte_H, byte_L;                                //Read High & Low Register Bytes and combine

  byte_H = MPU6000_SPI_read (MPUREG_ACCEL_XOUT_H);   //Read Accel X
  byte_L = MPU6000_SPI_read (MPUREG_ACCEL_XOUT_L);
  AccelRaw[0] = (byte_H << 8) | byte_L;
   
  byte_H = MPU6000_SPI_read (MPUREG_ACCEL_YOUT_H);   //Read Accel Y
  byte_L = MPU6000_SPI_read (MPUREG_ACCEL_YOUT_L);
  AccelRaw[1] = (byte_H << 8) | byte_L;
    
  byte_H = MPU6000_SPI_read (MPUREG_ACCEL_ZOUT_H);   //Read Accel Z
  byte_L = MPU6000_SPI_read (MPUREG_ACCEL_ZOUT_L);
  AccelRaw[2] = (byte_H << 8) | byte_L;
}    
//========================================================================
//Read Gyro Register Data in High-Low Bytes and return Integer
//========================================================================
void ReadGyroRaw()                                   //Read Gyro XYZ into GyroRaw[] array
{
  int byte_H, byte_L;                                //Read High & Low Register Bytes and combine
    
  byte_H = MPU6000_SPI_read (MPUREG_GYRO_XOUT_H);    //Read Gyro X
  byte_L = MPU6000_SPI_read (MPUREG_GYRO_XOUT_L);
  GyroRaw[0] = (byte_H << 8) | byte_L;
    
  byte_H = MPU6000_SPI_read (MPUREG_GYRO_YOUT_H);    //Read Gyro Y
  byte_L = MPU6000_SPI_read (MPUREG_GYRO_YOUT_L);
  GyroRaw[1] = (byte_H << 8) | byte_L;
    
  byte_H = MPU6000_SPI_read (MPUREG_GYRO_ZOUT_H);    //Read Gyro Z
  byte_L = MPU6000_SPI_read (MPUREG_GYRO_ZOUT_L);
  GyroRaw[2] = (byte_H << 8) | byte_L;
}
//========================================================================
//Read Temperature Register Data in High-Low Bytes and return Integer
//Could use for Linear correction to gyro/accel data - not used
//========================================================================
int ReadTemperatureRaw()                            //Read Temperature data from MPU6000
{
  int byte_H, byte_L;                               //Read High & Low Register Bytes and combine
    
  byte_H = MPU6000_SPI_read (MPUREG_TEMP_OUT_H);    //Read Temp
  byte_L = MPU6000_SPI_read (MPUREG_TEMP_OUT_L);
  return (byte_H << 8) | byte_L; 
}    

