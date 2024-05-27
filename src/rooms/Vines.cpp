#include "Vines.h"

void Vines::handleExamine(const std::string& object) const {
    if (object == "surroundings" || object == "environment") {
        std::cout << "The abundance of potions is uncountable..\n"
        "It would be easy for you to take one without anyone noticing...\n";
    } else {
        std::cout << "You examine the " << object << ", but there's nothing noteworthy about it.\n";
    }
}