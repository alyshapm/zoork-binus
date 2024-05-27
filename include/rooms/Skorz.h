#ifndef ZOORK_SKORZ_ROOM_H
#define ZOORK_SKORZ_ROOM_H

#include "Room.h"
#include <iostream>

class Skorz : public Room {
public:
    Skorz() : Room("Skorz", 
    "A place filled with fun stuffs like mini basketball, trampolines, etc.\n"
    "However, a looming shadow darkens the far corner of the room, growing larger with each passing moment\n") {}
    
    void handleExamine(const std::string& object) const override;
};

#endif // ZOORK_SKORZ_ROOM_H
