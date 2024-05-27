#ifndef ZOORK_SEDERHANA_ROOM_H
#define ZOORK_SEDERHANA_ROOM_H

#include "Room.h"
#include <iostream>

class Sederhana : public Room {
public:
    Sederhana() : Room("Sederhana", 
    "The warm, inviting aroma of Indonesian cuisine fills the air.\n"
    "Soft gamelan music plays in the background as patrons enjoy their meals.\n"
    "The menu boasts a variety of dishes, and a mysterious potion gleams on a display pedestal.") {}
    
    void handleExamine(const std::string& object) const override;
};

#endif // ZOORK_SEDERHANA_ROOM_H
