#include "Character.h"

Character::Character(const std::string& name, const std::string& description)
    : GameObject(name, description), health(10), armorClass(10), attackBonus(0), damage(1) {}

int Character::getHealth() const { 
    return health; 
}

void Character::setHealth(int health) { 
    this->health = health; 
}

int Character::getArmorClass() const { 
    return armorClass;
}

void Character::setArmorClass(int armorClass) { 
    this->armorClass = armorClass;
}

int Character::getAttackBonus() const { 
    return attackBonus; 
}

void Character::setAttackBonus(int attackBonus) { 
    this->attackBonus = attackBonus;
}

int Character::getDamage() const { 
    return damage;
}

void Character::setDamage(int damage) { 
    this->damage = damage;
}

void Character::takeDamage(int damage) { 
    health -= damage;
}
