#include "Lobby.h"

void Lobby::handleExamine(const std::string& object) const {
    if (object == "surroundings" || object == "environment") {
        std::cout << "You see a couple students in your vicinity. For some reason, you can’t seem to ignore the billboard.\n";
    } else if (object == "billboard") {
        std::cout << "(The message offering clues)\n";
    } else {
        std::cout << "You examine the " << object << ", but there's nothing noteworthy about it.\n";
    }
}

void Lobby::handleTalk(const std::string& object) const {
    if (object == "students" || object == "student") {
        std::cout << "(The students are just distractions which will tell the player to go back to Vines)\n";
    } else {
        std::cout << "You talk to the " << object << ", but are answered with silence.\n";
    }
}
