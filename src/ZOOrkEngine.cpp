#include "ZOOrkEngine.h"
#include "Utilities.h"

#include <utility>
#include <algorithm>
#include <cctype>
#include <memory>

ZOOrkEngine* ZOOrkEngine::instance_ = nullptr;

ZOOrkEngine::ZOOrkEngine(std::shared_ptr<Room> start) : startRoom(std::move(start)) {
    if (instance_ == nullptr) {
        instance_ = this;
    }

    player = Player::instance();
    player->setCurrentRoom(startRoom.get());
    player->getCurrentRoom()->enter();
}

ZOOrkEngine& ZOOrkEngine::instance() {
    return *instance_;
}

void ZOOrkEngine::run() {
    while (!gameOver) {
        std::cout << "> ";

        std::string input;
        std::getline(std::cin, input);

        std::vector<std::string> words = tokenizeString(input);
        std::string command = words[0];
        std::vector<std::string> arguments(words.begin() + 1, words.end());

        if (command == "go") {
            handleGoCommand(arguments);
        } else if ((command == "look")) {
            handleLookCommand(arguments);
        } else if ((command == "take") || (command == "get")) {
            handleTakeCommand(arguments);
        } else if (command == "drop") {
            handleDropCommand(arguments);
        } else if (command == "quit") {
            handleQuitCommand(arguments);
        } else if (command == "restart") {
            handleRestartCommand(arguments);
        } else if (command == "examine") {
            handleExamineCommand(arguments);
        } else if (command == "read") {
            handleReadCommand(arguments);
        } else if (command == "talk" && arguments.size() > 1 && arguments[0] == "to") {
            std::vector<std::string> talkArguments(words.begin() + 2, words.end());
            handleTalkCommand(talkArguments);
        } else if (command == "inventory") {
            handleInventoryCommand();
        } else if (command == "inspect") {
            handleInspectCommand(arguments);
        } else if (command == "equip") {
            handleEquipCommand(arguments);
        } else if (command == "unequip") {
            handleUnequipCommand(arguments);
        } else if (command == "status") {
            handleStatusCommand();
        } else {
            std::cout << "I don't understand that command.\n";
        }
    }
}

void ZOOrkEngine::requestRestart(std::shared_ptr<Room> start) {
    handleRoomRestartCommand({}, start);
}

void ZOOrkEngine::handleRestartCommand(std::vector<std::string> arguments) {
    std::string input;
    std::cout << "Do you want to Restart?\n> ";
    std::getline(std::cin, input);
    std::string restartStr = makeLowercase(input);

    if (restartStr == "y" || restartStr == "yes") {
        // Reset the game state
        player->setCurrentRoom(startRoom.get());
        player->getCurrentRoom()->enter();
        player->clearInventory();
    }
    else {
        std::cout << "Continuing in the current room.\n";
    }
}

void ZOOrkEngine::handleRoomRestartCommand(std::vector<std::string> arguments, std::shared_ptr<Room> start) {
    std::cout << "Restarting...\n> ";
        // Reset the game state
        // gameOver = false;
        if (!start) {
            start = startRoom;
        }
        player->setCurrentRoom(start.get());
        player->getCurrentRoom()->enter();
        player->clearInventory();
}

void ZOOrkEngine::handleGoCommand(std::vector<std::string> arguments) {
    std::string direction;
    if (arguments[0] == "n" || arguments[0] == "north") {
        direction = "north";
    } else if (arguments[0] == "s" || arguments[0] == "south") {
        direction = "south";
    } else if (arguments[0] == "e" || arguments[0] == "east") {
        direction = "east";
    } else if (arguments[0] == "w" || arguments[0] == "west") {
        direction = "west";
    } else if (arguments[0] == "u" || arguments[0] == "up") {
        direction = "up";
    } else if (arguments[0] == "d" || arguments[0] == "down") {
        direction = "down";
    } else {
        direction = arguments[0];
    }

    Room* currentRoom = player->getCurrentRoom();
    auto passage = currentRoom->getPassage(direction);
   if (passage) {
        if (passage->isLocked()) {
            std::cout << "The passage is locked.\n";
        } else {
            player->setCurrentRoom(passage->getTo());
            passage->enter();
        }
    } else {
        std::cout << "You cannot go that way.\n";
    }
}

