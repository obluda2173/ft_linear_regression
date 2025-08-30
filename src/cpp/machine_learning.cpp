#include "machine_learning.hpp"

BGD::BGD(char* filename, int learning_rate, int milage[], int price[]) {
    this->filename = filename;
    this->epoches = 100; // TODO: make it parameter of constructor
    this->learning_rate = learning_rate;
    this->m = sizeof(milage) / sizeof(milage[0]);
    this->price = arr_to_vec(price);
    this->milage = arr_to_vec(milage);
}

std::vector<int> arr_to_vec(int arr[]) {
    std::vector<int> vec;
    int len = sizeof(arr) / sizeof(arr[0]);

    for (int i = 0; i < len; i++) {
        vec.push_back(arr[i]);
    }

    return vec;
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

void BGD::update_thetas() {
    this->thetas.theta0 = this->thetas.theta0 - this->tmp_thetas.theta0;
    this->thetas.theta1 = this->thetas.theta1 - this->tmp_thetas.theta1;
}

Thetas BGD::batch_gradient_descent() {

    for (int epoch = 0; epoch < this->epoches; epoch++) {
        this->tmp_thetas.theta0 = this->calculate_theta0();
        this->tmp_thetas.theta1 = this->calculate_theta1();

        this->thetas.theta0 = this->thetas.theta0 - this->tmp_thetas.theta0;
        this->thetas.theta1 = this->thetas.theta1 - this->tmp_thetas.theta1;

        this->update_predictions();
        this->update_thetas();
    }

    return this->thetas;
}
