#ifndef ZOORK_FOODHALL_ROOM_H
#define ZOORK_FOODHALL_ROOM_H

#include "Room.h"
#include <iostream>

class FoodHall : public Room {
public:
    FoodHall() : Room("Food Hall", 
    "The supermarket fills with students queueing for purchase.\n"
    "Students chatter and laugh as they line up at the cashier.") {}
    
    void handleExamine(const std::string& object) const override;
    void handleTalk(const std::string& object) const override;
};

#endif // ZOORK_FOODHALL_ROOM_H
