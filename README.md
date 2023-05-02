# ML-Bike-Break
Embedded AI Project: Machine Learning bike brake detection using Arduino and TFLite.

### [Watch our Project Video!](https://www.youtube.com/watch?v=RIn2AcNfQwM&ab_channel=KennethMucyo)

Authors:
- [Andrew X](https://github.com/Qulxis)
- [Kenneth M](https://github.com/Kennethm-spec)
- [Sam B](https://github.com/sdb2174)


## Equipment and Tools:
### Hardware:
- Arduino Nano 33 BLE
- Photoresistor (For manual labeling)
### Software:
- Arduino/C
- Python

To install the version of python libraries used run:
```
$ pip install -r requirements.txt
```
# Walkthrough:
## Data Collection
The collection of data was using the files in the src/arduino folder. 

- "src/arduino/Data_collection_v2" was used to collect raw sensor data for EDA. 

- "src/arduino/Data_collection_v2_with_filter" was used to collect data for training including like kalman filtering. 

- "src/arduino/Break_classifier" is used to collect observation of a loaded model's performance.

(The remaining files in src/arduino are for experimentation)

Training Data
- **/src/Data/train/train_data1.csv:** Collected with "src/Data_collection_v2"
- **/src/Data/train/train_data1.csv:** Collected with "src/Data_collection_v2_with_filter"

Testing Data
- **/src/Data/test_data.csv** Collected with "src/arduino/Break_classifier"

## Data Cleaning
The two notebooks that we used in the end for data cleaning and generation are:
- src/data_exploration_dataGen2.ipynb
- src/kalman_filter_dataGen1.ipynb

The first creates the cleaned dataset from the last collection of data we did which recorded both the kalman filtered data as well as the raw date. It 

The second creates the cleaned dataset from the first collection of data we did which contained the x, y, and z data from the sensor. The notebook explores all three and notes that only x has significant correlation. It then run a simulated kalman filter over the raw x-axis accelerometer data.

Both notebooks filters out cases where valid break labels must be held for 4 sample steps. This is to remove noise from the photoresistor that we used to record with by hand. 

Both find the resting sensor value and shifts the kalman filtered data by that much so its resting state corresponds to 0. **The main reason is because the accelerometer measures both gravitationaly and linear acceleration and because the arduinos were installed in differen location on different bike, the gravitational acceleration contribution changes thus the "not moving state" differs between the two dataset.** 

Additionally 2 different arduino nanos BLE 33s were used both to make ensure consistency and make sure our model and approach were robust to different devices. Additionally, the datasets were collected on different terrains and different conditions. 

The final ouptut for both are csv files (train_data4.csv and train_data1.5) that contain the filtered and adjusted sensor data along with the cleaned labels.

# Evaluation
For proof of concept and evaluation, we used:
- src/simple_model_training.ipynb
- src/model_making.ipynb
- src/test_evaluation.ipynb

The first (simple_model_training) shows a sklearn logistic regression model on one set of data to show some experimentation with modeling. Note this is a simple model and is not the final model used in the embedded enviornment.

The second (model_making) creates and trains a TF model and compresses it through TFLite. This can then be loaded onto the arudiono for inference for then running brake_classifier.ino. The output model from our training is in src/model.h

The third (test_evaluation) looks at the "test_data.cvs" file which contains the recording from a live test of our embedded model on the Arduino. It looks at the ground truth labels, the model's predictions, and the filtered sensor data.

# Results
To see the examples of our model's performance and outputs, see the images in the "Images" folder which contains both the performace over the entire test run as well as a close of of a few notable cases. The first cluster of false positives are mostly due to mislabeling as this corresponds to our rider remounting and reorienting the bike after braking. Data was somewhat smaller than ideal (under 20k samples) as data was collected by hand but overal this serves as a proof of concept and explore the necessary considerations to take into account when scaling to a production level device. 
