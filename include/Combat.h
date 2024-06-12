#ifndef ZOORK_COMBAT_H
#define ZOORK_COMBAT_H

#include "Player.h"
#include "Enemy.h"

class Combat {
public:
    static void fight(Player& player, Enemy& enemy);

private:
    static bool attack(Character& attacker, Character& defender);
};

#endif //ZOORK_COMBAT_H
