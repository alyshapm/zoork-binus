#ifndef ZOORK_ROCKCLIMBING_ROOM_H
#define ZOORK_ROCKCLIMBING_ROOM_H

#include "Room.h"
#include <iostream>

class RockClimbing : public Room {
public:
    RockClimbing() : Room("Rock Climbing Station", 
    "A towering rock climbing wall stretches upwards, its colorful holds barely visible in the dim light.\n"
    "The air is thin and chilly. You feel a wave of vertigo as you look up at the seemingly endless climb.") {}
    
    void handleExamine(const std::string& object) const override;
    void handleTalk(const std::string& object) const override;
};

#endif // ZOORK_ROCKCLIMBING_ROOM_H
