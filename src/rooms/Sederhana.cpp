#include "Sederhana.h"
#include <ZOOrkEngine.h>

void Sederhana::handleExamine(const std::string& object) const {
    Player* player = Player::instance();
    if (object == "surroundings" || object == "environment") {
        std::cout << "Despite the busy and decorative atmosphere, you find yourself drawn to the potion the most.\n"
        "A lady stands at the counter.\n";
    } else if (object == "menu") {
        std::cout << "The menu features classic Indonesian dishes like Nasi Goreng, Satay, and Gado-Gado. A note at the bottom mentions a Potion! for adventurers\n";
    } else if (object == "dark spot") {
        if (player->getEquippedItem("flashlight")) {
            std::cout << "You shine your flashlight at the dark spot...\n A table appears, there seems to be an object on it…\n";
        } else {
            std::cout << "It's too dark to see, you need a some light...\n";
        }
    }else if (object == "potion") {
        std::cout << "A label read Rise, might this be a hint...\n";
    } else if (object == "table") {
        if (player->getEquippedItem("flashlight")) {
            std::cout << "You can see a (weapon) on the table\n";
        } else {
            std::cout << "The tables are all full, you should talk to the person at the counter.\n";
        }
    } else {
        std::cout << "You examine the " << object << ", but there's nothing noteworthy about it.\n";
    }
}

void Sederhana::handleTalk(const std::string& object) const {
    if (object == "lady") {
        std::cout << "it's too loud to hear what she is saying but she points at the dark spot and her lips read the word there.\n";
    } else {
        std::cout << "You read the " << object << ", but find yourself unable to understand it.\n";
    }
}