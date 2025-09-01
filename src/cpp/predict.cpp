#include "BGD.hpp"

double prompt() {
    double mileage;

    std::cout << "Enter mileage: ";
    std::cin >> mileage;
    return mileage / 1000;
}

int main() {
    std::string filename = "../../data/model.json";
    Thetas thetas = load_model(filename);

    double mileage = prompt();

    double prediction = predict(thetas, mileage);

    std::cout << "Expected price: " << prediction << std::endl;

    return 0;
}
