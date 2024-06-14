#include "Lobby.h"
#include "ZOOrkEngine.h"

void Lobby::handleExamine(const std::string& object) const {
    if (object == "surroundings" || object == "environment") {
        std::cout << "You see a couple students in your vicinity. For some reason, you can't seem to ignore the billboard.\n"
        "The professors with there nametags are gathered on the side, take a closer look.\n";
    } else if (object == "professors") {
        std::cout << "You see nametags attached to their clothes, you can try to read them\n";
    }
    else if (object == "floor") {
        std::cout << "you look around and see a flashlight at your reach…\n";
    }
    else if (object == "smoke") {
        std::cout << "you can't through without seeing what's on the other side, find a source of light.\n";
    }
    else {
        std::cout << "You examine the " << object << ", but there's nothing noteworthy about it.\n";
    }
}

void Lobby::handleRead(const std::string& object) const {
    if (object == "billboard") {
        std::cout << "Light! Light! Light! Flash a light at the gray wall.\n"; 
    } else if (object == "nametags") {
        std::cout << "MrJalo\n";
        std::cout << "Mr Borris\n";
        std::cout << "Ms Flash\n";
        std::cout << "Mr Alary\n";
        std::cout << "You might want to talk to them\n";
    }
    else {
        std::cout << "You read the " << object << ", but find yourself unable to understand it.\n";
    }
}

void Lobby::handleTalk(const std::string& object) const {
    if (object == "students" || object == "student") {
        std::cout << "I heard that the potions from the stores downstairs are delicious.\n";
    } 
    else if (object == "mr jalo") {
        std::cout << "He sees and hears EVERYTHIN...\n";
    }
    else if (object == "mr borris") {
        std::cout << "I've been thinking about opening my own restaurant you know!\n";
    }
    else if (object == "ms flash") {
        std::cout << "…no answer, she seems to be looking for something.\n";
    }
    else if (object == "mr alary") {
        std::cout << "I think Ms flash dropped her flashlight somewhere on the floor.\n";
    }
    else {
        std::cout << "You talk to the " << object << ", but are answered with silence.\n";
    }
}

void Lobby::handleGetThroughSmoke() const{
    Player* player = Player::instance(); 
    if (player->getEquippedItem("flashlight")) {
        std::cout << "With the help of the flashlight you get through the smoke.\n";
        smoke->unlock();
        player->unequipItem("flashlight");
    } else {
            std::cout << "A gray wall blocks your way, it seems like smoke... you can take a closer look\n";
            return;
    }
}