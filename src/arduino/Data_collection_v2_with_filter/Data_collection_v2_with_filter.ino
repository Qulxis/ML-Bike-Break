/*
Author: Sam Brosh + Andrew
Description: Used for data collection for Embedded AI project.
Goal: Continuously collect accelerometer data in parallel with photoresistor data
Reason: Collect data about accelerometer while breaking on a bicycle to be used in neural network for
smart break detection.
Note: Implementation follows concerns and improvement over button implementation. Button was not 
accurate and reliable enough for confident data collection. Will use a threshold for 
photoresistor instead; Cover with finger when braking, leave exposed when not.
*/

#include "Arduino_BMI270_BMM150.h"
#include <SimpleKalmanFilter.h>

// Kalman filtering
float e_mea = 0.1; // Amount to expect in noise
float e_est = 0.1; // Set to e_mea as described by https://github.com/denyssene/SimpleKalmanFilter
float q = 0.008; //  usually a small number between 0.001 and 1 how fast your measurement moves. Recommended 0.01. Should be tunned to your needs. (I think for this is equivalent to 1)
// Create a new instance of the SimpleKalmanFilter class
//X variations
SimpleKalmanFilter kalman_x1(0.05, 0.05, 0.008);
SimpleKalmanFilter kalman_x2(.1, .1, 0.008);
SimpleKalmanFilter kalman_x3(.1, .1, 0.5);
SimpleKalmanFilter kalman_x4(1, 1, 0.05);
SimpleKalmanFilter kalman_x5(10, 10, 0.08);

//Y and z
SimpleKalmanFilter kalman_y(e_mea, e_est, q);
SimpleKalmanFilter kalman_z(e_mea, e_est, q);
// End of filter declarations

const int prPin = 0;

void setup() {
  // Initialize baudrate, IMU, accelerometer check
  Serial.begin(9600);
  while(!Serial);
  Serial.println("Started");

  if(!IMU.begin()) {
    Serial.println("Failed to initialize IMU!");
    while (1);
  }

  // accelerometer check:
  Serial.print("Accelerometer sample rate = ");
  Serial.print(IMU.accelerationSampleRate());
  Serial.println(" Hz");
  Serial.println();
  Serial.println("Acceleration in G's, photosensitive resistor state");
  Serial.println("x_accel,y_accel,z_accel,photoresistor_value");

  pinMode(prPin, INPUT);
}

void loop() {
  float x_accel, y_accel, z_accel;
  if (IMU.accelerationAvailable()) {
    IMU.readAcceleration(x_accel, y_accel, z_accel); // READ data
    //Raw x    
    Serial.print("x_accel_raw:");
    Serial.print(x_accel);
    Serial.print(',');

    Serial.print("y_accel_raw:");
    Serial.print(y_accel);
    Serial.print(',');
    
    Serial.print("z_accel_raw:");
    Serial.print(z_accel);
    Serial.print(',');
    
  

    ////////////////// Kalman stuff START//////////////////////////////
    // Update the state of the Kalman filter with the new data
    //x variations
    float x_est1 = kalman_x1.updateEstimate(x_accel);
    float x_est2 = kalman_x2.updateEstimate(x_accel);
    float x_est3 = kalman_x3.updateEstimate(x_accel);
    float x_est4 = kalman_x4.updateEstimate(x_accel);
    float x_est5 = kalman_x5.updateEstimate(x_accel);
    //y variations
    float y_est = kalman_y.updateEstimate(y_accel);
    float z_est = kalman_z.updateEstimate(z_accel);
    
    Serial.print("x_kalman1:");
    Serial.print(x_est1);
    Serial.print(",");

    Serial.print("x_kalman2:");
    Serial.print(x_est2);
    Serial.print(",");

    Serial.print("x_kalman3:");
    Serial.print(x_est3);
    Serial.print(",");

    Serial.print("x_kalman4:");
    Serial.print(x_est4);
    Serial.print(",");

    Serial.print("x_kalman5:");
    Serial.print(x_est5);
    Serial.print(",");

    
    Serial.print("y_kalman:");
    Serial.print(y_est);
    Serial.print(",");
    
    Serial.print("z_kalman:");
    Serial.println(z_est);
    Serial.print(",");

    ////////////////// Kalman stuff END//////////////////////////////
    
    // label/////////////
    int reading = analogRead(prPin);
    Serial.print("label:");
    // Serial.print(reading);
    // Serial.print('\n');
    if (reading < 900) {
      Serial.println(1);
    } else {
      Serial.println(0);
    }

  }
  delay(25);
}




