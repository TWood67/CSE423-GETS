//=================================================================================================
//This is where the MAGIC! happens.  Have to crack open my Linear Algebra text from college!
//=================================================================================================
float Accel_Vector[3];   //Acceleration Vector
float Gyro_Vector[3];    //Rotation Rate Vector
float Omega_Vector[3];   //Corrected Gyro_Vector  
float Omega_P[3];        //Omega Proportional Correction
float Omega_I[3];        //Omega Integrator
float Omega[3];

float errorRollPitch[3]; 
float errorYaw[3];
float errorCourse = 180; 

#define Gyro_Gain   0.0609

#define Kp_ROLLPITCH   0.015           //PID Coefficients
#define Ki_ROLLPITCH   0.000010
#define Kp_YAW         2.5                  
#define Ki_YAW         0.00005


float DCM_Matrix[3][3]; 
float Update_Matrix[3][3];     
float Temporary_Matrix[3][3];

#define GPS_SPEEDFILT  2      // >1 use min speed filter for GPS yaw drift (m/s), 0 = do not use speed filter
float GPS_CourseOverGround_X; //Course overground X axis
float GPS_CourseOverGround_Y; //Course overground Y axis

//========================================================================
//============================ DCM Algorithm =============================
//========================================================================
//DCM Normalize
//========================================================================
void DCM_Normalize(void)
{
  float error = 0;
  float temporary[3][3];
  float renorm = 0;
  boolean problem = false;
  
  error= -Vector_Dot_Product(&DCM_Matrix[0][0], &DCM_Matrix[1][0]) * .5;    //eq.19

  Vector_Scale(&temporary[0][0], &DCM_Matrix[1][0], error);                 //eq.19
  Vector_Scale(&temporary[1][0], &DCM_Matrix[0][0], error);                 //eq.19
  
  Vector_Add(&temporary[0][0], &temporary[0][0], &DCM_Matrix[0][0]);        //eq.19
  Vector_Add(&temporary[1][0], &temporary[1][0], &DCM_Matrix[1][0]);        //eq.19
  
  Vector_Cross_Product(&temporary[2][0],&temporary[0][0],&temporary[1][0]); // c= a x b //eq.20
  
  renorm = Vector_Dot_Product(&temporary[0][0], &temporary[0][0]); 
  if      (renorm < 1.5625f && renorm > 0.64f)  renorm= .5 * (3-renorm);    //eq.21
  else if (renorm < 100.0f  && renorm > 0.01f)  renorm= 1. / sqrt(renorm);
  else                                          problem = true;
  
  Vector_Scale(&DCM_Matrix[0][0], &temporary[0][0], renorm);
  
  renorm = Vector_Dot_Product(&temporary[1][0], &temporary[1][0]); 
  if      (renorm < 1.5625f && renorm > 0.64f)  renorm= .5 * (3-renorm);    //eq.21
  else if (renorm < 100.0f  && renorm > 0.01f)  renorm= 1. / sqrt(renorm);  
  else                                          problem = true;
  
  Vector_Scale(&DCM_Matrix[1][0], &temporary[1][0], renorm);
  
  renorm = Vector_Dot_Product(&temporary[2][0], &temporary[2][0]); 
  if      (renorm < 1.5625f && renorm > 0.64f) renorm= .5 * (3-renorm);     //eq.21
  else if (renorm < 100.0f  && renorm > 0.01f) renorm= 1. / sqrt(renorm);   
  else                                         problem = true;  
  
  Vector_Scale(&DCM_Matrix[2][0], &temporary[2][0], renorm);
  
  if (problem) 
  {   
      DCM_Matrix[0][0] = 1.0f;
      DCM_Matrix[0][1] = 0.0f;
      DCM_Matrix[0][2] = 0.0f;
      DCM_Matrix[1][0] = 0.0f;
      DCM_Matrix[1][1] = 1.0f;
      DCM_Matrix[1][2] = 0.0f;
      DCM_Matrix[2][0] = 0.0f;
      DCM_Matrix[2][1] = 0.0f;
      DCM_Matrix[2][2] = 1.0f;
      problem = false;  
  }
}
//========================================================================
//DCM Drift Correction
//========================================================================
void DCM_DriftCorrection(void)
{
  static float Scaled_Omega_P[3];
  static float Scaled_Omega_I[3];
  float Accel_magnitude;
  float Accel_weight;
  float Integrator_magnitude;
                                         //Roll and Pitch
                                         //Calculate the magnitude of the accelerometer vector
  Accel_magnitude = sqrt(Accel_Vector[0] * Accel_Vector[0] + Accel_Vector[1] * Accel_Vector[1] + Accel_Vector[2] * Accel_Vector[2]);
  Accel_magnitude = Accel_magnitude / GRAVITY; //Scale to gravity from MPU6000 chip
                                         //Dynamic weighting of accelerometer info (reliability filter)
                                         //Weight for accelerometer info (<0.5G = 0.0, 1G = 1.0 , >1.5G = 0.0)
  Accel_weight = constrain(1 - 2 * abs(1 - Accel_magnitude), 0, 1);   
  
  Vector_Cross_Product (&errorRollPitch[0], &Accel_Vector[0], &DCM_Matrix[2][0]); //adjust the ground of reference
  Vector_Scale (&Omega_P[0], &errorRollPitch[0], Kp_ROLLPITCH * Accel_weight);
  
  Vector_Scale (&Scaled_Omega_I[0], &errorRollPitch[0], Ki_ROLLPITCH * Accel_weight);
  Vector_Add (Omega_I, Omega_I, Scaled_Omega_I);     
  
  #ifdef USE_MAGNETOMETER_YAW_CORRECTION 
                                                           //YAW drift correction based on compass magnetic heading
  errorCourse = (DCM_Matrix[0][0] * MagHeading_Y) - (DCM_Matrix[1][0] * MagHeading_X);  //Calculating YAW error
  Vector_Scale (errorYaw, &DCM_Matrix[2][0], errorCourse); //Apply the yaw correction to the XYZ rotation of the aircraft, depeding the position.
    
  Vector_Scale (&Scaled_Omega_P[0], &errorYaw[0], Kp_YAW);
  Vector_Add (Omega_P, Omega_P, Scaled_Omega_P);           //Adding Proportional.
    
  Vector_Scale (&Scaled_Omega_I[0], &errorYaw[0], Ki_YAW);
  Vector_Add (Omega_I, Omega_I, Scaled_Omega_I);          //Adding integrator to Omega_I  
    
  #else                                                   //Use GPS Ground course to correct yaw gyro drift
  
  if(GPS.ground_speed >= GPS_SPEEDFILT * 100)             //Ground speed from GPS is in m/s
  {
    GPS_CourseOverGround_X = cos(ToRad(GPS.ground_course / 100.0));
    GPS_CourseOverGround_Y = sin(ToRad(GPS.ground_course / 100.0));
                                                               //Calculating YAW error
    errorCourse = (DCM_Matrix[0][0] * GPS_CourseOverGround_Y) - (DCM_Matrix[1][0] * GPS_CourseOverGround_X); 
    Vector_Scale (errorYaw, &DCM_Matrix[2][0], errorCourse);   //Apply yaw correction to the XYZ rotation 
  
    Vector_Scale (&Scaled_Omega_P[0], &errorYaw[0], Kp_YAW);
    Vector_Add (Omega_P, Omega_P, Scaled_Omega_P);             //Adding  Proportional.
  
    Vector_Scale (&Scaled_Omega_I[0], &errorYaw[0], Ki_YAW);
    Vector_Add (Omega_I, Omega_I, Scaled_Omega_I);             //Adding integrator to Omega_I   
    
  }
  #endif
                                                       //Limit on the integrator so that the integrator cannot 
                                                       //exceed half the saturation limit of the gyros 
  Integrator_magnitude = sqrt(Vector_Dot_Product (Omega_I, Omega_I) );  
  if (Integrator_magnitude > ToRad(300)) Vector_Scale (Omega_I, Omega_I, 0.5f * ToRad(300) / Integrator_magnitude);
 }
