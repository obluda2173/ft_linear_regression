#include "BGD.hpp"

int main () {
    BGD bgd;
    std::string filename = "../../data/model.json";
    bgd.thetas = load_model(filename);

    double mse = bgd.calculate_mse();
    double rmse = bgd.calculate_rmse(mse);

    std::cout << "Mean Squared Error: " << mse << std::endl;
    std::cout << "Root Mean Squared Error: " << rmse << std::endl;

    return 0;
}
