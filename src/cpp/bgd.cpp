#include "BGD.hpp"

BGD::BGD() {
    this->filename = FILENAME;
    this->epoches = EPOCHS;
    this->learning_rate = LR;
    this->extract_data();
    this->m = mileage.size();
}

BGD::~BGD() {}

void BGD::extract_data() {
    std::ifstream csv_file(this->filename);
    std::string line;

    std::getline(csv_file, line);

    while (std::getline(csv_file, line)) {
        std::stringstream ss(line);
        std::string s_mileage, s_price;

        std::getline(ss, s_mileage, ',');
        std::getline(ss, s_price, ',');

        double mileage = std::stod(s_mileage) / 1000;
        double price = std::stod(s_price);

        this->mileage.push_back(mileage);
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
        summ += substraction(this->predictions[i], this->price[i]) * this->mileage[i];
    }
    summ /= this->m;
    return summ;
}

void BGD::update_predictions() {
    double theta0 = this->thetas.theta0;
    double theta1 = this->thetas.theta1;

    for (int i = 0; i < this->m; i++) {
        this->predictions[i] = theta0 + theta1 * this->mileage[i];
    }
}

void BGD::update_thetas() {
    this->thetas.theta0 -= this->learning_rate * this->tmp_thetas.theta0;
    this->thetas.theta1 -= this->learning_rate * this->tmp_thetas.theta1;
}

void BGD::train() {
    for (size_t epoch = 0; epoch < this->epoches; epoch++) {
        this->tmp_thetas.theta0 = this->calculate_theta0();
        this->tmp_thetas.theta1 = this->calculate_theta1();

        this->update_thetas();
        this->update_predictions();
        this->create_loss_data(epoch);
    }
}

double BGD::predict(double mileage) {
    double expected_price = mileage * this->thetas.theta1 + this->thetas.theta0;
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

double BGD::calculate_mse() {
    double mse = 0.0;
    size_t mileage_len = this->mileage.size();

    for (size_t i = 0; i < mileage_len; i++) {
        double tmp = this->price[i] - this->predict(this->mileage[i]);
        mse += std::pow(tmp, 2);
    }

    mse /= mileage_len;
    return mse;
}

double BGD::calculate_rmse(double mse) {
    return sqrt(mse);
}

void BGD::create_loss_data(size_t epoch) {
    double mse = this->calculate_mse();
    double rmse = this->calculate_rmse(mse);
    this->lc.push_back({epoch, rmse});
}

void BGD::save_loss_data(std::string file_path) {
    std::ofstream file(file_path);
    std::string header = "epoch,rmse\n";

    file << header;
    for (size_t i = 0; i < this->lc.size(); ++i) {
        std::string epoch = std::to_string(this->lc[i].epoch);
        std::string rmse = std::to_string(this->lc[i].rmse);
        file << epoch << "," << rmse << "\n";
    }
    file.close();
}
