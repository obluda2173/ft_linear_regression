#include "machine_learning.hpp"

BGD::BGD() {}

BGD::BGD(std::string filename, double learning_rate, int epoches) {
    this->filename = filename;
    this->epoches = epoches;
    this->learning_rate = learning_rate;
    this->extract_data();
    this->m = sizeof(milage) / sizeof(milage[0]);
}

BGD::~BGD() {}

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

        std::cout << milage << std::endl;

        this->milage.push_back(milage);
        this->price.push_back(price);
        this->predictions.push_back(0.0);
    }
}

double substraction(int nbr1, int nbr2) {
    return nbr1 - nbr2;
}

double BGD::calculate_theta0() {
    double summ = 0;

    for (int i = 0; i < this->m; i++) {
        summ += substraction(this->predictions[i], this->price[i]);
    }
    summ *= this->learning_rate * (1.0/this->m);
    return summ;
}

double BGD::calculate_theta1() {
    double summ = 0;

    for (int i = 0; i < this->m; i++) {
        summ += substraction(this->predictions[i], this->price[i]) * this->milage[i];
    }
    summ *= this->learning_rate * (1.0/this->m);
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

void BGD::batch_gradient_descent() {
    for (int epoch = 0; epoch < this->epoches; epoch++) {
        this->tmp_thetas.theta0 = this->calculate_theta0();
        this->tmp_thetas.theta1 = this->calculate_theta1();

        this->update_predictions();
        this->update_thetas();
    }

}

int main(int ac, char** av) {
    if (ac != 2) {
        std::cout << "Wrong amount of arguments" << std::endl;
        exit(1);
    }

    std::string filename = "../../data/data.csv";
    BGD bgd = BGD(filename, 0.2, 100);

    bgd.batch_gradient_descent();

    double expected_price = atoi(av[1]) * bgd.thetas.theta1 + bgd.thetas.theta0;

    std::cout << "Expected price: " << expected_price << std::endl;

    return 0;
}
