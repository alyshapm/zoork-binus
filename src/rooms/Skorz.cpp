#include "Skorz.h"
#include "Player.h"
#include "Dice.h"
#include "Utilities.h"
#include "ZOOrkEngine.h"
#include <iostream>
#include <iomanip>

Skorz::Skorz() : Room("Skorz", "You enter the Skorz room.\n"
    "The atmosphere is tense, and you can sense something lurking in the shadows.") {
    skorzMascot = std::make_shared<Enemy>("Skorz Mascot", "A terrifying Skorz mascot come to life.", 25, 10, 10);
}

void Skorz::handleExamine(const std::string& object) const {
    if (object == "surroundings" || object == "environment") {
        std::cout << "The player might find various objects lying around, such as basketballs, stuffed animals, or arcade game tokens.\n"
                  << "You sense a shadowy figure from the corner of your eyes. When you turn to look, it's gone.\n";
    } else if (object == "shadow" || object == "shadows") {
        std::cout << "The shadow stretches across the floor, taking on a grotesque, monstrous shape.\n"
                  << "It seems to be getting closer… After a few moments, the shadow fully materializes into a terrifying\n"
                  << "Skorz mascot come to life. Its eyes glow with an eerie light, and its smile is stretched into a sinister grin.\n"
                  << "There is a slide on the west side of the room which can be used to escape the fight\n";
    } else if(object == "lift" || object == "elevator") {
        if (elevator->isLocked()) {
            std::cout << "What elevator?\n";
        } else {
            std::cout << "After defeating the mascot, an open elevator appears in front of you. It appears to only go up.\n";
        }
    } else {
        std::cout << "You examine the " << object << ", but there's nothing noteworthy about it.\n";
    }
}

void Skorz::handleFight(const std::string& enemy) const {
    makeLowercase(enemy);
    if (enemy == "skorz mascot" || enemy == "mascot") {
        std::cout << "You encounter the Skorz mascot!\n";
        Player* player = Player::instance();

        bool enemyDefeated = false;
        bool playerDefeated = false;

        while (!enemyDefeated && !playerDefeated) {
            std::cout << "+------------------------+\n";
            std::cout << "| Your HP: " << std::setw(3) << std::left << player->getHealth() << "           |\n";
            std::cout << "| Mascot HP: " << std::setw(3) << std::left << skorzMascot->getHealth() << "         |\n";
            std::cout << "+------------------------+\n";
            std::cout << "Type 'attack' to attack or 'run' to escape!\n";
            std::cout << "> ";

            std::string choice;
            std::getline(std::cin, choice);

            if (choice == "attack") {
                int playerAttackRoll = Dice::roll(20) + player->getAttackModifier();
                std::cout << "You rolled a " << playerAttackRoll << " for attack.\n";

                if (playerAttackRoll >= skorzMascot->getArmorClass()) {
                    int damage = Dice::roll(player->getDamage());
                    std::cout << "You hit the Skorz mascot and deal " << damage << " damage!\n";
                    skorzMascot->takeDamage(damage);
                } else {
                    std::cout << "You missed the Skorz mascot!\n";
                }
            } else if (choice == "run") {
                std::cout << "You managed to escape from the Skorz mascot!\n";
                break;
            } else {
                std::cout << "Invalid choice!\n";
                continue;
            }

            // Mascot's turn to attack
            if (!skorzMascot->isDefeated()) {
                int enemyAttackRoll = Dice::roll(20);
                std::cout << "The Skorz mascot attacks you!\n";
                std::cout << "It rolled a " << enemyAttackRoll << " for attack.\n";

                if (enemyAttackRoll >= player->getArmorClass()) {
                    int enemyDamage = Dice::roll(skorzMascot->getDamage());
                    std::cout << "The Skorz mascot hits you and deals " << enemyDamage << " damage!\n";
                    player->takeDamage(enemyDamage);
                } else {
                    std::cout << "You managed to defend against the Skorz mascot's attack!\n";
                }
            }

            if (skorzMascot->isDefeated()) {
                std::cout << "You have defeated the Skorz mascot!\n";
                std::shared_ptr<Item> swordItem = std::make_shared<Item>("Sword", "A sharp blade. Equipping it gives you a higher chance of hitting an attack (+2)", ItemType::WEAPON, 5);
                addItem(swordItem);
                std::cout << "The enemy drops a sword! You notice an elevator behind where the monster used to stand.\n";
                elevator->unlock();
                enemyDefeated = true;
            }

            if (player->isDefeated()) {
                std::cout << "You have been defeated by the Skorz mascot!\n";
                playerDefeated = true;
            }
        }
    } else {
        std::cout << "There is no enemy named " << enemy << " in this room.\n";
    }
}
