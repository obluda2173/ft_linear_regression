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
#define EPOCHS 1000000;
#define LR 0.0001;

struct Thetas {
    double theta0 = 0.0;
    double theta1 = 0.0;
};

struct LC {
    size_t epoch;
    double rmse;
};

class BGD {
    public:
        std::string filename;
        size_t epoches;
        double learning_rate;
        int m;
        std::vector<double> price;
        std::vector<double> mileage;
        std::vector<double> predictions;
        Thetas tmp_thetas;
        Thetas thetas;
        std::vector<LC> lc;

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
    void create_loss_data(size_t epoch);
    void save_loss_data(std::string file_path);
    double calculate_mse();
    double calculate_rmse(double mse);
};

Thetas load_model(const std::string& filename);
double predict(const Thetas& thetas, double mileage);

#endif // BGD_HPP
