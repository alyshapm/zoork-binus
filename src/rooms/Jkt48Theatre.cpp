#include "Jkt48Theatre.h"

void Jkt48Theatre::handleExamine(const std::string& object) const {
    if (object == "surroundings" || object == "environment") {
        std::cout << "The vast theatre is empty, save for the stage and photos surrounding you.\n";
    } else if (object == "photos" || object == "photo") {
        std::cout << "The photos depict various JKT48 members, each with a unique pose and costume.\n"
        "Their names and accomplishments are etched in small plaques below each photo.\n";
    } else if (object == "stage") {
        std::cout << "The stage is empty, but a microphone stand and a few musical instruments rest in the corner.\n"
        "The spotlight seems to beckon you towards the center.\n";
    } else {
        std::cout << "You examine the " << object << ", but there's nothing noteworthy about it.\n";
    }
}