//========================================================================
//Account for Centrifugal Acceleration
//========================================================================
void Accel_adjust(void)
{
#ifdef USE_GPS  
  //Accel_Vector[1] += Accel_Scale ((GPS.ground_speed / 100) * Omega[2] * (GRAVITY/9.81));  //Centrifugal force on Acc_y = GPS ground speed (m/s) * GyroZ
  //Accel_Vector[2] -= Accel_Scale ((GPS.ground_speed / 100) * Omega[1] * (GRAVITY/9.81));  //Centrifugal force on Acc_z = GPS ground speed (m/s) * GyroY 
  Accel_Vector[1] += (GPS.ground_speed / 100) * Omega[2] * (GRAVITY/9.81);  //Centrifugal force on Acc_y = GPS ground speed (m/s) * GyroZ
  Accel_Vector[2] -= (GPS.ground_speed / 100) * Omega[1] * (GRAVITY/9.81);  //Centrifugal force on Acc_z = GPS ground speed (m/s) * GyroY 
#endif
}
//========================================================================
//DCM Matrix Update
//========================================================================
void DCM_MatrixUpdate(float delta_time)
{
  Gyro_Vector[0] = (GyroRaw[0] - GyroRawOffset[0]) * ToRad(Gyro_Gain);    //Gyro X
  Gyro_Vector[1] = (GyroRawOffset[1] - GyroRaw[1]) * ToRad(Gyro_Gain);    //Gyro Y
  Gyro_Vector[2] = (GyroRawOffset[2] - GyroRaw[2]) * ToRad(Gyro_Gain);    //Gyro Z  
  
  Accel_Vector[0] = (AccelRawOffset[0] - AccelRaw[0]);                    //Accel x
  Accel_Vector[1] = (AccelRaw[1]       - AccelRawOffset[1]);              //Accel y
  Accel_Vector[2] = (AccelRaw[2]       - AccelRawOffset[2]);              //Accel z
  
  Vector_Add (&Omega[0],        &Gyro_Vector[0], &Omega_I[0]);  //Add Proportional term
  Vector_Add (&Omega_Vector[0], &Omega[0],       &Omega_P[0]);  //Add Integrator term

  Accel_adjust();                                               //Remove centrifugal if usingh GPS

  Update_Matrix[0][0] =  0;
  Update_Matrix[0][1] = -delta_time * Omega_Vector[2];                //-Z
  Update_Matrix[0][2] =  delta_time * Omega_Vector[1];                // Y
  
  Update_Matrix[1][0] =  delta_time * Omega_Vector[2];                // Z
  Update_Matrix[1][1] =  0;
  Update_Matrix[1][2] = -delta_time * Omega_Vector[0];                //-X
  
  Update_Matrix[2][0] = -delta_time * Omega_Vector[1];                //-Y
  Update_Matrix[2][1] =  delta_time * Omega_Vector[0];                // X
  Update_Matrix[2][2] =  0;

  Matrix_Multiply (DCM_Matrix, Update_Matrix, Temporary_Matrix);     //a*b=c

  for(int x=0; x<3; x++)                                             //Matrix Addition 
  {
    for(int y=0; y<3; y++) DCM_Matrix[x][y] += Temporary_Matrix[x][y];
  }
}
//========================================================================
//Get Roll, Pitch & Yaw Angles in Radians
//========================================================================
void DCM_EulerAngles(void)
{
    pitch =  -asin(DCM_Matrix[2][0]);
    roll =   atan2(DCM_Matrix[2][1], DCM_Matrix[2][2]);
    yaw =    atan2(DCM_Matrix[1][0], DCM_Matrix[0][0]);
}

