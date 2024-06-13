#ifndef ZOORK_ENEMY_H
#define ZOORK_ENEMY_H

#include "Character.h"
#include <string>

class Enemy : public Character {
public:
    Enemy(const std::string& name, const std::string& description, int health, int armorClass, int damage)
        : Character(name, description), health(health), armorClass(armorClass), damage(damage) {}

    bool isDefeated() const;
    void takeDamage(int damage);
    int getArmorClass() const;
    int getHealth() const;
    int getDamage() const;

private:
    int health;
    int armorClass;
    int damage;
};

#endif // ZOORK_ENEMY_H
