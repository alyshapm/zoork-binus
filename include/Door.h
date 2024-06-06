#ifndef ZOORK_DOOR_H
#define ZOORK_DOOR_H

#include "Passage.h"
#include "Player.h"

class Door : public Passage {
public:
    Door(const std::string& name, const std::string& description, Room* from, Room* to, const std::string& requiredItem)
        : Passage(name, description, from, to), requiredItem(requiredItem) {}

    bool canEnter(Player* player) const;

private:
    std::string requiredItem;
};

#endif // ZOORK_DOOR_H
