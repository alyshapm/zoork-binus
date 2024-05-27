#include "Sederhana.h"

void Sederhana::handleExamine(const std::string& object) const {
    if (object == "surroundings" || object == "environment") {
        std::cout << "Despite the busy and decorative atmosphere, you find yourself drawn to the potion the most.\n";
    } else if (object == "menu") {
        std::cout << "The menu features classic Indonesian dishes like Nasi Goreng, Satay, and Gado-Gado. A note at the bottom mentions a Potion! for adventurers\n";
    } else if (object == "potion") {
        std::cout << "The potion is a vibrant red color and emits a faint glow.\n";
    } else {
        std::cout << "You examine the " << object << ", but there's nothing noteworthy about it.\n";
    }
}