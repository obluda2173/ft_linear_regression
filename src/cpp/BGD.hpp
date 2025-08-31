#ifndef BGD_HPP
#define BGD_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip>
#include <cstdio>

#define FILENAME "../../data/data.csv";
#define EPOCHS 10000000;
#define LR 0.0001;

struct Thetas {
    double theta0 = 0.0;
    double theta1 = 0.0;
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
    ~BGD();

    void extract_data();
    double calculate_theta0();
    double calculate_theta1();
    void update_predictions();
    void update_thetas();
    void train();
    double predict(double milage);
    bool save_model(std::string path);
};

std::vector<int> arr_to_vec(int arr[]);

#endif // BGD_HPP
