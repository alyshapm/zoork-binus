#ifndef ZOORK_SKORZ_ROOM_H
#define ZOORK_SKORZ_ROOM_H

#include "Room.h"
#include "Enemy.h"
#include <memory>
#include <iostream>

class Skorz : public Room {
public:
    Skorz();

    void handleExamine(const std::string& object) const override;
    void handleFight(const std::string& enemy) const;

    void setPassage(std::shared_ptr<Passage> passage){
        elevator = passage;
    }

private:
    std::shared_ptr<Enemy> skorzMascot;
    std::shared_ptr<Passage> elevator;
};

#endif // ZOORK_SKORZ_ROOM_H
