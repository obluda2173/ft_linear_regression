#include "train.hpp"

BGD::BGD() {}

BGD::BGD(std::string filename, double learning_rate, int epoches) {
    this->filename = filename;
    this->epoches = epoches;
    this->learning_rate = learning_rate;
    this->extract_data();
    this->m = milage.size();
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

        double milage = std::stod(s_milage) / 1000;
        double price = std::stod(s_price);

        this->milage.push_back(milage);
        this->price.push_back(price);
        this->predictions.push_back(0.0);
    }
}

double substraction(double nbr1, double nbr2) {
    return nbr1 - nbr2;
}

double BGD::calculate_theta0() {
    double summ = 0;

    for (int i = 0; i < this->m; i++) {
        summ += substraction(this->predictions[i], this->price[i]);
    }
    summ /= this->m;
    return summ;
}

double BGD::calculate_theta1() {
    double summ = 0;

    for (int i = 0; i < this->m; i++) {
        summ += substraction(this->predictions[i], this->price[i]) * this->milage[i];
    }
    summ /= this->m;
    return summ;
}

void BGD::update_predictions() {
    double theta0 = this->thetas.theta0;
    double theta1 = this->thetas.theta1;

    for (int i = 0; i < this->m; i++) {
        this->predictions[i] = theta0 + theta1 * this->milage[i];
    }
}

void BGD::update_thetas() {
    this->thetas.theta0 -= this->learning_rate * this->tmp_thetas.theta0;
    this->thetas.theta1 -= this->learning_rate * this->tmp_thetas.theta1;
}

void BGD::train() {
    for (int epoch = 0; epoch < this->epoches; epoch++) {
        this->tmp_thetas.theta0 = this->calculate_theta0();
        this->tmp_thetas.theta1 = this->calculate_theta1();

        this->update_thetas();
        this->update_predictions();
    }
}

double BGD::predict(double milage) {
    double expected_price = milage * this->thetas.theta1 + this->thetas.theta0;
    return expected_price;
}

bool BGD::save_model(std::string file_path) {
    std::string tmp = file_path + ".tmp";
    std::ofstream out(tmp, std::ios::out | std::ios::trunc);
    if (!out.is_open()) return false;

    out << std::setprecision(17);
    out << "{"
        << "\"theta0\": " << this->thetas.theta0 << ", "
        << "\"theta1\": " << this->thetas.theta1;
    out << "}\n";

    out.close();

    if (std::rename(tmp.c_str(), file_path.c_str()) != 0) {
        std::remove(tmp.c_str());
        return false;
    }
    return true;
}

int main(int ac, char** av) {
    if (ac != 2) {
        std::cout << "Wrong amount of arguments" << std::endl;
        exit(1);
    }

    std::string filename = "../../data/data.csv";
    double lr = 0.0001;
    int epoches = 10000000;

    BGD bgd = BGD(filename, lr, epoches);

    bgd.train();

    double expected_price = bgd.predict(stod(std::string(av[1])) / 1000);

    std::cout << "Expected price: " << expected_price << std::endl;

    bgd.save_model("../../data/model.json");

    return 0;
}
