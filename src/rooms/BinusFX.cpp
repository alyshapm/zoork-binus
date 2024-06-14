#include "BinusFX.h"
#include "Player.h"
#include "Dice.h"
#include "Utilities.h"
#include <iostream>
#include <iomanip>

BinusFX::BinusFX() : Room("Binus FX", 
    "The elevator doors slide open, revealing a dimly lit, high-tech laboratory.\n"
    "Strange contraptions hum and whir, casting eerie shadows on the walls. \n"
    "At the far end of the room, a figure silhouetted against a massive computer screen turns to face you.\n"
    "It's Dr. Z, his eyes glinting with a mix of madness and brilliance.") {
        drZ = std::make_shared<Enemy>("Dr. Z", "The final boss of FX.", 100, 15, 10);
}

void BinusFX::handleExamine(const std::string& object) const {
    if (object == "surroundings" || object == "environment") {
        std::cout << "You can only focus on Dr. Z, waiting for his next move.\n"
                  << "It's better to strike first. Maybe equipping a weapon would be a wise choice.. \n";
    } else {
        std::cout << "You examine the " << object << ", but there's nothing noteworthy about it.\n";
    }
}

void BinusFX::handleFight(const std::string& enemy) const {
    makeLowercase(enemy);
    if (enemy == "dr z" || enemy == "z"  || enemy == "dr. z") {
        std::cout << "You engage in battle with Dr. Z\n";
        Player* player = Player::instance();

        bool enemyDefeated = false;
        bool playerDefeated = false;

        while (!enemyDefeated && !playerDefeated) {
            std::cout << "+------------------------+\n";
            std::cout << "| Your HP: " << std::setw(3) << std::left << player->getHealth() << "           |\n";
            std::cout << "| Dr. Z's HP: " << std::setw(3) << std::left << drZ->getHealth() << "        |\n";
            std::cout << "+------------------------+\n";
            std::cout << "Type 'attack' to attack or 'run' to escape!\n";
            std::cout << "> ";

            std::string choice;
            std::getline(std::cin, choice);

            if (choice == "attack") {
                int playerAttackRoll = Dice::roll(20) + player->getAttackModifier();
                std::cout << "You rolled a " << playerAttackRoll << " for attack.\n";

                if (playerAttackRoll >= drZ->getArmorClass()) {
                    int damage = Dice::roll(player->getDamage());
                    std::cout << "You hit Dr. Z and deal " << damage << " damage!\n";
                    drZ->takeDamage(damage);
                } else {
                    std::cout << "You missed Dr. Z! \n";
                }
            } else if (choice == "run") {
                std::cout << "You can run but theres no where else to go after! \n";
                break;
            } else {
                std::cout << "Invalid choice!\n";
                continue;
            }

            // Mascot's turn to attack
            if (!drZ->isDefeated()) {
                int enemyAttackRoll = Dice::roll(20);
                std::cout << "Dr. Z attacks you!\n";
                std::cout << "He rolled a " << enemyAttackRoll << " for attack.\n";

                if (enemyAttackRoll >= player->getArmorClass()) {
                    int enemyDamage = Dice::roll(drZ->getDamage());
                    std::cout << "Dr. Z hits you and deals " << enemyDamage << " damage!\n";
                    player->takeDamage(enemyDamage);
                } else {
                    std::cout << "You managed to defend against Dr. Z!'s attack!\n";
                }
            }

            if (drZ->isDefeated()) {
                std::cout << "You have defeated Dr. Z!\n";
                enemyDefeated = true;
                Player::instance()->finishGame();
            }

            if (player->isDefeated()) {
                std::cout << "You have been defeated by Dr. Z!\n";
                playerDefeated = true;
            }
        }
    } else {
        std::cout << "There is no enemy named " << enemy << " in this room.\n";
    }
}
