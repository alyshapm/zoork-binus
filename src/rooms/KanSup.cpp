#include "KanSup.h"

void KanSup::handleExamine(const std::string& object) const {
    if (object == "surroundings" || object == "environment") {
        std::cout << "The place is filled with empty tables and chairs. A vent greets you when you look up.\n";
    } else if (object == "vent") {
        std::cout << "The vent is secured tightly in place. It looks like you'll need a tool to pry it open.\n";
    } else {
        std::cout << "You examine the " << object << ", but there's nothing noteworthy about it.\n";
    }
}

void KanSup::handleRead(const std::string& object) const { 
}

void KanSup::handleTalk(const std::string& object) const { 
}