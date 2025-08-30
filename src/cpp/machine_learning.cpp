#include "machine_learning.hpp"

int substraction(int nbr1, int nbr2) {
    return nbr1 - nbr2;
}

double t_data::calculate_theta0() {
    int summ = 0;

    for (int i = 0; i < this->epoches; i++) {
       summ += substraction(this->predictions[i], this->price[i]);
    }
    summ *= this->learning_rate * (1/this->m);
    return summ;
}

double t_data::calculate_theta1() {
    int summ = 0;

    for (int i = 0; i < this->epoches; i++) {
       summ += substraction(this->predictions[i], this->price[i]) * this->milage[i];
    }
    summ *= this->learning_rate * (1/this->m);
    return summ;
}

void t_data::update_predictions() {
    double theta0 = this->tmp_thetas.theta0;
    double theta1 = this->tmp_thetas.theta1;


    for (int i = 0; i < this->m; i++) {
        this->predictions[i] = theta0 + theta1 * this->milage[i];
    }
}

t_thetas t_data::batch_gradient_descent(t_data data) {
    t_thetas thetas;
    double tmp_theta0 = 0, tmp_theta1 = 0;
    int m = data.milage.size();
    int i = 0;


    for (int epoch = 0; epoch < data.epoches; epoch++) {
        this->tmp_thetas.theta0 = this->calculate_theta0();
        this->tmp_thetas.theta1 = this->calculate_theta1();

        this->thetas.theta0 = this->thetas.theta0 - this->tmp_thetas.theta0;
        this->thetas.theta1 = this->thetas.theta1 - this->tmp_thetas.theta1;

        this->update_predictions();
    }

    return this->thetas;
}
