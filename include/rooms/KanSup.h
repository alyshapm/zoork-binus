#ifndef ZOORK_KANSUP_ROOM_H
#define ZOORK_KANSUP_ROOM_H

#include "Room.h"
#include <iostream>

class KanSup : public Room {
public:
    KanSup() : Room("Kantin Supir", 
    "You find yourself in an empty food court.\n"
    "Chairs and tables are arranged messily.\n"
    "There doesn't seem to be any doors besides the one you entered in..") {}
    
    void handleExamine(const std::string& object) const override;
    void handleOpen(const std::string& object) const override;
};

#endif // ZOORK_KANSUP_ROOM_H
