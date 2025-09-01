#include "BGD.hpp"

int main() {
    BGD bgd = BGD();

    bgd.train();
    bgd.save_model("../../data/model.json");

    std::cout << "Model was successfully trained" << std::endl;

    return 0;
}
