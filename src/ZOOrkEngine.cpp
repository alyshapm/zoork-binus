#include "ZOOrkEngine.h"
#include "Utilities.h"
#include "Passage.h"

#include <utility>
#include <algorithm>
#include <cctype>
#include <memory>
#include <Lobby.h>
#include <RockClimbing.h>

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

        if (player->isDefeated()) {
            handleDeathCommand();
        }

        std::cout << "> ";

        std::string input;
        std::getline(std::cin, input);

        std::vector<std::string> words = tokenizeString(input);
        if (words.empty()) {
            continue;
        }

        std::string command = words[0];
        std::vector<std::string> arguments(words.begin() + 1, words.end());

        if (command == "go") {
            handleGoCommand(arguments);
        } else if (command == "look") {
            handleLookCommand(arguments);
        } else if (command == "take" || command == "get") {
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
        } else if (command == "open") {
            handleOpenCommand(arguments);
        } else if (command == "help") {
            handleHelpCommand();
        } else if (command == "fight") {
            handleFightCommand(arguments);
        } else if (command == "drink") {
            handleDrinkCommand(arguments);
        } else if (command == "stats") {
            handleStatsCommand();
        } else if (command == "dance") {
            handleDanceCommand();
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
    if (arguments.empty()) {
        std::cout << "Go where?\n";
        return;
    }

    // Map shorthand directions to full directions
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

    if (currentRoom->getName() == "Lobby" && (direction == "east" || direction == "e")) {
        // Cast the currentRoom pointer to a Lobby pointer
        Lobby* lobbyInstance = dynamic_cast<Lobby*>(currentRoom);
        if (lobbyInstance) {
            lobbyInstance->handleGetThroughSmoke();
        }
    }

    if (currentRoom->getName() == "Rock Climbing Station" && (direction == "up" || direction == "u")) {
        // Cast the currentRoom pointer to a RockClimbing pointer
        RockClimbing* rockClimbingInstance = dynamic_cast<RockClimbing*>(currentRoom);
        if (rockClimbingInstance) {
            rockClimbingInstance->handleClimbWall();
        }
    }

    std::shared_ptr<Passage> passage = currentRoom->getPassage(direction);

    if (!passage) {
        std::cout << "You can't go that way.\n";
        return;
    }

    if (passage->isLocked()) {
        std::cout << "The passage is locked.\n";
    } else {
        player->setCurrentRoom(passage->getTo());
        player->getCurrentRoom()->enter();
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

    std::string itemName = concatenateArguments(arguments); // Correctly concatenate arguments and convert to lowercase
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
    if (arguments.empty()) {
        std::cout << "Examine what?\n";
        return;
    }

    std::string object = concatenateArguments(arguments);
    player->getCurrentRoom()->executeCommand("examine " + object);
}

void ZOOrkEngine::handleReadCommand(std::vector<std::string> arguments) {
    if (arguments.empty()) {
        std::cout << "Read what?\n";
        return;
    }

    std::string object = concatenateArguments(arguments);
    player->getCurrentRoom()->executeCommand("read " + object);
}

void ZOOrkEngine::handleTalkCommand(std::vector<std::string> arguments) {
    if (arguments.empty()) {
        std::cout << "Talk to what?\n";
        return;
    }

    std::string object = concatenateArguments(arguments);
    player->getCurrentRoom()->executeCommand("talk " + object);
}

void ZOOrkEngine::handleOpenCommand(std::vector<std::string> arguments) {
    if (arguments.empty()) {
        std::cout << "Open what?\n";
        return;
    }

    std::string object = concatenateArguments(arguments);
    player->getCurrentRoom()->executeCommand("open " + object);
}

void ZOOrkEngine::handleFightCommand(std::vector<std::string> arguments) {
    if (arguments.empty()) {
        std::cout << "Fight what?\n";
        return;
    }

    std::string object = concatenateArguments(arguments);
    player->getCurrentRoom()->executeCommand("fight " + object);
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

void ZOOrkEngine::handleDrinkCommand(const std::vector<std::string> arguments) {
    if (arguments.empty()) {
        std::cout << "Drink what?\n";
        return;
    }

    std::string itemName = concatenateArguments(arguments);
    std::shared_ptr<Item> item = player->getItem(itemName);
    if (item && item->getType() == ItemType::POTION) {
        std::string lowercaseItemName = makeLowercase(itemName);
        if (lowercaseItemName == "vines potion") {
            int armorReduction = 5; 
            int armorClass = player->getArmorClass();
            player->setArmorClass(armorClass - armorReduction);
            std::cout << "You drank the " << itemName << "\n";
            std::cout << "You feel weaker... \n";
            player->addStatusEffect("Weakened", "Your armor class has been reduced by 5");
            // Remove the potion from the inventory after use
            player->removeItem(itemName);
        } else if (lowercaseItemName == "rise potion") {
            player->addStatusEffect("Strength", "You are now able to do more things..");
            std::cout << "You have used the " << itemName << " and you now feel strong enough to even climb a mountain!\n";
            player->removeItem(itemName);
        } else if (lowercaseItemName == "jkt48 potion") {
            player->addStatusEffect("Restore", "You are no longer weakened..");
            std::cout << "You have used the " << itemName << " and you have cleared your weakened!\n";
            player->removeStatusEffect("Weakened");
            player->removeItem(itemName);
        }

    } else {
        std::cout << "You don't have a " << itemName << " or it's not a potion.\n";
    }
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

void ZOOrkEngine::handleStatsCommand() {
    std::cout << "Player Stats:\n";
    std::cout << "  HP: " << player->getHealth() << "\n";
    std::cout << "  Armor: " << player->getArmorClass() << "\n";
    std::cout << "  Strength Modifier: " << player->getAttackBonus() << "\n";
}

void ZOOrkEngine::handleDeathCommand() {
    while (true) {
        std::string input;
        std::cout << "You have died!\n";
        std::cout << "Do you want to restart or quit the game? (restart/quit)\n> ";
        std::getline(std::cin, input);
        std::string lowerInput = makeLowercase(input);

        if (lowerInput == "restart" || lowerInput == "r") {
            std::cout << "Restarting the game...\n";
            player->reset();

            std::cout << "Game has been restarted. You are now back at the starting room.\n";
            break;
        } else if (lowerInput == "quit" || lowerInput == "q") {
            std::cout << "Are you sure you want to QUIT? (yes/no)\n> ";
            std::getline(std::cin, input);
            std::string quitStr = makeLowercase(input);

            if (quitStr == "y" || quitStr == "yes") {
                gameOver = true;
                break;
            } else if (quitStr == "n" || quitStr == "no") {
                std::cout << "Please choose to either restart or quit.\n";
            } else {
                std::cout << "Invalid input. Please choose to either restart or quit.\n";
            }
        } else {
            std::cout << "Invalid input. Please choose to either restart or quit.\n";
        }
    }
}

void ZOOrkEngine::handleDanceCommand() {
    player->getCurrentRoom()->executeCommand("dance");
}

void ZOOrkEngine::handleHelpCommand() {
    std::cout << "Available commands:\n";
    std::cout << "  go <direction>       - Move in the specified direction (north, south, east, west, up, down)\n";
    std::cout << "  look                 - Look around the current room\n";
    std::cout << "  look <item>          - Look at a specific item in the room\n";
    std::cout << "  take <item>          - Take an item from the room\n";
    std::cout << "  drop <item>          - Drop an item from your inventory\n";
    std::cout << "  quit                 - Quit the game\n";
    std::cout << "  restart              - Restart the game from the beginning\n";
    std::cout << "  examine <item>       - Examine an item in the room\n";
    std::cout << "  read <item>          - Read an item in the room\n";
    std::cout << "  talk to <character>  - Talk to a character in the room\n";
    std::cout << "  inventory            - List all items in your inventory\n";
    std::cout << "  inspect <item>       - Inspect an item in your inventory\n";
    std::cout << "  equip <item>         - Equip an item from your inventory\n";
    std::cout << "  unequip <item>       - Unequip an item\n";
    std::cout << "  status               - Show your current status effects\n";
    std::cout << "  open <item>          - Open an item\n";
    std::cout << "  fight <opponent>     - Engage in combat with an opponent\n";
    std::cout << "  drink <potion>       - Drink a potion\n";
    std::cout << "  stats                - Show your current player statistics\n";
    std::cout << "  dance                - Do a little jig! May be useful in some rooms\n";
    std::cout << "  help                 - Show this help message\n";
}
