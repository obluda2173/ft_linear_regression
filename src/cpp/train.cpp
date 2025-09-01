#include "BGD.hpp"

int main() {
    BGD bgd = BGD();

    bgd.train();
    bgd.save_model("../../data/model.json");
    bgd.save_loss_data("../../data/loss.csv");

    std::cout << "Model was successfully trained" << std::endl;

    return 0;
}
