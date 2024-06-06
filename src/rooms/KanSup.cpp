#include "KanSup.h"
#include "ZOOrkEngine.h"

void KanSup::handleExamine(const std::string& object) const {
    if (object == "surroundings" || object == "environment") {
        std::cout << "Despite the mess, there isn't anything of value on the tables. A vent greets you when you look up.\n";
    } else if (object == "vent") {
        std::cout << "The vent is secured tightly in place. It looks like you'll need a tool to pry it open.\n";
    } else {
        std::cout << "You examine the " << object << ", but there's nothing noteworthy about it.\n";
    }
}

void KanSup::handleOpen(const std::string& object) const {
    Player* player = Player::instance(); 
    if (!player) {
        std::cout << "Error: Player object is null.\n";
        return;
    }

    if (object == "vent" || object == "grate") {
        if (player->getEquippedItem("crowbar")) {
            std::cout << "You use your crowbar to pry open the vent. It comes off easily.\n";
        } else {
            std::cout << "You try to open the vent, but it seems to be securely fastened. Perhaps you need a tool to pry it open.\n";
        }
    } else {
        std::cout << "It doesn't seem like a " << object << " is something that can be opened.\n";
    }
}