void ZOOrkEngine::handleLookCommand(const std::vector<std::string>& arguments) {
    Room* currentRoom = player->getCurrentRoom();

    if (arguments.empty()) {
        // No specific target, print the room description
        std::cout << currentRoom->getDescription() << "\n";
    } else {
        // Concatenate all arguments into a single string (assuming item names could be multi-word)
        std::string itemName;
        for (const std::string& arg : arguments) {
            if (!itemName.empty()) {
                itemName += " ";
            }
            itemName += arg;
        }

        // Look for an item with this name in the room
        std::shared_ptr<Item> item = currentRoom->retrieveItem(itemName);
        if (item) {
            std::cout << item->getDescription() << "\n";
        } else {
            std::cout << "There is no '" << itemName << "' here to look at.\n";
        }
    }
}

void ZOOrkEngine::handleTakeCommand(std::vector<std::string> arguments) {
    if (arguments.empty()) {
        std::cout << "Take what?\n";
        return;
    }

    std::string itemName = makeLowercase(concatenateArguments(arguments)); // Correctly concatenate arguments and convert to lowercase
    std::shared_ptr<Item> item = player->getCurrentRoom()->retrieveItem(itemName);
    if (item) {
        std::cout << "You have taken a " << itemName << "\n";
        player->addItem(item);
    } else {
        std::cout << "No such item exists in this room.\n";
    }
}

void ZOOrkEngine::handleDropCommand(std::vector<std::string> arguments) {
    if (arguments.empty()) {
        std::cout << "Drop what?\n";
        return;
    }
    std::string itemName = arguments[0]; // Assuming simple single-word items for simplicity
    std::shared_ptr<Item> item = player->removeItem(itemName);
    if (item) {
        player->getCurrentRoom()->addItem(item);
        std::cout << "You have dropped your " << itemName << "\n";
    } else {
        std::cout << "You don't have that item.\n";
    }
}

void ZOOrkEngine::handleQuitCommand(std::vector<std::string> arguments) {
    std::string input;
    std::cout << "Are you sure you want to QUIT?\n> ";
    std::getline(std::cin, input);
    std::string quitStr = makeLowercase(input);

    if (quitStr == "y" || quitStr == "yes") {
        gameOver = true;
    } else {
        std::cout << "Continuing in the current room.\n";
    }
}

void ZOOrkEngine::handleExamineCommand(std::vector<std::string> arguments) {
    std::string object = concatenateArguments(arguments);
    player->getCurrentRoom()->executeCommand("examine " + object);
}

void ZOOrkEngine::handleReadCommand(std::vector<std::string> arguments) {
    std::string object = concatenateArguments(arguments);
    player->getCurrentRoom()->executeCommand("read " + object);
}

void ZOOrkEngine::handleTalkCommand(std::vector<std::string> arguments) {
    std::string object = concatenateArguments(arguments);
    player->getCurrentRoom()->executeCommand("talk " + object);
}

std::vector<std::string> ZOOrkEngine::tokenizeString(const std::string &input) {
    std::vector<std::string> tokens;
    std::stringstream ss(input);
    std::string token;

    while (std::getline(ss, token, ' ')) {
        tokens.push_back(makeLowercase(token));
    }

    return tokens;
}

std::string ZOOrkEngine::concatenateArguments(const std::vector<std::string>& arguments) {
    std::string result;
    for (const std::string& arg : arguments) {
        if (!result.empty()) {
            result += " ";
        }
        result += arg;
    }
    return result;
}

void ZOOrkEngine::handleInventoryCommand() {
    player->listInventory();
}

void ZOOrkEngine::handleInspectCommand(std::vector<std::string> arguments) {
    if (arguments.empty()) {
        std::cout << "Inspect what?\n";
        return;
    }

    std::string itemName = concatenateArguments(arguments);
    std::shared_ptr<Item> item = player->getItem(itemName);
    if (item) {
        std::cout << "Description of " << itemName << ":\n";
        std::cout << item->getDescription() << "\n";
    } else {
        std::cout << "You don't have a " << itemName << " in your inventory.\n";
    }
}

void ZOOrkEngine::handleEquipCommand(const std::vector<std::string>& arguments) {
    if (arguments.empty()) {
        std::cout << "Equip what?\n";
        return;
    }

    std::string itemName = concatenateArguments(arguments);
    player->equipItem(itemName);
}

void ZOOrkEngine::handleUnequipCommand(const std::vector<std::string>& arguments) {
    if (arguments.empty()) {
        std::cout << "Unequip what?\n";
        return;
    }

    std::string itemName = concatenateArguments(arguments);
    player->unequipItem(itemName);
}

void ZOOrkEngine::handleStatusCommand() {
    player->listStatusEffects();
}