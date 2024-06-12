#include "Enemy.h"

bool Enemy::isDefeated() const {
    return health <= 0;
}

void Enemy::takeDamage(int damage) {
    health -= damage;
}

int Enemy::getArmorClass() const {
    return armorClass;
}

int Enemy::getHealth() const {
    return health;
}
