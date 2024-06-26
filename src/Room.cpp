#include "NullPassage.h"
#include "Room.h"
#include "Item.h"
#include "Utilities.h"

#include <utility>
#include <memory>
#include <iterator>
#include <sstream>
#include <vector>
#include <string>

Room::Room(const std::string &n, const std::string &d) : Location(n, d) {
    enterCommand = std::make_shared<RoomDefaultEnterCommand>(this);
}

Room::Room(const std::string &n, const std::string &d, std::shared_ptr<Command> c) : Location(n, d, std::move(c)) {}

void Room::addPassage(const std::string &direction, std::shared_ptr<Passage> p) {
    passageMap[direction] = std::move(p);
}

void Room::removePassage(const std::string &direction) {
    auto it = passageMap.find(direction);
    if (it != passageMap.end()) {
        passageMap.erase(it);
    }
}

std::shared_ptr<Passage> Room::getPassage(const std::string &direction) {
    auto it = passageMap.find(direction);
    if (it != passageMap.end()) {
        return it->second;
    } else {
        std::cout << "It is impossible to go " << direction << "!\n";
        return std::make_shared<NullPassage>(this);
    }
}

void Room::setPassage(std::shared_ptr<Passage> passage) {
    this->passage = passage;
}

void Room::unlockPassage() {
    if (passage) {
        passage->unlock();
    }
}

void Room::lockPassage() {
    if (passage) {
        passage->lock();
    }
}

bool Room::isPassageLocked() const {
    return passage ? passage->isLocked() : false;
}


void Room::addItem(std::shared_ptr<Item> item) {
    std::string itemNameLower = makeLowercase(item->getName());
    items[itemNameLower] = item;
}

void Room::removeItem(const std::string& name) {
    items.erase(name);
}

std::shared_ptr<Item> Room::getItem(const std::string& name) {
    auto it = items.find(name);
    if (it != items.end()) {
        return it->second;  // Return the shared_ptr directly
    }
    return nullptr;  // Return nullptr if the item is not found
}

std::shared_ptr<Item> Room::retrieveItem(const std::string& name) {
    auto it = items.find(name);
    if (it != items.end()) {
        std::shared_ptr<Item> item = it->second;
        items.erase(it);
        return item;
    }
    return nullptr;
}

void Room::executeCommand(const std::string& command) {
    std::istringstream iss(command);
    std::vector<std::string> tokens(std::istream_iterator<std::string>{iss}, std::istream_iterator<std::string>());

    if (tokens.empty()) {
        std::cout << "Invalid command\n";
        return;
    }

    std::string mainCommand = tokens[0];
    std::string object;
    if (tokens.size() > 1) {
        object = tokens[1];
        for (size_t i = 2; i < tokens.size(); ++i) {
            object += " " + tokens[i];
        }
    }

    // Now handle the command and object appropriately
    if (mainCommand == "examine") {
        handleExamine(object);
    } else if (mainCommand == "talk") {
        handleTalk(object);
    } else if (mainCommand == "read") {
        handleRead(object);
    } else if (mainCommand == "open") {
        handleOpen(object);
    } else if (mainCommand == "fight") {
        handleFight(object);
    } else if (mainCommand == "dance") {
        handleDance();
    } else {
        std::cout << "Unknown command: " << mainCommand << std::endl;
    }
}

void Room::handleExamine(const std::string& object) const {
    std::cout << "You examine the " << object << ".\n";
}

void Room::handleTalk(const std::string& object) const {
    std::cout << "You attempt to talk to " << object << ".\n";
}

void Room::handleFight(const std::string& object) const {
    std::cout << "You engage in combat with " << object << ".\n";
}

void Room::handleRead(const std::string& object) const {
    std::cout << "You read " << object << ".\n";
}

void Room::handleDrink(const std::string& object) const {
    std::cout << "You drink " << object << ".\n";
}

void Room::handleClimb(const std::string& object) const {
    std::cout << "You attempt to climb " << object << ".\n";
}

void Room::handleEscape(const std::string& object) const {
    std::cout << "You try to escape " << object << ".\n";
}

void Room::handleGo(const std::string& object) const {
    std::cout << "You try to go " << object << ".\n";
}

void Room::handleOpen(const std::string& object) const {
    std::cout << "You try to open " << object << ".\n";
}

void Room::handleDance() {
    std::cout << "List your dance moves! (left, right, up, or down), type 'stop' to end.\n";
    while (true) {
        std::string input;
        std::cout << "Dance: ";
        std::getline(std::cin, input);

        std::string lowercaseInput = makeLowercase(input);
        if (lowercaseInput == "stop") {
            std::cout << "You stop dancing.\n";
            return;
        }

        bool validMove = false;
        for (const std::string& move : {"left", "right", "up", "down"}) {
            if (lowercaseInput == move) {
                validMove = true;
                std::cout << "You dance " << lowercaseInput << "\n";
                break;
            }
        }

        if (!validMove) {
            std::cout << "That's not a dance move.. \n";
        }
    }
}