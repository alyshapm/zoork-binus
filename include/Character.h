#ifndef ZOORK_CHARACTER_H
#define ZOORK_CHARACTER_H

#include "GameObject.h"
#include "Item.h"
#include <vector>
#include <string>

class Character : public GameObject {
public:
    Character(const std::string &, const std::string &);

    int getHealth() const;
    void setHealth(int health);
    int getArmorClass() const;
    void setArmorClass(int armorClass);
    int getAttackBonus() const;
    void setAttackBonus(int attackBonus);
    int getDamage() const;
    void setDamage(int damage);
    void takeDamage(int damage);
    bool isDefeated() const;

protected:
    std::vector<Item*> inventory;
    std::vector<std::string> tags;

private:
    int health;
    int armorClass;
    int attackBonus;
    int damage;
};

#endif //ZOORK_CHARACTER_H
