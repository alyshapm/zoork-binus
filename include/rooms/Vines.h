#ifndef ZOORK_VINES_ROOM_H
#define ZOORK_VINES_ROOM_H

#include "Room.h"
#include <iostream>

class Vines : public Room {
public:
    Vines() : Room("Vines", 
    "The Vines store are full of potions. The store is only filled with one type of potion") {}
    
    void handleExamine(const std::string& object) const override;
};

#endif // ZOORK_VINES_ROOM_H
