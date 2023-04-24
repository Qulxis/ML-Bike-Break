#include <SimpleKalmanFilter.h>
#include <Kalman.h>
#include <FastLED.h>
#include <Servo.h>
#include <Wire.h>
#include <Math.h>

// Global init kalman filters for the MPU readings, not sure what the params should be here
// SimpleKalmanFilter kalmanX(.1, .1, 0.008);
// SimpleKalmanFilter kalmanY(.1, .1, 0.008);
// SimpleKalmanFilter kalmanZ(.1, .1, 0.008);
Kalman kalmanFilter;

// From https://docs.arduino.cc/tutorials/nano-33-iot/imu-accelerometer
// float x, y, z;
// int degreesX = 0;
// int degreesY = 0;

float xAccel, yAccel, zAccel;
float xFiltered, yFiltered, zFiltered;

Adafruit_ADXL345 accelerometer;

void setup() {
  Serial.begin(9600);
  accelerometer.begin();
  kalmanFilter.setAngle(0); // Initialize the filter
}
void loop() {
  // Read the accelerometer data
  accelerometer.readXYZ(&xAccel, &yAccel, &zAccel);

  // Apply the Kalman filter to the X, Y, and Z axis
  xFiltered = kalmanFilter.getAngle(xAccel, 0, 0, millis());
  yFiltered = kalmanFilter.getAngle(yAccel, 0, 0, millis());
  zFiltered = kalmanFilter.getAngle(zAccel, 0, 0, millis());

  // Print the filtered data to the serial monitor
  Serial.print("X: ");
  Serial.print(xFiltered);
  Serial.print(" Y: ");
  Serial.print(yFiltered);
  Serial.print(" Z: ");
  Serial.println(zFiltered);
}
//
// Code for using external accel sensor below
// void read_accel() {
//   /*
//   * Take one reading of current ACCELEROMETER values, 
//   * update the global mpu_arr_raw variable to store them
//   */
//   Wire.beginTransmission(MPU_ADDR);
//   Wire.write(ACCEL_XOUT_H); // starting with register GYRO_XOUT_H [MPU-6000 and MPU-6050 Register Map and Descriptions Revision 4.2, p.40]
//   Wire.endTransmission(false); // the parameter indicates that the Arduino will send a restart. As a result, the connection is kept active.
//   Wire.requestFrom(MPU_ADDR, 6, true); // request a total of 3*2=6 registers, then stops the transmission bc that `true`
  
//   // "Wire.read()<<8 | Wire.read();" means two registers are read and stored in the same variable
//   mpu_arr_raw[0] = Wire.read()<<8 | Wire.read(); // reading registers: 0x43 (ACCEL_XOUT_H) and 0x44 (ACCEL_XOUT_L)
//   mpu_arr_raw[1] = Wire.read()<<8 | Wire.read(); // reading registers: 0x45 (ACCEL_YOUT_H) and 0x46 (ACCEL_YOUT_L)
//   mpu_arr_raw[2] = Wire.read()<<8 | Wire.read(); // reading registers: 0x47 (ACCEL_ZOUT_H) and 0x48 (ACCEL_ZOUT_L)  
// }

// void kalman_MPU() {
//   // Updates kalman estimates for mpu readings
//   mpu_arr_kal[0] = kalmanX.updateEstimate(mpu_arr_raw[0]);
//   mpu_arr_kal[1] = kalmanY.updateEstimate(mpu_arr_raw[1]);
//   mpu_arr_kal[2] = kalmanZ.updateEstimate(mpu_arr_raw[2]);
// }

