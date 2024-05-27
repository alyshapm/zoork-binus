#include "RockClimbing.h"

void RockClimbing::handleExamine(const std::string& object) const {
    if (object == "surroundings" || object == "environment") {
        std::cout << "At the base of the wall stands a staff member ready to greet you.\n";
    } else {
        std::cout << "You examine the " << object << ", but there's nothing noteworthy about it.\n";
    }
}

void RockClimbing::handleTalk(const std::string& object) const {
    if (object == "staff member" || object == "staff") {
        std::cout << "The rock climb is fun but dangerous be careful when you climb,\n"
        "(The staff member sighs) This wall is a real challenge. Many have tried, \n"
        "but few have conquered it. Be sure you're prepared before attempting the climb\n";
    } else {
        std::cout << "You talk to the " << object << ", but are answered with silence.\n";
    }
}