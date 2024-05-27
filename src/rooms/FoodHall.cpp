#include "FoodHall.h"

void FoodHall::handleExamine(const std::string& object) const {
    if (object == "surroundings" || object == "environment") {
        std::cout << "The students seem friendly enough. Maybe you can ask them for some advice?\n"
        "Or is the cashier a better choice…\n";
    } else {
        std::cout << "You examine the " << object << ", but there's nothing noteworthy about it.\n";
    }
}

void FoodHall::handleTalk(const std::string& object) const {
    if (object == "students" || object == "student") {
        std::cout << "(They offer gossip, rumors about Mr. Z, or cryptic hints)\n";
    } else if (object == "cashier") {
        std::cout << "(Giving hints of instructions cyphered code to the lift)\n";
    } else {
        std::cout << "You talk to the " << object << ", but are answered with silence.\n";
    }
}
