#include <TensorFlowLite.h>

#include <stdio.h>
#include <time.h>
#include <SimpleKalmanFilter.h>


#include <tensorflow/lite/micro/all_ops_resolver.h>
#include <tensorflow/lite/micro/micro_error_reporter.h>
#include <tensorflow/lite/micro/micro_interpreter.h>
#include <tensorflow/lite/schema/schema_generated.h>
#include <tensorflow/lite/version.h>
#include "Arduino_BMI270_BMM150.h"
#include "model.h"

// global variables used for TensorFlow Lite (Micro)
tflite::MicroErrorReporter tflErrorReporter;

// pull in all the TFLM ops, you can remove this line and
// only pull in the TFLM ops you need, if would like to reduce
// the compiled size of the sketch.
tflite::AllOpsResolver tflOpsResolver;

const tflite::Model* tflModel = nullptr;
tflite::MicroInterpreter* tflInterpreter = nullptr;
TfLiteTensor* tflInputTensor = nullptr;
TfLiteTensor* tflOutputTensor = nullptr;

// Create a static memory buffer for TFLM, the size may need to
// be adjusted based on the model you are using
constexpr int tensorArenaSize = 20 * 1024;
byte tensorArena[tensorArenaSize];

SimpleKalmanFilter kalman_x1(0.05, 0.05, 0.008);

const int prPin = 0;

void setup() {
  Serial.begin(9600);
  while (!Serial) {};

  Serial.println("Smart Bicycle Brake Classification using Accelerometer");
  Serial.println("--------------------------------------------");
  Serial.println("Arduino Nano 33 BLE Sense running TensorFlow Lite Micro");
  Serial.println("");

  pinMode(prPin, INPUT);

  if(!IMU.begin()) {
    Serial.println("Failed to initialize IMU!");
    while (1);
  }

  tflModel = tflite::GetModel(model);
  if (tflModel->version() != TFLITE_SCHEMA_VERSION) {
    Serial.println("Model schema mismatch!");
    while (1);
  }

  // Create an interpreter to run the model
  tflInterpreter = new tflite::MicroInterpreter(tflModel, tflOpsResolver, tensorArena, tensorArenaSize, &tflErrorReporter);

  // Allocate memory for the model's input and output tensors
  tflInterpreter->AllocateTensors();

  // Get pointers for the model's input and output tensors
  tflInputTensor = tflInterpreter->input(0);
  tflOutputTensor = tflInterpreter->output(0);

}

const int BUFFER_LENGTH = 120;
// initialize the buffer and the index variables:
float buffer[BUFFER_LENGTH] = {0};

void add_to_buffer(float x_accel) {

  // shift buffer values to the right
  for (int i = BUFFER_LENGTH - 1; i >= 1; i--) {
    buffer[i] = buffer[i - 1];
  }

  // insert new input value at the beginning of the buffer
  buffer[0] = x_accel;
}

int count = 0;

void loop() {
  count = count + 1;
  float x_accel, y_accel, z_accel;
  if (IMU.accelerationAvailable()) {
    IMU.readAcceleration(x_accel, y_accel, z_accel);

  }

  // offset between the old and new arduino:
  x_accel = x_accel + 0.22;

  // Call kalman filter function on x_accel.

  float x_est1 = kalman_x1.updateEstimate(x_accel);

  // kalman done

  add_to_buffer(x_est1);

  if (count > BUFFER_LENGTH) {
    int i = 0;
    while (i < BUFFER_LENGTH) {
      tflInputTensor->data.f[i] = buffer[BUFFER_LENGTH - 1 - i];
      i = i + 1;
    }
    

    // run inferencing
    TfLiteStatus invokeStatus = tflInterpreter->Invoke();
    if (invokeStatus != kTfLiteOk) {
      Serial.println("Invoke failed!");
      while (1);
      return;
    }

    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    Serial.print(tm.tm_min);
    Serial.print(",");
    Serial.print(tm.tm_sec);
    Serial.print(",");

    Serial.print(int(tflOutputTensor->data.f[0] * 100));
    Serial.print(",");


    int reading = analogRead(prPin);

    Serial.print(reading);

    Serial.print(",");

    Serial.print(x_accel);

    Serial.println();
  }

  delay(25);
}










