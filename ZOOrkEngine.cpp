//
// Created by Richard Skarbez on 5/7/23.
//

#include "ZOOrkEngine.h"

#include <utility>
#include <algorithm> // Required for std::transform
#include <cctype>     // Required for std::tolower
#include <memory>


ZOOrkEngine::ZOOrkEngine(std::shared_ptr<Room> start) {
    player = Player::instance();
    player->setCurrentRoom(start.get());
    player->getCurrentRoom()->enter();
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
        } else if ((command == "look") || (command == "inspect")) {
            handleLookCommand(arguments);
        } else if ((command == "take") || (command == "get")) {
            handleTakeCommand(arguments);
        } else if (command == "drop") {
            handleDropCommand(arguments);
        } else if (command == "quit") {
            handleQuitCommand(arguments);
        } else if (command == "examine") {
            handleExamineCommand(arguments);
        } else {
            std::cout << "I don't understand that command.\n";
        }
    }
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
    player->setCurrentRoom(passage->getTo());
    passage->enter();
}

// void ZOOrkEngine::handleLookCommand(std::vector<std::string> arguments) {
//     // To be implemented
//     std::cout << "This functionality is not yet enabled.\n";
// }


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


// void ZOOrkEngine::handleTakeCommand(std::vector<std::string> arguments) {
//     // To be implemented
//     std::cout << "This functionality is not yet enabled.\n";
// }

void ZOOrkEngine::handleTakeCommand(std::vector<std::string> arguments) {
    if (arguments.empty()) {
        std::cout << "Take what?\n";
        return;
    }
    std::string itemName = arguments[0]; // Assuming simple single-word items for simplicity
    std::shared_ptr<Item> item = player->getCurrentRoom()->retrieveItem(itemName);
    if (item) {
        player->addItem(item);
        std::cout << "Taken.\n";
    } else {
        std::cout << "No such item.\n";
    }
}


// void ZOOrkEngine::handleDropCommand(std::vector<std::string> arguments) {
//     // To be implemented
//     std::cout << "This functionality is not yet enabled.\n";
// }

void ZOOrkEngine::handleDropCommand(std::vector<std::string> arguments) {
    if (arguments.empty()) {
        std::cout << "Drop what?\n";
        return;
    }
    std::string itemName = arguments[0]; // Assuming simple single-word items for simplicity
    std::shared_ptr<Item> item = player->removeItem(itemName);
    if (item) {
        player->getCurrentRoom()->addItem(item);
        std::cout << "Dropped.\n";
    } else {
        std::cout << "You don't have that item.\n";
    }
}


void ZOOrkEngine::handleQuitCommand(std::vector<std::string> arguments) {
    std::string input;
    std::cout << "Are you sure you want to QUIT?\n> ";
    std::cin >> input;
    std::string quitStr = makeLowercase(input);

    if (quitStr == "y" || quitStr == "yes") {
        gameOver = true;
    }
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

std::string ZOOrkEngine::makeLowercase(std::string input) {
    std::string output = std::move(input);
    // Using a lambda to ensure the correct tolower function is called
    std::transform(output.begin(), output.end(), output.begin(),
                   [](unsigned char c) -> unsigned char { return std::tolower(c); });

    return output;
}

void ZOOrkEngine::handleExamineCommand(std::vector<std::string> arguments) {
    if (arguments.empty()) {
        std::cout << "Examine what?\n";
        return;
    }

    std::string object;
    for (const std::string& arg : arguments) {
        if (!object.empty()) {
            object += " ";
        }
        object += arg;
    }
    std::transform(object.begin(), object.end(), object.begin(), ::tolower);

    if (object == "door") {
        std::cout << "The door is locked, and there's a keypad next to it.\n";
    } else if (object == "guard" || object == "security guard") {
        std::cout << "The security guard is snoring loudly, oblivious to your presence.\n";
    } else {
        std::cout << "You examine the " << object << ".\n";
    }
}
