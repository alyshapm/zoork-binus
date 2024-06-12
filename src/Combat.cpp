#include "Combat.h"
#include "Dice.h"
#include <iostream>

void Combat::fight(Player& player, Enemy& enemy) {
    while (player.getHealth() > 0 && enemy.getHealth() > 0) {
        if (attack(player, enemy)) {
            std::cout << player.getName() << " hits " << enemy.getName() << " for " << player.getDamage() << " damage!\n";
            enemy.takeDamage(player.getDamage());
        } else {
            std::cout << player.getName() << " misses " << enemy.getName() << ".\n";
        }

        if (enemy.getHealth() <= 0) {
            std::cout << enemy.getName() << " is defeated!\n";
            return;
        }

        if (attack(enemy, player)) {
            std::cout << enemy.getName() << " hits " << player.getName() << " for " << enemy.getDamage() << " damage!\n";
            player.takeDamage(enemy.getDamage());
        } else {
            std::cout << enemy.getName() << " misses " << player.getName() << ".\n";
        }

        if (player.getHealth() <= 0) {
            std::cout << player.getName() << " is defeated!\n";
            return;
        }
    }
}

bool Combat::attack(Character& attacker, Character& defender) {
    int roll = Dice::roll(20);
    return roll + attacker.getAttackBonus() >= defender.getArmorClass();
}
