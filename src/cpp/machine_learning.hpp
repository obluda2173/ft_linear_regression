#ifndef MACHINE_LEARNING_H_
#define MACHINE_LEARNING_H_

#include <iostream>
#include <vector>

struct t_thetas {
    double theta0 = 0;
    double theta1 = 0;
} s_thetas;

class t_data {
    public:
        int epoches;
        int learning_rate;
        std::vector<int> price;
        std::vector<int> milage;
        std::vector<int> predictions;
        int m;
        t_thetas tmp_thetas;
        t_thetas thetas;

    double calculate_theta0();
    double calculate_theta1();
    void update_predictions();
    t_thetas batch_gradient_descent(t_data data);
} s_data;

#endif // MACHINE_LEARNING_H_
