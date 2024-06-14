#include "FxB1.h"
#include "Player.h"
#include "Dice.h"
#include "Utilities.h"
#include "ZOOrkEngine.h"
#include <iostream>
#include <iomanip>

bool continueExamining = false;

void FxB1::handleExamine(const std::string& object) const {
    if (object == "surroundings" || object == "environment") {
        std::cout << "You see a security guard asleep at his desk and a toolbox.\n"
                  << "Next to him, a door with a keypad. He's not doing a good job of guarding it..\n";
    } else if (object == "door") {
        if (steelDoor->isLocked()) {
            std::cout << "The door is locked, and there's a keypad next to it.\n";
        } else {
            std::cout << "The door is unlocked. A staircase awaits you.\n";
        }
    } else if (object == "toolbox") {
        std::cout << "It's unlocked and contains a hammer, a sturdy crowbar, and a note.\n";
    } else if (object == "keypad") {
        std::cout << "You examine the keypad.\n";
        std::string input;
        continueExamining = true;
        do {
            std::cout << "Enter the 6 numbers passcode ('exit' to continue examining surroundings): ";
            std::getline(std::cin, input);
            if (input == "exit") {
                std::cout << "You decide to keep looking around.\n";
                continueExamining = false;
            } else {
                handleEnterPasscode(input);
            }
        } while (continueExamining);
    } else {
        std::cout << "You examine the " << object << ", but there's nothing noteworthy about it.\n";
    }
}

void FxB1::handleRead(const std::string& object) const {
    if (object == "note") {
        if (correctPasscode.size() != 6) {
            std::cerr << "Error: Passcode length is incorrect.\n";
            std::cout << correctPasscode;
        }

        std::cout << "Shopping List:\n\n"
                  << "-" << correctPasscode[0] << " ripe apples, a tart delight\n"
                  << "-" << correctPasscode[1] << " juicy oranges, bursting with sunlight\n"
                  << "-" << correctPasscode[2] << " plump tomatoes, firm to the touch\n"
                  << "-" << correctPasscode[3] << " crisp carrots, offering a healthy crunch\n"
                  << "-" << correctPasscode[4] << " sweet mangoes, a tropical treat\n"
                  << "-" << correctPasscode[5] << " vibrant peppers, adding a spicy heat\n\n"
                  << "The fruits will open the way to a new realm.\n";

        return;
    } else {
        std::cout << "You read the " << object << ", but find yourself unable to understand it.\n";
    }
}

void FxB1::handleTalk(const std::string& object) const {
    if (object == "security guard" || object == "guard") {
        std::cout << "(Wakes up, groggy) \"Hey, you're not supposed to be down here! Get out before I call...\" (Falls back asleep)\n";
    } else {
        std::cout << "You talk to the " << object << ", but there's no response.\n";
    }
}

void FxB1::handleEnterPasscode(const std::string& passcode) const {
    if (passcode == correctPasscode) {
        std::cout << "Click! The door unlocks with a satisfying click. You can now go up.\n";
        steelDoor->unlock(); 
        continueExamining = false;
        
    } else {
        if (--remainingAttempts > 0) {
            std::cout << "Access Denied. Incorrect passcode. You have " << remainingAttempts << " attempt(s) remaining.\n";
        } else {
            std::cout << "Access Denied. You've used all your attempts. The security system has activated, and you hear footsteps approaching.\n"
                      << "You've been captured by the security guard!\n";
            continueExamining = false;
            fightSecurityGuard();
        }
    }
}

void FxB1::fightSecurityGuard() const {
    // Create a security guard enemy
    std::shared_ptr<Enemy> securityGuard = std::make_shared<Enemy>("Security Guard", "The guard has awoken and he's ready to fight!", 15, 5, 5);
    Player* player = Player::instance();

    std::cout << "You engage in combat with the security guard!\n";

    bool enemyDefeated = false;
    bool playerDefeated = false;

    while (!enemyDefeated && !playerDefeated) {
        std::cout << "+------------------------+\n";
        std::cout << "| Your HP: " << std::setw(3) << std::left << player->getHealth() << "           |\n";
        std::cout << "| Guard HP: " << std::setw(3) << std::left << securityGuard->getHealth() << "          |\n";
        std::cout << "+------------------------+\n";
        std::cout << "Type 'attack' to attack or 'run' to escape!\n";
        std::cout << "> ";

        std::string choice;
        std::getline(std::cin, choice);

        if (choice == "attack") {
            int playerAttackRoll = Dice::roll(20) + player->getAttackModifier();
            std::cout << "You rolled a " << playerAttackRoll << " for attack.\n";

            if (playerAttackRoll >= securityGuard->getArmorClass()) {
                int damage = Dice::roll(player->getDamage());
                std::cout << "You hit the Security Guard and deal " << damage << " damage!\n";
                securityGuard->takeDamage(damage);
            } else {
                std::cout << "You missed the Security Guard!\n";
            }
        } else if (choice == "run") {
            std::cout << "You can't run! Theres no way out.\n";
            continue;
        } else {
            std::cout << "Invalid choice!\n";
            continue;
        }

        // Security's turn to attack
        if (!securityGuard->isDefeated()) {
            int enemyAttackRoll = Dice::roll(securityGuard->getArmorClass());
            std::cout << "The Security Guard attacks you!\n";
            std::cout << "It rolled a " << enemyAttackRoll << " for attack.\n";

            if (enemyAttackRoll >= player->getArmorClass()) {
                int enemyDamage = Dice::roll(securityGuard->getDamage());
                std::cout << "The Security Guard hits you and deals " << enemyDamage << " damage!\n";
                player->takeDamage(enemyDamage);
            } else {
                std::cout << "You managed to defend against the Skorz mascot's attack!\n";
            }
        }

        if (securityGuard->isDefeated()) {
            std::cout << "You have defeated the Security Guard!\n";
            std::shared_ptr<Item> taser = std::make_shared<Item>("Taser", "A small taser. Equipping it gives you a higher chance of hitting an attack (+1)", ItemType::WEAPON, 1);
            addItem(taser);
            std::cout << "The enemy drops a keycard and a taser! You use the card to unlock the steel door.\n";
            steelDoor->unlock();
            enemyDefeated = true;
        }

        if (player->isDefeated()) {
            std::cout << "You have been defeated by the Security Guard!\n";
            playerDefeated = true;
        }
    }
}