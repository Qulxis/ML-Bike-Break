/*
Author: Sam Brosh
Description: Used for data collection for Embedded AI project.
Goal: Continuously collect accelerometer data in parallel with photoresistor data
Reason: Collect data about accelerometer while breaking on a bicycle to be used in neural network for
smart break detection.
Note: Implementation follows concerns and improvement over button implementation. Button was not 
accurate and reliable enough for confident data collection. Will use a threshold for 
photoresistor instead; Cover with finger when braking, leave exposed when not.
*/

#include "Arduino_BMI270_BMM150.h"

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
    IMU.readAcceleration(x_accel, y_accel, z_accel);
    
    Serial.print(x_accel);
    Serial.print(',');
    Serial.print(y_accel);
    Serial.print(',');
    Serial.print(z_accel);
    Serial.print(',');
    int reading = analogRead(prPin);

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