//========================================================================
//Matrix Operations Library
//========================================================================
//Dot Product
//========================================================================
float Vector_Dot_Product (float vector1[3], float vector2[3]) //Dot Product
{
  float op=0;
  
  for(int i=0; i<3; i++) op += vector1[i] * vector2[i];
  return op; 
}
//========================================================================
//Cross Product
//========================================================================
void Vector_Cross_Product (float vectorOut[3], float vectorIn_1[3], float vectorIn_2[3])   
{
  vectorOut[0] = (vectorIn_1[1] * vectorIn_2[2]) - (vectorIn_1[2] * vectorIn_2[1]);
  vectorOut[1] = (vectorIn_1[2] * vectorIn_2[0]) - (vectorIn_1[0] * vectorIn_2[2]);
  vectorOut[2] = (vectorIn_1[0] * vectorIn_2[1]) - (vectorIn_1[1] * vectorIn_2[0]);
}
//========================================================================
//Multiply the vector by a scalar
//========================================================================
void Vector_Scale (float vectorOut[3], float vectorIn[3], float scaler)   
{
  for(int i=0; i<3; i++) vectorOut[i] = vectorIn[i] * scaler; 
}
//========================================================================
//Vector Add
//========================================================================
void Vector_Add (float vectorOut[3], float vectorIn1[3], float vectorIn2[3])  
{
  for(int i=0; i<3; i++) vectorOut[i] = vectorIn1[i] + vectorIn2[i];
}
//========================================================================
//Matrix Multiply
//========================================================================
void Matrix_Multiply (float a[3][3], float b[3][3], float mat[3][3])         
{
  float op[3]; 
  
  for(int x=0; x<3; x++)
  {
    for(int y=0; y<3; y++)
    {
      for(int w=0; w<3; w++) op[w] = a[x][w] * b[w][y];
      mat[x][y] = 0;
      mat[x][y] = op[0] + op[1] + op[2];
    }
  }
}



