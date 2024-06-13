#ifndef ZOORK_BINUSFX_ROOM_H
#define ZOORK_BINUSFX_ROOM_H

#include "Room.h"
#include "Enemy.h"
#include <iostream>

class BinusFX : public Room {
public:
    BinusFX();

    void handleExamine(const std::string& object) const override;
    void handleFight(const std::string& enemy) const;

private:
    std::shared_ptr<Enemy> drZ;
};

#endif // ZOORK_BINUSFX_ROOM_H
