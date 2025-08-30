#ifndef MACHINE_LEARNING_H_
#define MACHINE_LEARNING_H_

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

struct Thetas {
    double theta0 = 0;
    double theta1 = 0;
};

struct Data {
    int milage;
    int price;
};

class BGD {
    public:
        std::string filename;
        std::vector<Data> data;
        int epoches;
        int learning_rate;
        int m;
        std::vector<int> price;
        std::vector<int> milage;
        std::vector<int> predictions;
        Thetas tmp_thetas;
        Thetas thetas;

    BGD();
    BGD(char* filename, int learning_rate, int milage[], int price[]);

    void extract_data();
    double calculate_theta0();
    double calculate_theta1();
    void update_predictions();
    Thetas batch_gradient_descent();
};

#endif // MACHINE_LEARNING_H_
