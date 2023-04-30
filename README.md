# ML-Bike-Break
Embedded AI Project: Bike Brake using Arduino and TFLite

# Instructions:
The two notebooks that we used in the end for data cleaning and generation are:
- andrew_exploration_newdata.ipynb 
- kalman_filter.ipynb

The first creates the cleaned dataset from the last collection of data we did which recorded both the kalman filtered data as well as the raw date. 

The second creates the cleaned dataset from the first collection of data we did which contained the x, y, and z data from the sensor. The notebook explores all three and notes that only x has significant correlation. It then run a simulated kalman filter over the raw x-axis accelerometer data.

Both notebooks filters out cases where valid break labels must be held for 4 sample steps. This is to remove noise from the photoresistor that we used to record with by hand. 

Both find the resting sensor value and shifts the kalman filtered data by that much so its resting state corresponds to 0. **The main reason is because the accelerometer measures both gravitationaly and linear acceleration and because the arduinos were installed in differen location on different bike, the gravitational acceleration contribution changes thus the "not moving state" differs between the two dataset.** 

Additionally 2 different arduino nanos BLE 33s were used both to make ensure consistency and make sure our model and approach were robust to different devices. Additionally, the datasets were collected on different terrains and different conditions. 

The final ouptut for both are csv files (train_data4.csv and train_data1.5) that contain the filtered and adjusted sensor data along with the cleaned labels.


For proof of concept, we used:
- andrew_model_training.ipynb

