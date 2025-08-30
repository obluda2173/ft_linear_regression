#include "machine_learning.hpp"

BGD::BGD(char* filename, int learning_rate, int milage[], int price[]) {
    this->filename = filename;
    this->epoches = 100;
    this->learning_rate = learning_rate;
    this->m = sizeof(milage) / sizeof(milage[0]);
    this->price = price;
    this->milage = milage;
}

void BGD::extract_data() {
    std::ifstream csv_file(this->filename);
    std::string line;

    std::getline(csv_file, line);

    while (std::getline(csv_file, line)) {
        std::stringstream ss(line);
        std::string s_milage, s_price;

        std::getline(ss, s_milage, ',');
        std::getline(ss, s_price, ',');

        int milage = std::stod(s_milage);
        int price = std::stod(s_price);

        this->data.push_back({milage, price});
    }
}

int substraction(int nbr1, int nbr2) {
    return nbr1 - nbr2;
}

double BGD::calculate_theta0() {
    int summ = 0;

    for (int i = 0; i < this->epoches; i++) {
       summ += substraction(this->predictions[i], this->price[i]);
    }
    summ *= this->learning_rate * (1/this->m);
    return summ;
}

double BGD::calculate_theta1() {
    int summ = 0;

    for (int i = 0; i < this->epoches; i++) {
       summ += substraction(this->predictions[i], this->price[i]) * this->milage[i];
    }
    summ *= this->learning_rate * (1/this->m);
    return summ;
}

void BGD::update_predictions() {
    double theta0 = this->tmp_thetas.theta0;
    double theta1 = this->tmp_thetas.theta1;


    for (int i = 0; i < this->m; i++) {
        this->predictions[i] = theta0 + theta1 * this->milage[i];
    }
}

Thetas BGD::batch_gradient_descent() {
    Thetas thetas;
    double tmp_theta0 = 0, tmp_theta1 = 0;
    int m = this->milage.size();
    int i = 0;


    for (int epoch = 0; epoch < this->epoches; epoch++) {
        this->tmp_thetas.theta0 = this->calculate_theta0();
        this->tmp_thetas.theta1 = this->calculate_theta1();

        this->thetas.theta0 = this->thetas.theta0 - this->tmp_thetas.theta0;
        this->thetas.theta1 = this->thetas.theta1 - this->tmp_thetas.theta1;

        this->update_predictions();
    }

    return this->thetas;
}
