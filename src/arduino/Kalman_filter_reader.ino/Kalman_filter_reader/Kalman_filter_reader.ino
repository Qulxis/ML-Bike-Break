#include <Arduino_BMI270_BMM150.h>
#include <SimpleKalmanFilter.h>

// // Define the Kalman filter parameters
// int arr_raw[3];
// int arr_kal[3]; // After applying kalman filters

float e_mea = .1
float e_est = .1
float q = 0.008
// Create a new instance of the SimpleKalmanFilter class
SimpleKalmanFilter kalman_x(e_mea, e_est, q);
SimpleKalmanFilter kalman_y(e_mea, e_est, q);
SimpleKalmanFilter kalman_z(e_mea, e_est, q);


void setup() {
  Serial.begin(9600);
  if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU!");
    while (1);
  }
}

void loop() {
  // Read accelerometer data from the IMU
  float x, y, z;
  if (IMU.accelerationAvailable()) {
    IMU.readAcceleration(x, y, z);
  } else {
    Serial.println("No acceleration data available!");
    return;
  }
  
  // Update the state of the Kalman filter with the new data
  float x_est = kalman_x.updateEstimate(x);
  float y_est = kalman_y.updateEstimate(y);
  float z_est = kalman_z.updateEstimate(z);
  
  Serial.print(x_est);
  Serial.print(",");
  Serial.print(y_est);
  Serial.print(",");
  Serial.println(z_est);

  delay(10);
}
