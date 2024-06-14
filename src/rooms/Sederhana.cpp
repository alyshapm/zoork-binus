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
            std::cout << "You shine your flashlight at the dark spot...\nA table appears, there seems to be an object on it...\n";
        } else {
            std::cout << "It's too dark to see, you need a some light...\n";
        }
    }else if (object == "potion") {
        std::cout << "A label read Rise, might this be a hint...\n";
    } else if (object == "table") {
        if (player->getEquippedItem("flashlight")) {
            std::shared_ptr<Item> knifeItem = std::make_shared<Item>("Knife", "A short sharp blade. It might be better than fighting bare handed.", ItemType::WEAPON, 2);
            addItem(knifeItem);
            std::cout << "You can see a knife on the table, you might need it later...\n";
            std::cout << "Standing next to the table, you understand the presence of a dark spot.\n";
            std::cout << "Up north you can see the silhouette of a never ending wall, should you check it out?\n";
        } else {
            std::cout << "The tables are all full, you should talk to the person at the counter.\n";
        }
    } else {
        std::cout << "You examine the " << object << ", but there's nothing noteworthy about it.\n";
    }
}

void Sederhana::handleTalk(const std::string& object) const {
    if (object == "lady") {
        std::cout << "It's too loud to hear what she is saying but she points at the dark spot and her lips read the word there.\n";
    } else {
        std::cout << "You read the " << object << ", but find yourself unable to understand it.\n";
    }
}