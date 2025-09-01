#ifndef BGD_HPP
#define BGD_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip>
#include <cstdio>
#include <cmath>

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
        std::vector<double> mileage;
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
    friend double calculate_mse(BGD& bgd);
};

Thetas load_model(const std::string& filename);
double predict(const Thetas& thetas, double mileage);
double prompt();

#endif // BGD_HPP
