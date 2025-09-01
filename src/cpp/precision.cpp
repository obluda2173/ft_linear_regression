#include "BGD.hpp"

double calculate_mse(BGD& bgd) {
    double mse = 0.0;
    size_t mileage_len = bgd.mileage.size();

    for (size_t i = 0; i < mileage_len; i++) {
        double tmp = bgd.price[i] - bgd.predict(bgd.mileage[i]);
        mse += std::pow(tmp, 2);
    }

    mse /= mileage_len;
    return mse;
}

double calculate_rmse(double mse) {
    return sqrt(mse);
}

int main () {
    BGD bgd;
    std::string filename = "../../data/model.json";
    bgd.thetas = load_model(filename);

    double mse = calculate_mse(bgd);
    double rmse = calculate_rmse(mse);

    std::cout << "Mean Squared Error: " << mse << std::endl;
    std::cout << "Root Mean Squared Error: " << rmse << std::endl;

    return 0;
}
