#include "Skorz.h"

void Skorz::handleExamine(const std::string& object) const {
    if (object == "surroundings" || object == "environment") {
        std::cout << "The player might find various objects lying around, such as basketballs, stuffed animals, or arcade game tokens.\n";
    } else if (object == "shadow" || object == "shadows") {
        std::cout << "The shadow stretches across the floor, taking on a grotesque, monstrous shape.\n"
        "It seems to be getting closer… After a few moments, the shadow fully materializes into a terrifying\n"
        "Skorz mascot come to life. Its eyes glow with an eerie light, and its smile is stretched into a sinister grin.\n"
        "There is a slide on the west side of the room which can be used to escape the fight\n";
    } else if (object == "slide") {
        std::cout << "The slide is brightly colored and looks harmless enough, but a sign warns: 'Use at your own risk'\n";
    } else {
        std::cout << "You examine the " << object << ", but there's nothing noteworthy about it.\n";
    }
}