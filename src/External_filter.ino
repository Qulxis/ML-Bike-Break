//imports
#include <SimpleKalmanFilter.h>

// Def inputs:
// Will have to redefine to match for accelerometer 
#define PFS1  A0
#define PFS2  A1
#define PBS1  A2
#define PBS2  A3
#define PFM   A6
#define PBM   A7

// Kalman init
SimpleKalmanFilter kalman1(.1, .1, 0.008);

//Init pins
void setup() {
  // put your setup code here, to run once:

  pinMode(PFS1, INPUT);
  pinMode(PFS2, INPUT);
  pinMode(PBS1, INPUT);
  pinMode(PBS2, INPUT);
  pinMode(PFM, INPUT);
  pinMode(PBM, INPUT);
  Serial.begin(19200);

}

void loop() {
  // put your main code here, to run repeatedly:

  fs1v = analogRead(PFS1) * -1;
//   fs2v = analogRead(PFS2) * -1;
//   bs1v = analogRead(PBS1) * -1;
//   bs2v = analogRead(PBS2) * -1;
//   fmv = analogRead(PFM) * -1;
//   bmv = analogRead(PBM) * -1;

  float kfs1v = kalman1.updateEstimate(fs1v); //these are working
//   float kfs2v = kalman2.updateEstimate(fs2v);
//   float kbs1v = kalman3.updateEstimate(bs1v);
//   float kbs2v = kalman4.updateEstimate(bs2v);
//   float kfmv = kalman5.updateEstimate(fmv);
//   float kbmv = kalman5.updateEstimate(bmv);

  Serial.print("kfs1v:");
  Serial.print(kfs1v);
//   Serial.print(","); 
//   Serial.print("kfs2v:");
//   Serial.print(kfs2v);
//   Serial.print(",");
//   Serial.print("kbs1v:");
//   Serial.print(kbs1v);
//   Serial.print(",");
//   Serial.print("kbs2v:");
//   Serial.print(kbs2v);
//   Serial.print(",");
//  Serial.print("kfmv:");
//  Serial.print(kfmv);
//  Serial.print(",");
//  Serial.print("kbmv:");
//  Serial.print(kbmv);
//  Serial.print(",");
  
  Serial.println();


}
