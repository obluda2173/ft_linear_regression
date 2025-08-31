#include "BGD.hpp"

Thetas load_model(std::string& filename) {
    Thetas thetas;
    std::ifstream json_file(filename);
    std::string line, content;

    if (!json_file.is_open()) {
        throw std::runtime_error("Could not find the file\n");
    }


    while (std::getline(json_file, line)) {
        content += line;
    }

    size_t pos0 = content.find("theta0");
    if (pos0 != std::string::npos) {
        size_t start = content.find(":", pos0) + 1;
        size_t end = content.find(",", start);
        thetas.theta0 = std::stod(content.substr(start, end - start));
    }

    size_t pos1 = content.find("theta1");
    if (pos1 != std::string::npos) {
        size_t start = content.find(":", pos1) + 1;
        size_t end = content.find(",", start);
        thetas.theta1 = std::stod(content.substr(start, end - start));
    }

    return thetas;
}

double predict(Thetas thetas, double mileage) {
    double prediction = thetas.theta1 * mileage + thetas.theta0;

    // std::cout << "theta0: " << thetas.theta0 << std::endl;
    // std::cout << "theta1: " << thetas.theta1 << std::endl;
    // std::cout << "mileage: " << mileage << std::endl;

    return prediction;
}

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
