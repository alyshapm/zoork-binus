#ifndef ZOORK_ENEMY_H
#define ZOORK_ENEMY_H

#include "Character.h"
#include <string>

class Enemy : public Character {
public:
    Enemy(const std::string& name, const std::string& description, int health, int armorClass)
        : Character(name, description), health(health), armorClass(armorClass) {}

    bool isDefeated() const;
    void takeDamage(int damage);
    int getArmorClass() const;
    int getHealth() const;

private:
    int health;
    int armorClass;
};

#endif // ZOORK_ENEMY_H
