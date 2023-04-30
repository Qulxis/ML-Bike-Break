#include <iostream>
#include "SimpleKalmanFilter.h"

float e_mea = .1;
float e_est = .1;
float q = 0.008;
// Create a new instance of the SimpleKalmanFilter class
SimpleKalmanFilter kalman_x(e_mea, e_est, q);
SimpleKalmanFilter kalman_y(e_mea, e_est, q);
SimpleKalmanFilter kalman_z(e_mea, e_est, q);

int main()
{
    std::cout << "Hello World" << std::endl;
}