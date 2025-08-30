#ifndef MACHINE_LEARNING_H_
#define MACHINE_LEARNING_H_

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

// python
// #include <pybind11/pybind11.h>
// #include <pybind11/numpy.h>

struct Thetas {
    double theta0 = 0;
    double theta1 = 0;
};

class BGD {
    public:
        std::string filename;
        int epoches;
        double learning_rate;
        int m;
        std::vector<double> price;
        std::vector<double> milage;
        std::vector<double> predictions;
        Thetas tmp_thetas;
        Thetas thetas;

    BGD();
    BGD(std::string filename, double learning_rate, int epoches);
    ~BGD();

    void extract_data();
    double calculate_theta0();
    double calculate_theta1();
    void update_predictions();
    void update_thetas();
    void batch_gradient_descent();
};

std::vector<int> arr_to_vec(int arr[]);

#endif // MACHINE_LEARNING_H_
