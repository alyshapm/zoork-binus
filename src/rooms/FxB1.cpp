#include "FxB1.h"

void FxB1::handleExamine(const std::string& object) const {
    if (object == "surroundings" || object == "environment") {
        std::cout << "You see a security guard asleep at his desk and a toolbox.\n";
    } else if (object == "door") {
        std::cout << "The door is locked, and there's a keypad next to it.";
    } else if (object == "toolbox") {
        std::cout << "It's unlocked and contains a rope, a sturdy belt, and a note.\n";
    } else {
        std::cout << "You examine the " << object << ", but there's nothing noteworthy about it.\n";
    }
}

void FxB1::handleTalk(const std::string& object) const {
    if (object == "security guard" || object == "guard") {
        std::cout << "(Wakes up, groggy) 'Hey, you're not supposed to be down here! Get out before I call...' (Falls back asleep)\n";
    } else {
        std::cout << "You talk to the " << object << ", but are answered with silence.\n";
    }
}

void FxB1::handleRead(const std::string& object) const {
    if (object == "note") {
        std::cout << "(The note contains a riddle, the answer to which is the code for the door's keypad)\n";
    } else {
        std::cout << "You read the " << object << ", but find yourself unable to understand it.\n";
    }
}